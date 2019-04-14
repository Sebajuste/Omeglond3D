#ifndef _DEF_OMEGLOND3D_OGLShaderGLSL_HPP
#define _DEF_OMEGLOND3D_OGLShaderGLSL_HPP

#include "../../Core/CShader.hpp"
//#include "OGLShaderBaseGLSL.hpp"
#include <GL/gl.h>

namespace OMGL3D
{
    namespace OGL
    {
        class OGLShaderBaseGLSL;

        class OGLShaderGLSL : public CORE::CShader
        {

        public:

            OGLShaderGLSL(const std::string & name, OGLShaderBaseGLSL * vertex_shader, OGLShaderBaseGLSL * pixel_shader);

            ~OGLShaderGLSL();

            void Enable();

            void Disable();

            void SetParameter(const std::string & name, const float & value);

            void SetParameter(const std::string & name, const int & value);


        private:

            GLuint _id;
        };
    }
}

#endif
