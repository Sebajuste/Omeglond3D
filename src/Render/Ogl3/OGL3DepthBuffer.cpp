#include "OGL3DepthBuffer.hpp"

#define GL3_PROTOTYPES 1

#include <GL3/gl3.h>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3DepthBuffer::OGL3DepthBuffer() : CORE::IDepthBuffer("depth_buffer")
        {
            glEnable(GL_DEPTH_TEST);
        }

        OGL3DepthBuffer::~OGL3DepthBuffer()
        {
        }

        void OGL3DepthBuffer::Clear()
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClearDepth(1.0f);
        }

        void OGL3DepthBuffer::Lock()
        {
            glDepthMask(GL_FALSE);
        }

        void OGL3DepthBuffer::Unlock()
        {
            glDepthMask(GL_TRUE);
        }

        void OGL3DepthBuffer::SetDepth(const CORE::DepthFunc &depth)
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

