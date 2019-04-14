#ifndef _DEF_OMEGLOND3D_OGL3SHADERBASEGLSL_HPP
#define _DEF_OMEGLOND3D_OGL3SHADERBASEGLSL_HPP

#include "../../Core/CShaderBase.hpp"

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3ShaderBaseGLSL : public CORE::CShaderBase
        {

        public:

            OGL3ShaderBaseGLSL(const std::string & name, const CORE::ShaderType & type);

            ~OGL3ShaderBaseGLSL();

            void SetSource(const char * source);

            void Compile();

            void Enable();

            void Disable();

            void SetParameter(const std::string & name, const float * value);

            GLuint GetId() const;


        private:

            GLuint _id;
        };
    }
}

#endif
