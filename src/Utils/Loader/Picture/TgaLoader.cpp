#include "TgaLoader.hpp"

#include "../CBufferOperation.hpp"

#include "../../../Debug/DebugAllocation.hpp"

#include <sstream>

namespace OMGL3D
{
    namespace UTILS
    {
        enum TextureFormat { OMGL_TEXTURE_LUMINANCE, OMGL_TEXTURE_LUMINANCE_ALPHA, OMGL_TEXTURE_RGB, OMGL_TEXTURE_RGBA };

        enum TgaEnum { TGA_I=1, TGA_RGB=2, TGA_G=3, TGA_I_RLE=9, TGA_RGB_RLE=10, TGA_G_RLE=11 };

        struct GlTexture
        {
            unsigned int  width;           /* largeur */
            unsigned int  height;          /* hauteur */

            int  format;                   /* RVB, RVBA, Luminance, Luminance Alpha */
            int   internalFormat;          /* composantes d'un texel */

            unsigned char *texels;         /* données de l'image */

        };

        #pragma pack(push, 1)
        struct TgaHeader
        {
            unsigned char   id_lenght;          /* size of image id */
            unsigned char   colormap_type;      /* 1 is has a colormap */
            unsigned char   image_type;         /* compression type */

            short   cm_first_entry;     /* colormap origin */
            short   cm_length;          /* colormap length */
            unsigned char   cm_size;            /* colormap size */

            short   x_origin;           /* bottom left x coord origin */
            short   y_origin;           /* bottom left y coord origin */

            short   width;              /* picture width (in pixels) */
            short   height;             /* picture height (in pixels) */

            unsigned char   pixel_depth;        /* bits per pixel: 8, 16, 24 or 32 */
            unsigned char   image_descriptor;   /* 24 bits = 0x00; 32 bits = 0x80 */

        };
        #pragma pack(pop)

        inline void GetTextureInfo(TgaHeader * header, GlTexture * info);
        inline void Read32Bits(std::istream & in, GlTexture * texinfo);
        inline void Read32BitsRLE(std::istream & in, GlTexture * texinfo);
        inline void Read24Bits(std::istream & in, GlTexture * texinfo);
        inline void Read24BitsRLE(std::istream & in, GlTexture * texinfo);
        inline void Read16Bits(std::istream & in, GlTexture * texinfo);
        inline void ReadGrey16Bits(std::istream & in, GlTexture * texinfo);
        inline void Read8Bits(std::istream & in, GlTexture * texinfo, unsigned char * colormap);
        inline void Read8Bits(std::istream & in, GlTexture * texinfo);

        inline void Write32Bits(std::stringstream & buffer, const CORE::CPicture & picture);
        inline void Write32BitsRLE(std::stringstream & buffer, const CORE::CPicture & picture);
        inline void Write24Bits(std::stringstream & buffer, const CORE::CPicture & icture);
        inline void Write24BitsRLE(std::stringstream & buffer, const CORE::CPicture & picture);


        TgaLoader::TgaLoader()
        {

        }

        TgaLoader::~TgaLoader()
        {

        }

