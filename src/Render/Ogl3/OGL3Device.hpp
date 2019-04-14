#ifndef _DEF_OMEGLOND3D_OGL3DEVIDE_HPP
#define _DEF_OMEGLOND3D_OGLD3EVIDE_HPP

//#include <boost/scoped_ptr.hpp>

#include "../../Core/CDevice.hpp"

namespace OMGL3D
{
    namespace CORE {
        class IVideoDriver;
    }

    namespace OGL3
    {
        class OGL3Device : public CDevice
        {

        public:

            OGL3Device();

            ~OGL3Device();

            CORE::IVideoDriver * GetVideoDriver();

        private:

            //boost::scoped_ptr<CORE::IVideoDriver> _videoDriver;
            CORE::IVideoDriver * _videoDriver;
        };
    }
}

#endif

