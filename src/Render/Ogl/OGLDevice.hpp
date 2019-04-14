#ifndef _DEF_OMEGLOND3D_OGLDEVIDE_HPP
#define _DEF_OMEGLOND3D_OGLDEVIDE_HPP

//#include <boost/scoped_ptr.hpp>

#include "../../Core/CDevice.hpp"

namespace OMGL3D
{
    namespace CORE {
        class IVideoDriver;
    }

    namespace OGL
    {
        class OGLDevice : public CDevice
        {

        public:

            OGLDevice();

            ~OGLDevice();

            CORE::IVideoDriver * GetVideoDriver();

        private:

            //boost::scoped_ptr<CORE::IVideoDriver> _videoDriver;
            CORE::IVideoDriver * _videoDriver;
        };
    }
}

#endif