        CORE::CPicture * TgaLoader::Load(const CBuffer & bufferObject) throw(EXCP::LoadException)
        {
            std::stringstream buffer;
            buffer << bufferObject.GetBuffer();

            // lecture de l'en tête du fichier TGA
            TgaHeader header;
            GlTexture texture_info;
            unsigned char * colormap = 0;

            // Lecture de l'header
            CBufferOperation::Read(buffer, header);


            if( (header.width % 2) != 0 || (header.height % 2) != 0 ) {
                throw EXCP::LoadException("Error size of "+bufferObject.GetName());
            }

            buffer.seekg(header.id_lenght, std::ios::cur);  // on positionne le curseur apres le header
            GetTextureInfo(&header, &texture_info);         // on initialise les informations pour la texture



            // si le fichier utilise une palette de couleur
            if( header.colormap_type)
            {
                colormap = new unsigned char[header.cm_length * (header.cm_size >> 3)];
                buffer.read(reinterpret_cast<char*>(&colormap), header.cm_length * (header.cm_size >> 3));
            }

            texture_info.texels = new unsigned char[texture_info.width * texture_info.height * texture_info.internalFormat];

            // en cas d'erreur d'allocation de mémoire, on arrète le chargement
            if( texture_info.texels == 0)
            {
                throw EXCP::LoadException("Bad allocation "+bufferObject.GetName());
            }

            // on appele la fonction de lecture en fonction de son type et du nombre de bits pour chaque pixel
            switch(header.image_type)
            {
                case TGA_I:
                    Read8Bits(buffer, &texture_info, colormap);
                    break;

                case TGA_RGB:
                {
                    switch(header.pixel_depth)
                    {
                        case 16:
                            Read16Bits(buffer, &texture_info);
                            break;

                        case 24:
                            Read24Bits(buffer, &texture_info);
                            break;

                        case 32:
                            Read32Bits(buffer, &texture_info);
                            break;

                        default:
                            break;
                    }
                }
                break;

                case TGA_G:
                {
                    switch(header.pixel_depth)
                    {
                        case 16:
                            ReadGrey16Bits(buffer, &texture_info);
                            break;

                        case 8:
                            Read8Bits(buffer, &texture_info);
                            break;

                        default:
                            break;
                    }
                }
                break;

                case TGA_RGB_RLE:
                {
                    switch(header.pixel_depth)
                    {
                        case 24:
                            Read24BitsRLE(buffer, &texture_info);
                            break;

                        case 32:
                            Read32BitsRLE(buffer, &texture_info);
                            break;

                        default:
                            break;
                    }
                }
                break;

                default:
                    break;
            }





            // on supprime la palette de couleur
            delete colormap;
            // Note: on ne supprime pas texture_info.texels  En effet, on utilise ce pointeur dans la classe Picture
            // C'est le destructeur de Picture qui désalouera la mémoire.

            // on crée un image à partir des informations obtenus
            CORE::CPicture *p = new CORE::CPicture(bufferObject.GetName(), header.pixel_depth, texture_info.width, texture_info.height, texture_info.texels);
            //boost::shared_ptr<CORE::Picture> picture = boost::shared_ptr<CORE::Picture>(new CORE::Picture(header.pixel_depth, texture_info.width, texture_info.height, texture_info.texels));

            // On retourne notre image
            return p;
            //return picture;
        }

        CBuffer TgaLoader::Save(CORE::CPicture * picture) throw(EXCP::SaveException)
        {
            if( !picture )
            {
                throw EXCP::SaveException("Error save picture : no picture");
            }

            std::stringstream buffer;

            TgaHeader header;
            header.id_lenght = 0x00;
            header.colormap_type = 0x00;
            header.image_type = TGA_RGB;

            header.cm_first_entry = 0;
            header.cm_length = 0;
            header.cm_size = 0x00;

            header.x_origin = 0;
            header.y_origin = 0;

            header.width = picture->GetWidth();
            header.height = picture->GetHeight();
            header.pixel_depth = picture->GetBpp();
            header.image_descriptor = 0x00;

            CBufferOperation::Write(buffer, header);
            //WriteTextureInfo(buffer, header);

            switch(header.image_type)
            {
                case TGA_RGB:
                {
                    switch(header.pixel_depth)
                    {
                        case 24:
                            Write24Bits(buffer, *picture);
                            break;

                        case 32:
                            Write32Bits(buffer, *picture);
                            break;
                    }
                    break;
                }

                case TGA_RGB_RLE:
                {
                    switch(header.pixel_depth)
                    {
                        case 24:
                            Write24BitsRLE(buffer, *picture);
                            break;

                        case 32:
                            Write32BitsRLE(buffer, *picture);
                            break;
                    }
                    break;
                }
            }

            return CBuffer("buffer_picture", buffer.str());
        }





