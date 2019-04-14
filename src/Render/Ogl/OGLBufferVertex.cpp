#include "OGLBufferVertex.hpp"

#include "../../Utils/Logger/ILogger.hpp"

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLBufferVertex::OGLBufferVertex(unsigned int size, unsigned int stride ) : CORE::IBufferBase(size, stride)
        {
            _datas = new unsigned char[size*stride];
        }

        OGLBufferVertex::~OGLBufferVertex()
        {
            delete[] _datas;
        }

        unsigned char * OGLBufferVertex::Lock(unsigned int offset, unsigned int size)
        {
            unsigned char * buffer = reinterpret_cast<unsigned char*>(_datas);
            return buffer + offset;
        }

        const unsigned char * OGLBufferVertex::ConstLock(unsigned int offset, unsigned int size) const
        {
            const unsigned char * buffer = reinterpret_cast<unsigned char*>(_datas);
            return buffer + offset;
        }

        void OGLBufferVertex::Unlock() const
        {
        }

        const unsigned char * OGLBufferVertex::GetBuffer() const
        {
            return _datas;
        }
    }
}
