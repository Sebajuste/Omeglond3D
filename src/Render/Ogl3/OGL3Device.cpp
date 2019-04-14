#include "OGL3Device.hpp"

#include "OGL3VideoDriver.hpp"
#include "OGL3Extention.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3Device::OGL3Device()
        {
            //_videoDriver.reset(new OMGL3D::OGL::OGLVideoDriver());
            _videoDriver = new OMGL3D::OGL3::OGL3VideoDriver();
            OGL3Extention::GetInstance().CheckExtentions();
            OGL3Extention::GetInstance().LoadAllExtention();
        }

        OGL3Device::~OGL3Device()
        {
            delete _videoDriver;
        }

        CORE::IVideoDriver * OGL3Device::GetVideoDriver()
        {
            //return _videoDriver.get();
            return _videoDriver;
        }
/*
        extern "C"
        {
            OGL3Device * CreateDevice()
            {
                return new OGL3Device();
            }
        }
        */
    }
}

