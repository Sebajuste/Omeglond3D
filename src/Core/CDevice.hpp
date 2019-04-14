#ifndef _DEF_OMEGLOND3D_IDEVICE_HPP
#define _DEF_OMEGLOND3D_IDEVICE_HPP

#include "../Exception/OmglException.hpp"
#include "../Utils/Export.hpp"

#include "../Interface/CInterfaceManager.hpp"

namespace OMGL3D
{
    namespace CORE {
        class IVideoDriver;
    }

    enum VideoRender {
        OMGL_SOFTWARE,
        OMGL_OPENGL2,
        OMGL_OPENGL3,
        OMGL_DIRECTX
    };

    class EXPORT CDevice
    {

    public:
        virtual ~CDevice();

        static CDevice * CreateDevice(int width, int height, const VideoRender &render) throw(EXCP::OMGLException);

        static CDevice * CreateDevice(int width, int height, const std::string & render) throw(EXCP::OMGLException);

        static CDevice * GetDevice();

        virtual CORE::IVideoDriver * GetVideoDriver()=0;

        UI::CInterfaceManager * CreateInterfaceManager();


    protected:

        CDevice();

    private:

        //UI::CInterfaceManager _interface;

    };


}

#endif
