#ifndef _DEF_OMEGLOND3D_CSHADERBASE_HPP
#define _DEF_OMEGLOND3D_CSHADERBASE_HPP

#include "IShaderBase.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CShaderBase : public IShaderBase
        {

        public:

            ShaderType GetType() const;

            virtual void SetSource(const char * source)=0;

            virtual void Compile()=0;

            virtual void Enable()=0;

            virtual void Disable()=0;

            virtual void SetParameter(const std::string & name, const float * value)=0;


        protected:

            CShaderBase(const std::string & name, const ShaderType & type);

            virtual ~CShaderBase();


            private:

            ShaderType _type;

        };
    }
}

#endif