        void GetTextureInfo(TgaHeader *header, GlTexture *info)
        {
            info->width = header->width;
            info->height = header->height;

            switch(header->image_type)
            {
                case TGA_G:        // 8-16 bits, dégradé de gris
                case TGA_G_RLE:    // 8-16 bits, dégradé de gris (RLE)
                {
                    if( (int)header->pixel_depth == 8 ) {
                        info->format = OMGL_TEXTURE_LUMINANCE;
                        info->internalFormat = 1;
                    }
                    else { /* 16 bits */
                        info->format = OMGL_TEXTURE_LUMINANCE_ALPHA;
                        info->internalFormat = 2;
                    }
                }
                break;

                case TGA_I:           // 8 bits index couleur
                case TGA_RGB:         // 16-24-32 bits BVR
                case TGA_I_RLE:       // 8 bits index couleur (RLE)
                case TGA_RGB_RLE:     // 16-24-32 bits BVR (RLE)
                {
                    // les images 8 et 16 bits seront converties en 24 bits
                    if( (int)header->pixel_depth <= 24 ) {
                        info->format = OMGL_TEXTURE_RGB;
                        info->internalFormat = 3;
                    } else { // 32 bits
                        info->format = OMGL_TEXTURE_RGBA;
                        info->internalFormat = 4;
                    }
                }
                break;

                default:
                    break;
            }
        }




        void Read32Bits(std::istream &in, GlTexture *texinfo)
        {
            for(unsigned int i=0; i< texinfo->height * texinfo->width; ++i)
            {
                unsigned char blue, green, red, alpha;

                CBufferOperation::Read(in, blue);
                CBufferOperation::Read(in, green);
                CBufferOperation::Read(in, red);
                CBufferOperation::Read(in, alpha);

                texinfo->texels[i*4 + 0 ] = red;
                texinfo->texels[i*4 + 1 ] = green;
                texinfo->texels[i*4 + 2 ] = blue;
                texinfo->texels[i*4 + 3 ] = alpha;
            }
        }

        void Read32BitsRLE(std::istream &in, GlTexture *texinfo)
        {
            unsigned char* texels = texinfo->texels;
            int index=0;

            for(unsigned int i=0; i < texinfo->height*texinfo->width; )
            {
                unsigned char header;

                CBufferOperation::Read(in, header);

                if( header & 0x80 ) // 10000000
                {
                    int size=0;
                    unsigned char blue, green, red, alpha;
                    CBufferOperation::Read(in, blue);
                    CBufferOperation::Read(in, green);
                    CBufferOperation::Read(in, red);
                    CBufferOperation::Read(in, alpha);

                    size = 1 + ( header & 0x7F );  // 01111111

                    for(int j=0; j<size; ++j)
                    {
                        texels[index+0]=red; texels[index+1]=green; texels[index+2]=blue; texels[index+3]=alpha;
                        index+=4;
                        i++;
                    }
                }
                else
                {
                    int size = 1 + (header & 0x7F);

                    for(int j=0; j<size; ++j)
                    {
                        unsigned char blue, green, red, alpha;
                        CBufferOperation::Read(in, blue);
                        CBufferOperation::Read(in, green);
                        CBufferOperation::Read(in, red);
                        CBufferOperation::Read(in, alpha);
                        texels[index+0]=red; texels[index+1]=green; texels[index+2]=blue; texels[index+3]=alpha;
                        index+=4;
                        i++;
                    }
                }
            }
        }

        void Read24Bits(std::istream &in, GlTexture *texinfo)
        {
            for(unsigned int i=0; i< texinfo->height * texinfo->width; ++i)
            {
                unsigned char blue, green, red;

                CBufferOperation::Read(in, blue);
                CBufferOperation::Read(in, green);
                CBufferOperation::Read(in, red);

                texinfo->texels[i*3 +  0 ] = red;
                texinfo->texels[i*3 +  1 ] = green;
                texinfo->texels[i*3 +  2 ] = blue;
            }
        }

