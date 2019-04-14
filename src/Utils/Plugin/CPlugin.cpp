#include "CPlugin.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        CPlugin::CPlugin() : _hndl(0)
        {
        }

        CPlugin::~CPlugin()
        {
            if( _hndl != NULL)
            {
                #if defined (WIN32)
                    FreeLibrary(_hndl);
                #else
                    dlclose(_hndl);
                #endif
            }
        }

        bool CPlugin::LoadLib(const std::string & lib) throw(EXCP::OMGLException)
        {
            if( _hndl != NULL) return true;

            #if defined (WIN32)
                _hndl = LoadLibrary(lib.c_str());
            #else
                _hndl = dlopen(lib.c_str(), RTLD_NOW | RTLD_GLOBAL);
            #endif
            if( _hndl == NULL)
            {
                #if defined (WIN32)
                    LPTSTR str_error;
                    DWORD dwLastError = GetLastError();
                    FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        dwLastError,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR)&str_error,
                        0, NULL );

                #else
                    char * str_error = dlerror();
                #endif

                std::string message(str_error);
                throw EXCP::OMGLException("Error loading library "+message);
            }
            return false;
        }

        void * CPlugin::LoadFunction(const std::string & func) throw(EXCP::OMGLException)
        {
            PtrFunc pFunc = 0;

            #if defined (WIN32)
                pFunc = reinterpret_cast<PtrFunc>(GetProcAddress(_hndl, func.c_str()));
            #else
                pFunc = reinterpret_cast<PtrFunc>(dlsym(_hndl, func.c_str()));
            #endif

            if( pFunc == NULL)
            {
                #if defined (WIN32)
                    LPTSTR str_error;
                    DWORD dwLastError = GetLastError();
                    FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        dwLastError,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR)&str_error,
                        0, NULL );

                #else
                    char * str_error = dlerror();
                #endif

                std::string message(str_error);
                throw EXCP::OMGLException("Error loading function "+message);
            }

            _factory[func] = pFunc;
            return (void*)pFunc;
        }

        void * CPlugin::GetFunction(const std::string & name)
        {
            return (void*)_factory[name];
        }

        void * CPlugin::Call(const std::string & name)
        {
            return _factory[name]();
        }
    }
}
