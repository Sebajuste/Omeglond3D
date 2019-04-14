#include "OGLDevice.hpp"

#include "OGLVideoDriver.hpp"
#include "OGLExtention.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace OGL
    {
        OGLDevice::OGLDevice()
        {
            //_videoDriver.reset(new OMGL3D::OGL::OGLVideoDriver());
            _videoDriver = new OMGL3D::OGL::OGLVideoDriver();
            OGLExtention::GetInstance().CheckExtentions();
            OGLExtention::GetInstance().LoadAllExtention();
        }

        OGLDevice::~OGLDevice()
        {
            delete _videoDriver;
        }

        CORE::IVideoDriver * OGLDevice::GetVideoDriver()
        {
            //return _videoDriver.get();
            return _videoDriver;
        }

        extern "C"
        {
            OGLDevice * CreateDevice()
            {
                return new OGLDevice();
            }
        }
    }
}