        void Read24BitsRLE(std::istream &in, GlTexture *texinfo)
        {
            unsigned char* texels = texinfo->texels;
            int index=0;

            for(unsigned int i=0; i < texinfo->height*texinfo->width; )
            {
                unsigned char header;

                CBufferOperation::Read(in, header);


                if( header & 0x80 ) // 10000000
                {
                    int size=0;
                    unsigned char blue, green, red;
                    CBufferOperation::Read(in, blue);
                    CBufferOperation::Read(in, green);
                    CBufferOperation::Read(in, red);

                    size = 1 + ( header & 0x7F );  // 01111111

                    for(int j=0; j<size; ++j)
                    {
                        texels[index+0]=red; texels[index+1]=green; texels[index+2]=blue;
                        index+=3;
                        i++;
                    }
                }
                else
                {
                    int size = 1 + (header & 0x7F);

                    for(int j=0; j<size; ++j)
                    {
                        unsigned char blue, green, red;
                        CBufferOperation::Read(in, blue);
                        CBufferOperation::Read(in, green);
                        CBufferOperation::Read(in, red);
                        texels[index+0]=red; texels[index+1]=green; texels[index+2]=blue;
                        index+=3;
                        i++;
                    }
                }
            }
        }

        void Read16Bits(std::istream &in, GlTexture *texinfo)
        {
            for(unsigned int i=0; i < texinfo->height*texinfo->width; ++i)
            {
                unsigned char c1, c2;
                CBufferOperation::Read(in, c1);
                CBufferOperation::Read(in, c2);

                short color = c1 + (c2 << 8);

                texinfo->texels[ (i * 3) + 0 ] = (unsigned char)(((color & 0x7C00) >> 10) << 3);
                texinfo->texels[ (i * 3) + 1 ] = (unsigned char)(((color & 0x03E0) >>  5) << 3);
                texinfo->texels[ (i * 3) + 2 ] = (unsigned char)(((color & 0x001F) >>  0) << 3);
            }
        }

        void ReadGrey16Bits(std::istream &in, GlTexture *texinfo)
        {
            for(unsigned int i=0; i < texinfo->height*texinfo->width; ++i)
            {
                unsigned char c1, c2;
                CBufferOperation::Read(in, c1);
                CBufferOperation::Read(in, c2);

                texinfo->texels[i*2 + 0 ] = c1;
                texinfo->texels[i*2 + 1 ] = c2;
            }
        }

        void Read8Bits(std::istream &in, GlTexture *texinfo, unsigned char *colormap)
        {
            for(unsigned int i=0; i < texinfo->height*texinfo->width; ++i)
            {
                unsigned char color;
                CBufferOperation::Read(in, color);

                texinfo->texels[i*3 + 2] = colormap[color*3 + 0];
                texinfo->texels[i*3 + 1] = colormap[color*3 + 1];
                texinfo->texels[i*3 + 0] = colormap[color*3 + 2];
            }
        }

        void Read8Bits(std::istream &in, GlTexture *texinfo)
        {
            for(unsigned int i=0; i< texinfo->height*texinfo->width; ++i)
            {
                unsigned char color;
                CBufferOperation::Read(in, color);

                texinfo->texels[i] = color;
            }
        }

        void Write32Bits(std::stringstream &buffer, const CORE::CPicture &picture)
        {
            const unsigned char *color = picture.GetDatas();

            for(unsigned int i=0; i< picture.GetWidth() * picture.GetHeight(); ++i)
            {
                CBufferOperation::Write(buffer, color[i*4 +  0 ]);
                CBufferOperation::Write(buffer, color[i*4 +  1 ]);
                CBufferOperation::Write(buffer, color[i*4 +  2 ]);
                CBufferOperation::Write(buffer, color[i*4 +  3 ]);
            }
        }

        void Write32BitsRLE(std::stringstream &buffer, const CORE::CPicture &picture)
        {
        }

        void Write24Bits(std::stringstream &buffer, const CORE::CPicture &picture)
        {
            const unsigned char *color = picture.GetDatas();

            for(unsigned int i=0; i< picture.GetWidth() * picture.GetHeight(); ++i)
            {
                // B G R
                CBufferOperation::Write(buffer, color[i*3 +  2 ]);
                CBufferOperation::Write(buffer, color[i*3 +  1 ]);
                CBufferOperation::Write(buffer, color[i*3 +  0 ]);
            }
        }

