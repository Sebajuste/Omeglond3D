#include "OGLFontSystem.hpp"

#if defined (WIN32)
    #include <windows.h>
#else
    #include <GL/glx.h>
#endif

namespace OMGL3D
{
    namespace OGL
    {
        OGLFontSystem::OGLFontSystem(const std::string & name) : FONT::IFont(name)
        {
        }

        OGLFontSystem::~OGLFontSystem()
        {
            glDeleteLists(_base, 256);
        }

        void OGLFontSystem::LoadFont(const std::string & font_name, unsigned int size, bool bold, bool italic)
        {

            #if defined (WIN32)
                HFONT hFont = NULL;
                HFONT hPrevFont = NULL;
                HDC	DC = GetDC(NULL);

                _base = glGenLists(256);

                hFont = CreateFont(size,
                    0,
                    0,
                    0,
                    bold, // bold
                    italic, // italid
                    FALSE, // underline
                    FALSE, // overlined
                    ANSI_CHARSET,
                    OUT_TT_PRECIS,
                    CLIP_DEFAULT_PRECIS,
                    ANTIALIASED_QUALITY,
                    FF_DONTCARE|DEFAULT_PITCH, font_name.c_str());

                hPrevFont = (HFONT)SelectObject(DC, hFont);

                wglUseFontBitmaps(DC, 0, 255, _base);
                SelectObject(DC, (HGDIOBJ)hPrevFont);
            #else
                Display * display;
                XFontStruct * fontInfo;

                /* Get our current display long enough to get the fonts */
                display = XOpenDisplay( NULL );

                /* Get the font information */
                fontInfo = XLoadQueryFont( display, font_name.c_str() );

                /* If the above font didn't exist try one that should */
                if ( fontInfo == NULL )
                {
                    fontInfo = XLoadQueryFont( display, "fixed" );
                    if ( fontInfo == NULL )
                    {
                        XCloseDisplay( display );
                        return;
                    }
                }

                unsigned int first, last, firstrow, lastrow, maxchars, firstbitmap;
                Font id = fontInfo->fid;
                first = fontInfo->min_char_or_byte2;
                last = fontInfo->max_char_or_byte2;

                firstrow = (int)fontInfo->min_byte1;
                lastrow = (int)fontInfo->max_byte1;
                maxchars = 256 * lastrow + last;

                _base = glGenLists(maxchars+1);

                if (_base == 0) {
                    XFreeFont( display, fontInfo );
                    XCloseDisplay( display );
                    return;
                }

                firstbitmap = 256 * firstrow + first;

                for(unsigned int i=firstrow; i<=lastrow; i++)
                {
                    glXUseXFont(id, firstbitmap, last-first+1, _base+firstbitmap);
                    firstbitmap += 256;
                }

                /* Recover some memory */
                XFreeFont( display, fontInfo );

                /* close the display now that we're done with it */
                XCloseDisplay( display );
            #endif
        }

        void OGLFontSystem::Draw(const std::string & text, const CORE::CColor & color)
        {
            glColor3fv(*color);

            glPushAttrib(GL_LIST_BIT);
            glRasterPos4f(0, 0, 0, 1);
            glListBase(_base);
            glCallLists(text.size(), GL_UNSIGNED_BYTE, text.c_str());
            glPopAttrib();

            glColor3ub(255, 255, 255);
        }
    }
}
