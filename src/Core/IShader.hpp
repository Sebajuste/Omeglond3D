#ifndef _DEF_OMEGLOND3D_ISHADER_HPP
#define _DEF_OMEGLOND3D_ISHADER_HPP

#include "CResource.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class IShaderBase;

        class IShader : public CResource
        {

        public:

            IShader(const std::string & name) : CResource(name) {}

            ~IShader() {}

            virtual IShaderBase * GetVertexShader()=0;

            virtual IShaderBase * GetPixelShader()=0;

            virtual void Enable()=0;

            virtual void Disable()=0;

            virtual void SetParameter(const std::string & name, const float & value)=0;

            virtual void SetParameter(const std::string & name, const int & value)=0;
        };
    }
}

#endif
