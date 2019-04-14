#include "OGL3BlendingParameter.hpp"

namespace OMGL3D
{
    namespace OGL3
    {

        GLenum BlendingFunc::OGLAlphaMode[] =
        {
            GL_EQUAL,
            GL_GREATER
        };

        GLenum BlendingFunc::OGLBlendingMode[] =
        {
            GL_ZERO,
            GL_ONE,
            GL_DST_COLOR,
            GL_SRC_COLOR,
            GL_ONE_MINUS_DST_COLOR,
            GL_ONE_MINUS_SRC_COLOR,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            GL_DST_ALPHA,
            GL_ONE_MINUS_DST_ALPHA,
            GL_SRC_ALPHA_SATURATE
        };
    }
}
