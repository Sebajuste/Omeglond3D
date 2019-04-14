#ifndef _DEF_OMEGLOND3D_CRESOURCE_HPP
#define _DEF_OMEGLOND3D_CRESOURCE_HPP

#include "IResource.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class CResource : public IResource
        {

        public:

            virtual ~CResource();

            std::string GetName() const;

            void SetName(const std::string & name);

            void AddRef();

            unsigned int GetCount() const;

            void Release();



        protected:

            CResource();

            CResource(const std::string &name);



        private:

            //friend class ResourceManager;

            std::string _name;
            unsigned int _counter;

            CResource(const CResource &);

            void operator=(const CResource&);
        };
    }
}

#endif
