#ifndef _DEF_OMEGLOND3D_CIMAGE_HPP
#define _DEF_OMEGLOND3D_CIMAGE_HPP

#include "CComponent.hpp"

#include "../Core/ITexture.hpp"
#include "../Model/IStaticModel.hpp"
#include "../Utils/Export.hpp"

namespace OMGL3D
{
    namespace UI
    {
        class EXPORT CImage : public CComponent
        {

        public:

            CImage(const std::string & name);

            void SetTexture(const std::string & texture);

            void Draw();


        private:

            UTILS::ptr<CORE::ITexture>::ResourcePtr _image;
            UTILS::ptr<MODEL::IStaticModel>::ResourcePtr _square;
        };
    }
}

#endif
