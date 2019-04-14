#include "OGL3ColorBuffer.hpp"

#define GL3_PROTOTYPES 1

#include <GL3/gl3.h>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3ColorBuffer::OGL3ColorBuffer() : CORE::IColorBuffer("color_buffer")
        {
        }

        OGL3ColorBuffer::~OGL3ColorBuffer()
        {
        }

        void OGL3ColorBuffer::Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        }

        void OGL3ColorBuffer::Lock()
        {
            glColorMask(false, false, false, false);
        }

        void OGL3ColorBuffer::Unlock()
        {
            glColorMask(true, true, true, true);
        }
    }
}

