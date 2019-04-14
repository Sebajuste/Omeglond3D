#include "OGLDepthBuffer.hpp"

#include <GL/gl.h>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLDepthBuffer::OGLDepthBuffer() : CORE::IDepthBuffer("depth_buffer")
        {
            glEnable(GL_DEPTH_TEST);
        }

        OGLDepthBuffer::~OGLDepthBuffer()
        {
        }

        void OGLDepthBuffer::Clear()
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClearDepth(1.0f);
        }

        void OGLDepthBuffer::Lock()
        {
            glDepthMask(GL_FALSE);
        }

        void OGLDepthBuffer::Unlock()
        {
            glDepthMask(GL_TRUE);
        }

        void OGLDepthBuffer::SetDepth(const CORE::DepthFunc &depth)
        {
            switch(depth)
            {
                case CORE::OMGL_DEPTH_EQUAL:
                    glDepthFunc(GL_EQUAL);
                    break;

                case CORE::OMGL_DEPTH_LESS:
                    glDepthFunc(GL_LESS);
                    break;
            }
        }
    }
}
