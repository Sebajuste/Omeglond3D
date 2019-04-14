#ifndef _DEF_OMEGLOND3D_OGL3ShaderGLSL_HPP
#define _DEF_OMEGLOND3D_OGL3ShaderGLSL_HPP

#include "../../Core/CShader.hpp"
#include "OGL3ShaderBaseGLSL.hpp"

#define GL3_PROTOTYPES 1

#include <GL3/gl3.h>

namespace OMGL3D
{
    namespace OGL3
    {
        class OGL3ShaderGLSL : public CORE::CShader
        {

        public:

            OGL3ShaderGLSL(const std::string & name, OGL3ShaderBaseGLSL * vertex_shader, OGL3ShaderBaseGLSL * pixel_shader);

            ~OGL3ShaderGLSL();

            void Enable();

            void Disable();

            void SetParameter(const std::string & name, const float & value);

            void SetParameter(const std::string & name, const int & value);


        private:

            GLuint _id;

            GLuint m_MatrixID;

            GLuint m_VertexPositionID;
            GLuint m_VertexNormalID;
            GLuint m_VertexColorID;
            GLuint m_VertexTexCoordID;
        };
    }
}

#endif
