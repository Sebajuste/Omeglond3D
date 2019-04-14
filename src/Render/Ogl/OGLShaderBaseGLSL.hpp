#ifndef _DEF_OMEGLOND3D_OGLSHADERBASEGLSL_HPP
#define _DEF_OMEGLOND3D_OGLSHADERBASEGLSL_HPP

#include "../../Core/CShaderBase.hpp"
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLShaderBaseGLSL : public CORE::CShaderBase
        {

        public:

            OGLShaderBaseGLSL(const std::string & name, const CORE::ShaderType & type);

            ~OGLShaderBaseGLSL();

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
