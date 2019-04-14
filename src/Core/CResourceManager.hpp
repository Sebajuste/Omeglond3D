#ifndef _DEF_OMEGLOND3D_RESOURCEMANAGER_HPP
#define _DEF_OMEGLOND3D_RESOURCEMANAGER_HPP

#include "../Utils/Pattern/Singleton.hpp"

#include "../Exception/PointerNullException.hpp"

#include <string>
#include <map>

namespace OMGL3D
{
    namespace CORE
    {
        class IResource;

        class CResourceManager : public UTILS::Singleton<CResourceManager>
        {

        public:

            void AddResource(const std::string &key, IResource *resource);

            void RemoveResource(const std::string &key);

            template <class C> C * GetResource(const std::string & key) const throw(EXCP::PointerNullException);


        private:

            IResource * GetResource(const std::string & key) const throw(EXCP::PointerNullException);

            friend class UTILS::Singleton<CResourceManager>;

            ~CResourceManager();

            CResourceManager();

            typedef std::map<std::string, IResource*> ResourcesMap;

            ResourcesMap _resources;
        };

        template <class C> C * CResourceManager::GetResource(const std::string & key) const throw(EXCP::PointerNullException)
        {
            return dynamic_cast<C*>( GetResource(key) );
        }
    }
}

#endif
