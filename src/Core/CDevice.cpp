#include "CDevice.hpp"

#include "CResourceManager.hpp"
#include "CMediaManager.hpp"

#include "../Render/Ogl/OGLDevice.hpp"

#include "../Utils/Logger/ILogger.hpp"
#include "../Utils/Plugin/CPlugin.hpp"
#include "../Utils/Ptr/SmartPtr.hpp"

#include "../Debug/DebugAllocation.hpp"

#if defined (WIN32)
    #include "../Render/Ogl/OGLDevice.hpp"
    #include "../Render/Ogl3/OGL3Device.hpp"
#endif

//#include <boost/scoped_ptr.hpp>

namespace OMGL3D
{
    //boost::scoped_ptr<UTILS::CPlugin> _plugin;
    //boost::scoped_ptr<CDevice> _instance;

    UTILS::ptr<UTILS::CPlugin>::SharedPtr _plugin;
    UTILS::ptr<CDevice>::SharedPtr _instance;

    CDevice::CDevice()
    {
        UTILS::ILogger::SetLogger(UTILS::OMGL_LOGGER_STANDART, UTILS::OMGL_LOGGER_CONSOLE);
        UTILS::ILogger::SetLogger(UTILS::OMGL_LOGGER_DEBUG, UTILS::OMGL_LOGGER_FILE);
        UTILS::ILogger::SetLogger(UTILS::OMGL_LOGGER_ERROR, UTILS::OMGL_LOGGER_FILE);
        UTILS::ILogger::SetLogger(UTILS::OMGL_LOGGER_RENDERER, UTILS::OMGL_LOGGER_FILE);
    }

    CDevice::~CDevice()
    {
        //UTILS::ILogger::destroyAll();
    }

    CDevice * CDevice::CreateDevice(int width, int height, const VideoRender &render) throw(EXCP::OMGLException)
    {
        PLUGIN_FUNCTION(CDevice*, RenderDevice)

        _instance = 0;
        _plugin = new UTILS::CPlugin();

        RenderDevice createRenderDevice = 0;

        switch(render)
        {
            case OMGL_SOFTWARE:
            {
                #if defined (WIN32)
                    _plugin->LoadLib("./SoftwareRender.dll");
                #else
                    _plugin->LoadLib("./libSoftwareRender.so");
                #endif
                createRenderDevice = (RenderDevice)_plugin->LoadFunction("createDevice");
                break;
            }

            case OMGL_OPENGL2:
            {
                #if defined (WIN32)
                    //_plugin->loadLibrary("./OGLRender.dll");
                    //_instance.reset(new OGL::OGLDevice());
                    _instance = new OGL::OGLDevice();
                    return _instance.GetPtr();

                #else
                    //_plugin->loadLibrary("./libOGLRender.so");
                    //_instance.reset(new OGL::OGLDevice());
                    _instance = new OGL::OGLDevice();
                    _instance->_interface.SetSize(width, height);
                    return _instance.GetPtr();
                #endif
                createRenderDevice = (RenderDevice)_plugin->LoadFunction("createDevice");
                break;
            }

            case OMGL_OPENGL3:
            {
                throw EXCP::OMGLException("DirectX render is not supported");
                #if defined (WIN32)
                    //_plugin->LoadLib("./OGL3Render.dll");
                    //_instance = new OGL3::OGL3Device();
                    return _instance.GetPtr();
                #else
                    _plugin->LoadLib("./libOGL3Render.so");
                #endif
                createRenderDevice = (RenderDevice)_plugin->LoadFunction("createDevice");
                //_instance = new OGL3::OGL3Device();
                //return _instance.GetPtr();
                break;
            }

            case OMGL_DIRECTX:
            {
                #if defined (WIN32)
                    _plugin->LoadLib("./DXRender.dll");
                    createRenderDevice = (RenderDevice)_plugin->LoadFunction("createDevice");
                #else
                    throw EXCP::OMGLException("DirectX render is not supported");
                #endif

                break;
            }
        }

        if( createRenderDevice == 0)
        {
            throw EXCP::OMGLException("Error loading render library");
        }

        //_instance.reset(createRenderDevice());
        _instance = createRenderDevice();

        return _instance.GetPtr();
    }

    CDevice * CDevice::CreateDevice(int width, int height, const std::string & render) throw(EXCP::OMGLException)
    {
        PLUGIN_FUNCTION(CDevice*, RenderDevice)

        //_instance.reset(0);
        //_plugin.reset(new UTILS::CPlugin());
        _instance = 0;
        _plugin = new UTILS::CPlugin();

        _plugin->LoadLib(render);
        RenderDevice createRenderDevice = (RenderDevice)_plugin->LoadFunction("createDevice");

        if( createRenderDevice == 0)
        {
            throw EXCP::OMGLException("Error loading render library");
        }

        //_instance.reset(createRenderDevice());
        _instance = createRenderDevice();
        return _instance.GetPtr();
    }

    CDevice * CDevice::GetDevice()
    {
        return _instance.GetPtr();
    }

    UI::CInterfaceManager * CDevice::CreateInterfaceManager()
    {
        return new UI::CInterfaceManager();
    }
}
