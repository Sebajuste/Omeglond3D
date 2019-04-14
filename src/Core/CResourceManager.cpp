#include "CResourceManager.hpp"

#include "../Debug/DebugAllocation.hpp"

#include "../Utils/Logger/ILogger.hpp"

#include "IResource.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CResourceManager::CResourceManager()
        {
        }

        CResourceManager::~CResourceManager()
        {
            if( !_resources.empty() )
            {
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : Warning ! Resources not deleted" << UTILS::OMGL_LOGGER_ENDL;

                ResourcesMap::const_iterator it;
                for(it = _resources.begin(); it!=_resources.end(); ++it)
                {
                    UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << " -> " << it->second->GetName() << UTILS::OMGL_LOGGER_ENDL;
                }
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << UTILS::OMGL_LOGGER_FLUSH;
            }
        }

        void CResourceManager::AddResource(const std::string &key, IResource * resource)
        {
            if( resource == 0 )
            {
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : attempt add resource NULL " << key << UTILS::OMGL_LOGGER_FLUSH;
                return;
            }

            // if the resource already exist
            if( _resources.find(key) != _resources.end() )
            {
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_DEBUG) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : " << key << " : is already loaded" << UTILS::OMGL_LOGGER_FLUSH;
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : " << key << " : is already loaded" << UTILS::OMGL_LOGGER_FLUSH;
            }

            _resources[key] = resource;
            resource->SetName(key);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_DEBUG) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : resource " << key << " added" << UTILS::OMGL_LOGGER_FLUSH;
        }

        void CResourceManager::RemoveResource(const std::string &key)
        {

            ResourcesMap::iterator it = _resources.find(key);

            // if the resource does not found
            if( it == _resources.end() )
            {
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_ERROR) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : error delete : resource " << key << " was not loaded" << UTILS::OMGL_LOGGER_FLUSH;
                return;
            }
            _resources.erase(it);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_DEBUG) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] ResourceManager : resource " << key << " has been delete" << UTILS::OMGL_LOGGER_FLUSH;
        }

        IResource * CResourceManager::GetResource(const std::string & key) const throw(EXCP::PointerNullException)
        {
            ResourcesMap::const_iterator it = _resources.find(key);

            // if the resource does not exist
            if( it == _resources.end() ) {
                throw EXCP::PointerNullException("resource null: "+key);
            }

            it->second->AddRef();
            return it->second;
        }
    }
}
