#ifndef _DEF_OMEGLOND3D_ISHADERBASE_HPP
#define _DEF_OMEGLOND3D_ISHADERBASE_HPP

#include "CResource.hpp"
#include "ECoreEnum.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class IShaderBase : public CResource
        {

        public:

            virtual ShaderType GetType() const=0;

            virtual void SetSource(const char * source)=0;

            virtual void Compile()=0;

            virtual void Enable()=0;

            virtual void Disable()=0;

            virtual void SetParameter(const std::string & name, const float * value)=0;


        protected:

            IShaderBase(const std::string & name) : CResource(name) {}

            virtual ~IShaderBase() {}
        };
    }
}

#endif
