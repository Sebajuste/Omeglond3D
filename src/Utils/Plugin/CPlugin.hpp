#ifndef _DEF_PLUGIN_HPP
#define _DEF_PLUGIN_HPP

#include "../../Exception/OmglException.hpp"

#include <string>
#include <map>

#if defined (WIN32)
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

#define PLUGIN_FUNCTION(type, name) typedef type (*name)();
#define PLUGIN_FUNCTION1(type, name, arg1) typedef type (*name)(arg1);
#define PLUGIN_FUNCTION2(type, name, arg1, arg2) typedef type (*name)(arg1, arg2);

namespace OMGL3D
{
    namespace UTILS
    {

        class CPlugin
        {

        public:

            //----------------------------------------------------------
            // Default Constructor
            //----------------------------------------------------------
            CPlugin();

            //----------------------------------------------------------
            // Destrucor
            //----------------------------------------------------------
            ~CPlugin();

            //----------------------------------------------------------
            // Load library and return statement
            //----------------------------------------------------------
            bool LoadLib(const std::string & lib) throw(EXCP::OMGLException);

            //----------------------------------------------------------
            // Load function and return the function address
            //----------------------------------------------------------
            void * LoadFunction(const std::string & func) throw(EXCP::OMGLException);

            //----------------------------------------------------------
            // Load all functions with their table name
            //----------------------------------------------------------
            template <std::size_t S> void LoadFunctions(const std::string (&tab)[S]);

            //----------------------------------------------------------
            // Return the function address function if it was already load
            //----------------------------------------------------------
            void * GetFunction(const std::string & name);

            //----------------------------------------------------------
            // Call function
            //----------------------------------------------------------
            void * Call(const std::string & name);


        private:

            //----------------------------------------------------------
            // Datas
            //----------------------------------------------------------
            typedef void * (*PtrFunc)();
            typedef std::map<std::string, PtrFunc, std::less<std::string> > Factory;

            #if defined (WIN32)
                HMODULE _hndl;
            #else
                void * _hndl;
            #endif
            Factory _factory;

            //----------------------------------------------------------
            // Copy is forbidden
            //----------------------------------------------------------
            CPlugin(const CPlugin & copy);

            void operator=(const CPlugin & copy);
        };

        template <std::size_t S> void CPlugin::LoadFunctions(const std::string (&tab)[S])
        {
            for(unsigned int index=0; index<S; ++index)
            {
                LoadFunction(tab[index]);
            }
        }
    }
}

#endif

