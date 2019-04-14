#include "OGL3BufferVertex.hpp"

#include "../../Utils/Logger/ILogger.hpp"

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3BufferVertex::OGL3BufferVertex(unsigned int size, unsigned int stride ) : CORE::IBufferBase(size, stride)
        {
            _datas = new unsigned char[size*stride];
        }

        OGL3BufferVertex::~OGL3BufferVertex()
        {
            delete[] _datas;
        }

        unsigned char * OGL3BufferVertex::Lock(unsigned int offset, unsigned int size)
        {
            unsigned char * buffer = reinterpret_cast<unsigned char*>(_datas);
            return buffer + offset;
        }

        const unsigned char * OGL3BufferVertex::ConstLock(unsigned int offset, unsigned int size) const
        {
            const unsigned char * buffer = reinterpret_cast<unsigned char*>(_datas);
            return buffer + offset;
        }

        void OGL3BufferVertex::Unlock() const
        {
        }

        const unsigned char * OGL3BufferVertex::GetBuffer() const
        {
            return _datas;
        }
    }
}
