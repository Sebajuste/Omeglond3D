#ifndef _DEF_OMEGLOND3D_SINGLETON_HPP
#define _DEF_OMEGLOND3D_SINGLETON_HPP

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        template <typename T> class Singleton
        {

        public:

            static T & GetInstance();

            static void Destroy();



        protected:

            Singleton();

            virtual ~Singleton();



        private:

            Singleton(Singleton&);

            void operator=(Singleton&);

            struct Life {
                ~Life();
            };

            static T * m_Instance;
            static Life m_Life;
        };

    } // end namespace UTILS
} // end namespace OMGL

#include "Singleton.inl"

#endif
