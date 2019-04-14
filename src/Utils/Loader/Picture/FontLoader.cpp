#include "FontLoader.hpp"

#include <ft2build.h>   // GNU freetype font 2
#include FT_FREETYPE_H

namespace OMGL3D
{
    namespace UTILS
    {

        FontLoader::FontLoader()
        {

        }

        FontLoader::~FontLoader()
        {

        }

        CORE::CPicture * FontLoader::Load(const CBuffer & buffer) throw(EXCP::LoadException)
        {
            /*
            static const unsigned int ptSize = 14;

            FT_Library ftlib;
            FT_Face face;

            if (FT_Init_FreeType(&ftlib))
                throw new EXCP::LoadException("Load font error : FreeType not initialized");
            if (FT_New_Face(ftlib, fontName, 0, &face))
                throw new EXCP::LoadException("Load font error : font can not be loaded");

            FT_Set_Char_Size(face, 0, ptSize << 6, 96, 96); // résolution courante des écrans: 96 dpi

            FT_Load_Char(face, ch, FT_LOAD_RENDER);
            FT_Bitmap * pgpix = &face->glyph->bitmap;  // raccourci
*/

            return 0;
        }

        CBuffer FontLoader::Save(CORE::CPicture * picture) throw(EXCP::SaveException)
        {
            throw new EXCP::SaveException("Save font function not implemented");
        }
    }
}
