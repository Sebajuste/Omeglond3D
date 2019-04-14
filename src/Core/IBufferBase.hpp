#ifndef _DEF_OMEGLOND3D_IBUFFERBASE_HPP
#define _DEF_OMEGLOND3D_IBUFFERBASE_HPP

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        enum BufferType {
            OMGL_BUFFER_VERTEX,
            OMGL_BUFFER_INDEX
        };

        class IBufferBase
        {

        public:

            IBufferBase(unsigned int size, unsigned int stride) : _size(size), _stride(stride) {}

            virtual ~IBufferBase() {}

            unsigned int GetSize() const
            {
                return _size;
            }

            unsigned int GetStride() const
            {
                return _stride;
            }

            virtual unsigned char * Lock(unsigned int offset, unsigned int size)=0;

            virtual const unsigned char * ConstLock(unsigned int offset, unsigned int size) const=0;

            virtual void Unlock() const=0;


        protected:

            unsigned int _size;
            unsigned int _stride;
        };

        typedef UTILS::SmartPtr<IBufferBase, UTILS::RefCountPtr> BufferBasePtr;
    }
}

#endif
