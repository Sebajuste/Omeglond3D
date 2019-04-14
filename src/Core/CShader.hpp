#ifndef _DEF_OMEGLOND3D_CSHADER_HPP
#define _DEF_OMEGLOND3D_CSHADER_HPP

#include "IShader.hpp"
#include "IShaderBase.hpp"
#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CShader : public IShader
        {

        public:

            CShader(const std::string & name);

            virtual ~CShader();

            IShaderBase * GetVertexShader();

            IShaderBase * GetPixelShader();

            virtual void Enable()=0;

            virtual void Disable()=0;

            virtual void SetParameter(const std::string & name, const float & value)=0;

            virtual void SetParameter(const std::string & name, const int & value)=0;


        protected:

            UTILS::ptr<IShaderBase>::ResourcePtr _vertexShader;
            UTILS::ptr<IShaderBase>::ResourcePtr _pixelShader;
        };
    }
}

#endif
