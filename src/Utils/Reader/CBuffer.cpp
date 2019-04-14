#include "CBuffer.hpp"

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        CBuffer::CBuffer()
        {
        }

        CBuffer::CBuffer(const std::string & name) : _name(name)
        {
        }

        CBuffer::CBuffer(const CBuffer & buffer) : _name(buffer.GetName()), _buffer(buffer.GetBuffer())
        {
        }

        CBuffer::CBuffer(const std::string & name, const std::string & buffer) : _name(name), _buffer(buffer)
        {
        }

        CBuffer::~CBuffer()
        {
        }

        std::string CBuffer::GetName() const
        {
            return _name;
        }

        std::string CBuffer::GetBuffer() const
        {
            return _buffer;
        }
    }
}
