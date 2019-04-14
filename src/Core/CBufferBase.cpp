#include "CBufferBase.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CBufferBase::CBufferBase(unsigned int size, unsigned int stride) : IBufferBase(size, stride)
        {
            _datas = new unsigned char[size*stride];
        }

        CBufferBase::~CBufferBase()
        {
            delete[] _datas;
        }

        unsigned char * CBufferBase::Lock(unsigned int offset, unsigned int size)
        {
            unsigned char * buffer = reinterpret_cast<unsigned char*>(_datas);
            return buffer + offset;
        }

        const unsigned char * CBufferBase::ConstLock(unsigned int offset, unsigned int size) const
        {
            unsigned char * buffer = reinterpret_cast<unsigned char*>(_datas);
            return buffer + offset;
        }

        void CBufferBase::Unlock() const
        {
        }
    }
}
