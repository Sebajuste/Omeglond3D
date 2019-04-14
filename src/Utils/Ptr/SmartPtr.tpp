namespace OMGL3D
{
    namespace UTILS
    {
        template <class C, template <class> class Ownership> SmartPtr<C, Ownership>::SmartPtr() : _ptr(0)
        {
        }

        template <class C, template <class> class Ownership> SmartPtr<C, Ownership>::SmartPtr(const SmartPtr<C, Ownership> &copy) : Ownership<C>(copy), _ptr(Ownership<C>::Clone(copy._ptr))
        {
        }

        template <class C, template <class> class Ownership> SmartPtr<C, Ownership>::SmartPtr(C * ptr) : _ptr(ptr)
        {
        }

        template <class C, template <class> class Ownership> SmartPtr<C, Ownership>::~SmartPtr()
        {
            Ownership<C>::Release(_ptr);
        }

        template <class C, template <class> class Ownership> C * SmartPtr<C, Ownership>::GetPtr() const
        {
            return _ptr;
        }

        template <class C, template <class> class Ownership> unsigned int SmartPtr<C, Ownership>::Count() const
        {
            return Ownership<C>::GetCounter(_ptr);
        }

        template <class C, template <class> class Ownership> void SmartPtr<C, Ownership>::Swap(SmartPtr<C, Ownership> &ptr)
        {
            Ownership<C>::Swap(ptr);
            std::swap(_ptr, ptr._ptr);
        }

        template <class C, template <class> class Ownership> C & SmartPtr<C, Ownership>::operator*()
        {
            return *_ptr;
        }

        template <class C, template <class> class Ownership> C * SmartPtr<C, Ownership>::operator->()
        {
            return _ptr;
        }

        template <class C, template <class> class Ownership> const SmartPtr<C, Ownership> & SmartPtr<C, Ownership>::operator=(SmartPtr<C, Ownership> &ptr)
        {
            SmartPtr<C, Ownership>(ptr).Swap(*this);
            return *this;
        }

        template <class C, template <class> class Ownership> const SmartPtr<C, Ownership> & SmartPtr<C, Ownership>::operator=(C * ptr)
        {
            if ( _ptr != ptr)
            {
                SmartPtr<C, Ownership>(ptr).Swap(*this);
            }
            return *this;
        }

        template <class C, template <class> class Ownership> bool SmartPtr<C, Ownership>::operator==(SmartPtr & ptr) const
        {
            return _ptr == ptr._ptr ? true : false;
        }

        template <class C, template <class> class Ownership> bool SmartPtr<C, Ownership>::operator==(C * ptr) const
        {
            return _ptr == ptr ? true : false;
        }

        template <class C, template <class> class Ownership> SmartPtr<C, Ownership>::operator C*() const
        {
            return _ptr;
        }
    }
}
