#ifndef _DEF_OMEGLOND3D_POLICYPTR_HPP
#define _DEF_OMEGLOND3D_POLICYPTR_HPP

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        template <class C> class RefCountPtr
        {

        public:

            RefCountPtr();

            unsigned int GetCounter(C * ptr) const;

            C * Clone(C * ptr);

            void Release(C * ptr);

            void Swap(RefCountPtr &ptr);


        private:

            int *_counter;
        };

        template <class C> struct RefResourcePtr
        {
            unsigned int GetCounter(C * ptr) const;

            C * Clone(C * ptr);

            void Release(C * ptr);

            void Swap(RefResourcePtr &ptr);
        };



        template <class C> struct RefScopedPtr
        {
            RefScopedPtr();

            unsigned int GetCounter(C * ptr) const;

            C * Clone(C * ptr);

            void Release(C * ptr);

            void Swap(RefScopedPtr &ptr);
        };
    }
}

#include "PolicyPtr.tpp"

#endif
