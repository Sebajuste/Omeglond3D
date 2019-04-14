#include "OGLColorBuffer.hpp"

#include <GL/gl.h>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLColorBuffer::OGLColorBuffer() : CORE::IColorBuffer("color_buffer")
        {
        }

        OGLColorBuffer::~OGLColorBuffer()
        {
        }

        void OGLColorBuffer::Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        }

        void OGLColorBuffer::Lock()
        {
            glColorMask(false, false, false, false);
        }

        void OGLColorBuffer::Unlock()
        {
            glColorMask(true, true, true, true);
        }
    }
}
