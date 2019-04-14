#ifndef _DEF_OMEGLOND3D_SMARTPTR_HPP
#define _DEF_OMEGLOND3D_SMARTPTR_HPP

#include "../../Debug/DebugAllocation.hpp"

#include "PolicyPtr.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        template <class C, template <class> class Ownership>
        class SmartPtr : private Ownership<C>
        {

        public:

            SmartPtr();

            SmartPtr(const SmartPtr & copy);

            SmartPtr(C * ptr);

            virtual ~SmartPtr();

            C * GetPtr() const;

            unsigned int Count() const;

            C & operator*();

            C * operator->();

            const SmartPtr & operator=(SmartPtr & ptr);

            const SmartPtr & operator=(C * ptr);

            bool operator==(SmartPtr & ptr) const;

            bool operator==(C * ptr) const;

            operator C*() const;


        protected:

            void Swap(SmartPtr &ptr);

            C * _ptr;
        };

        template <class C> struct ptr
        {
            typedef SmartPtr<C, RefCountPtr> SharedPtr;
            typedef SmartPtr<C, RefResourcePtr> ResourcePtr;
        };
    }
}

#include "SmartPtr.tpp"

#endif
