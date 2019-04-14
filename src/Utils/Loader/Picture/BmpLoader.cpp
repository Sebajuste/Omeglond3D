#include "BmpLoader.hpp"

#include "../../../Core/CPicture.hpp"

#include "../CBufferOperation.hpp"

#include "../../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        enum TextureType { OMGL_TEXTURE_RGB };

        #pragma pack(push, 1)
        struct FileHeader
        {
            unsigned char signature[2];
            unsigned int size;
            unsigned short reserved1;
            unsigned short reserved2;
            unsigned int offset;
        };

        struct InformationHeader
        {
            unsigned int size_header;
            unsigned int width;
            unsigned int height;
            unsigned short nb_plans;
            unsigned short bits_count;
            unsigned int compression_type;
            unsigned int size;
            unsigned int width_resolution;
            unsigned int height_resolution;
            unsigned int size_color;
            unsigned int weight_color;
        };
        #pragma pack(pop)

        struct TextureInformation
        {
            unsigned int width;
            unsigned int height;

            int format;                   // RVB, RVBA, Luminance, Luminance Alpha
            int internalFormat;           // composantes d'un pixel


            unsigned char *texels;        // nos texel
        };

        inline void GetTextureInfo(InformationHeader *iheader, TextureInformation *texinfo);
        inline void Read24Bits(std::istream &in, TextureInformation* texinfo);

        //inline void WriteHeaders(std::ostream &out, const FileHeader &file_header, const InformationHeader &information_header);
        inline void Write24Bits(std::ostream &out, const CORE::CPicture &picture);

        CORE::CPicture * BmpLoader::Load(const CBuffer &bufferObject) throw(EXCP::LoadException)
        {
            std::stringstream buffer;
            buffer << bufferObject.GetBuffer();

            FileHeader fheader;
            InformationHeader iheader;
            TextureInformation itexture;
            unsigned char* colormap = 0;


            // lecture du header du fichier
            CBufferOperation::Read(buffer, fheader);

            /*
            CBufferOperation::Read(buffer, fheader.signature[0]);
            CBufferOperation::Read(buffer, fheader.signature[1]);
            CBufferOperation::Read(buffer, fheader.size);
            CBufferOperation::Read(buffer, fheader.reserved1);
            CBufferOperation::Read(buffer, fheader.reserved2);
            CBufferOperation::Read(buffer, fheader.offset);
            */


            // lecture du header de l'image
            CBufferOperation::Read(buffer, iheader);
            /*
            CBufferOperation::Read(buffer, iheader.size_header);
            CBufferOperation::Read(buffer, iheader.width);
            CBufferOperation::Read(buffer, iheader.height);
            CBufferOperation::Read(buffer, iheader.nb_plans);
            CBufferOperation::Read(buffer, iheader.bits_count);
            CBufferOperation::Read(buffer, iheader.compression_type);
            CBufferOperation::Read(buffer, iheader.size);
            CBufferOperation::Read(buffer, iheader.width_resolution);
            CBufferOperation::Read(buffer, iheader.height_resolution);
            CBufferOperation::Read(buffer, iheader.size_color);
            CBufferOperation::Read(buffer, iheader.weight_color);
            */
            GetTextureInfo(&iheader, &itexture);

            // si il existe une palette de couleur
            if( iheader.size_color != 0)
            {
                colormap = new unsigned char[iheader.size_color];
                for(unsigned int i=0; i<iheader.size_color/4; ++i) {
                    CBufferOperation::Read(buffer, colormap[i]);
                }
            }

            itexture.texels = new unsigned char[itexture.width*itexture.height*itexture.internalFormat];


            switch(iheader.compression_type)
            {
                case 0:
                {
                    switch(iheader.bits_count)
                    {
                        case 24:
                            Read24Bits(buffer, &itexture);
                            break;

                        default:
                            break;
                    }
                    break;
                }

                default:
                    break;
            }

            // on supprime la palette de couleur
            delete colormap;

            return new CORE::CPicture(bufferObject.GetName(), iheader.bits_count, itexture.width, itexture.height, itexture.texels);
        }

        CBuffer BmpLoader::Save(CORE::CPicture * picture) throw(EXCP::SaveException)
        {
            std::stringstream buffer;

            FileHeader file_header;
            InformationHeader information_header;

            file_header.signature[0] = 'B';
            file_header.signature[1] = 'M';
            file_header.size = sizeof(FileHeader) + sizeof(InformationHeader) + picture->GetWidth()*picture->GetHeight()*3;
            file_header.reserved1 = 0;
            file_header.reserved2 = 0;
            file_header.offset = sizeof(FileHeader) + sizeof(InformationHeader);

            information_header.size_header = 0x28;
            information_header.width = picture->GetWidth();
            information_header.height = picture->GetHeight();
            information_header.nb_plans = 1;
            information_header.bits_count = 24;
            information_header.compression_type = 0;
            information_header.size = picture->GetWidth()*picture->GetHeight()*3;
            information_header.width_resolution = picture->GetWidth();
            information_header.height_resolution = picture->GetHeight();
            information_header.size_color = 0;
            information_header.weight_color = 0;

            //WriteHeaders(buffer, file_header, information_header);
            CBufferOperation::Write(buffer, file_header);
            CBufferOperation::Write(buffer, information_header);

            switch(information_header.bits_count)
            {
                case 24:
                {
                    switch(information_header.compression_type)
                    {
                        case 0:
                            Write24Bits(buffer, *picture);
                            break;
                    }
                    break;
                }
            }


            return CBuffer("bmp_buffer", buffer.str());
        }

        void GetTextureInfo(InformationHeader *iheader, TextureInformation *texinfo)
        {
            texinfo->width = iheader->width;
            texinfo->height = iheader->height;

            switch(iheader->bits_count)
            {
                case 24:
                    texinfo->format = OMGL_TEXTURE_RGB;
                    texinfo->internalFormat = 3;
                    break;

                default:
                    break;
            }
        }


        void Read24Bits(std::istream &in, TextureInformation* texinfo)
        {
            for(unsigned int i=0; i<texinfo->width*texinfo->height; ++i)
            {

                unsigned char blue, green, red;
                CBufferOperation::Read(in, blue);
                CBufferOperation::Read(in, green);
                CBufferOperation::Read(in, red);

                texinfo->texels[i*3+0] = red;
                texinfo->texels[i*3+1] = green;
                texinfo->texels[i*3+2] = blue;

            }
        }


        void Write24Bits(std::ostream &out, const CORE::CPicture &picture)
        {
            const unsigned char *datas = picture.GetDatas();
            for(unsigned int i=0; i<picture.GetWidth()*picture.GetHeight(); ++i)
            {
                // V R B
                CBufferOperation::Write(out, datas[i*3+1]);
                CBufferOperation::Write(out, datas[i*3+0]);
                CBufferOperation::Write(out, datas[i*3+2]);
            }
        }
    }
}