        void Write24BitsRLE(std::stringstream &buffer, const CORE::CPicture &picture)
        {
            const unsigned char* pixel = picture.GetDatas();
            int index_pixel=0;

            unsigned char blue, green, red;
            int last_index=0;

            int count_pixel_equal=0;
            int count_pixel_different=0;

            // pour tous les pixel
            for(unsigned int i=0; i< picture.GetWidth() * picture.GetHeight(); ++i)
            {
                // si le pixel actuel est de la même couleur que le précendent
                if( blue == pixel[index_pixel] && green == pixel[index_pixel+1] && red == pixel[index_pixel+2])
                {
                    // si on avait une suite de pixel différent
                    if( count_pixel_different != 0)
                    {
                        // On enregistrer le nombre de pixel différent
                        char header = 0x80 + count_pixel_equal-1;
                        CBufferOperation::Write(buffer, header);

                        // on enregistre tous les pixel
                        for(int j=0; j<count_pixel_different; ++j)
                        {
                            CBufferOperation::Write(buffer, pixel[last_index]);
                            CBufferOperation::Write(buffer, pixel[last_index+1]);
                            CBufferOperation::Write(buffer, pixel[last_index+2]);
                            last_index+=3;
                        }

                        count_pixel_different = 0;
                    }
                    else // si on est toujours dans la suite
                    {

                        // si on approche de la limite, on enregistre la suite
                        if( count_pixel_equal > 126 )
                        {
                            // on indique combien de couleur se suivent
                            char header = 0x80 + count_pixel_equal-1;
                            CBufferOperation::Write(buffer, header);

                            // on enregistre le pixel à répéter
                            CBufferOperation::Write(buffer, blue);
                            CBufferOperation::Write(buffer, green);
                            CBufferOperation::Write(buffer, red);

                            count_pixel_equal = 0;
                        }

                    }

                    // on indique qu'il faut utiliser un pixel supplémentaire de la même couleur
                    count_pixel_equal++;
                }
                // si il est différent, mais que l'on a enregistré une suite du pixel identique
                else if(count_pixel_equal != 0 )
                {
                    // on indique combien de couleur se suivent
                    char header = 0x80 + count_pixel_equal-1;
                    CBufferOperation::Write(buffer, header);

                    // on enregistre le pixel à répéter
                    CBufferOperation::Write(buffer, blue);
                    CBufferOperation::Write(buffer, green);
                    CBufferOperation::Write(buffer, red);


                    count_pixel_equal = 0;
                    count_pixel_different++;

                    // on enregistre l'index auquel doit commencer la prochaine séquence de couleur non identique
                    last_index = index_pixel;
                }
                // Si il est différent, et que l'on est pas dans une suite de pixel identique
                else
                {

                    count_pixel_different++;
                }

                blue = pixel[index_pixel];
                green = pixel[index_pixel+1];
                red = pixel[index_pixel+2];
                index_pixel+=3;
            }

            /*
            unsigned char* texels = texinfo->texels;
            int index=0;

            for(unsigned int i=0; i < texinfo->height*texinfo->width; )
            {
                unsigned char header;

                BufferOperation::read(in, header);

                // il y a une compression
                if( header & 0x80 ) // 10000000
                {
                    int size=0;
                    unsigned char blue, green, red;
                    BufferOperation::read(in, blue);
                    BufferOperation::read(in, green);
                    BufferOperation::read(in, red);

                    size = 1 + ( header & 0x7F );  // 01111111

                    for(int j=0; j<size; ++j)
                    {
                        texels[index+0]=red;
                        texels[index+1]=green;
                        texels[index+2]=blue;
                        index+=3;
                        i++;
                    }
                }
                else
                {
                    int size = 1 + (header & 0x7F);

                    for(int j=0; j<size; ++j)
                    {
                        unsigned char blue, green, red;
                        BufferOperation::read(in, blue);
                        BufferOperation::read(in, green);
                        BufferOperation::read(in, red);
                        texels[index+0]=red;
                        texels[index+1]=green;
                        texels[index+2]=blue;
                        index+=3;
                        i++;
                    }
                }
            }
            */
        }
    }
}
