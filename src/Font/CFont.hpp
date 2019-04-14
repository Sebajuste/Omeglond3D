#ifndef _DEF_OMEGLOND3D_CFONT_HPP
#define _DEF_OMEGLOND3D_CFONT_HPP

#include "IFont.hpp"

namespace OMGL3D
{
    namespace FONT
    {

        public CFont : public IFont
        {

        public:

            virtual ~CFont() {}

            virtual void Draw(const std::string & text, const CORE::CColor & color=CORE::CColor::White)=0;


        protected:

            CFont(const std::string & name);

            UTILS::ResourcePtr<CORE::ITexture> _texture;
            UTILS::ResourcePtr<MODEL::IStaticModel> _squad;

        };

    }
}

#endif
