#include <iostream>

namespace OMGL3D
{
    namespace UTILS
    {
        template <class C> RefCountPtr<C>::RefCountPtr() : _counter(new int(1))
        {
        }

        template <class C> unsigned int RefCountPtr<C>::GetCounter(C * ptr) const
        {
            return *_counter;
        }

        template <class C> C * RefCountPtr<C>::Clone(C * ptr)
        {
            ++*_counter;
            return ptr;
        }

        template <class C> void RefCountPtr<C>::Release(C * ptr)
        {
            if( --*_counter == 0)
            {
                delete _counter;
                delete ptr;
            }
        }

        template <class C> void RefCountPtr<C>::Swap(RefCountPtr<C> & ptr)
        {
            std::swap(_counter, ptr._counter);
        }



        template <class C> unsigned int RefResourcePtr<C>::GetCounter(C * ptr) const
        {
            return ptr->GetCount();
        }

        template <class C> C * RefResourcePtr<C>::Clone(C * ptr)
        {
            if( ptr != 0)
            {
                ptr->AddRef();
            }
            return ptr;
        }

        template <class C> void RefResourcePtr<C>::Release(C * ptr)
        {
            if( ptr != 0)
            {
                ptr->Release();
            }
        }

        template <class C> void RefResourcePtr<C>::Swap(RefResourcePtr &ptr)
        {
        }



        template <class C> RefScopedPtr<C>::RefScopedPtr()
        {
        }

        template <class C> unsigned int RefScopedPtr<C>::GetCounter(C * ptr) const
        {
            return 1;
        }

        template <class C> C * RefScopedPtr<C>::Clone(C * ptr)
        {
        }

        template <class C> void RefScopedPtr<C>::Release(C * ptr)
        {
            delete ptr;
        }

        template <class C> void RefScopedPtr<C>::Swap(RefScopedPtr &ptr)
        {
        }

    }
}
