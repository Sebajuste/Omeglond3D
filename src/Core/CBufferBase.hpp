#ifndef _DEF_OMEGLOND3D_CBUFFERBASE_HPP
#define _DEF_OMEGLOND3D_CBUFFERBASE_HPP

#include "IBufferBase.hpp"

namespace OMGL3D
{
        namespace CORE
        {
            class CBufferBase : public IBufferBase
            {
                public:

                CBufferBase(unsigned int size, unsigned int stride);

                ~CBufferBase();

                unsigned char * Lock(unsigned int offset, unsigned int size);

                const unsigned char * ConstLock(unsigned int offset, unsigned int size) const;

                void Unlock() const;

                private:

                unsigned char * _datas;
            };
        }
}

#endif
