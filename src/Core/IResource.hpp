#ifndef _DEF_OMEGLOND3D_IRESOURCE_HPP
#define _DEF_OMEGLOND3D_IRESOURCE_HPP

#include <string>

namespace OMGL3D
{
    namespace CORE
    {
        class IResource
        {

        public:

            virtual ~IResource() {}

            virtual std::string GetName() const=0;

            virtual void SetName(const std::string & name)=0;

            virtual void AddRef()=0;

            virtual unsigned int GetCount() const=0;

            virtual void Release()=0;


        private:

            // copie interdite
            void operator=(IResource&);
        };
    }
}

#endif
