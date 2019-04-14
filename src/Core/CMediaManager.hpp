#ifndef _DEF_OMEGLOND3D_MEDIAMANAGER_HPP
#define _DEF_OMEGLOND3D_MEDIAMANAGER_HPP

#include <string>
#include <map>
#include <vector>

#include <fstream>

#include "CPicture.hpp"
#include "CResourceManager.hpp"

#include "../Model/IStaticModel.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"
#include "../Utils/Loader/ILoader.hpp"
#include "../Utils/Logger/ILogger.hpp"
#include "../Utils/Pattern/GenHierarchy.hpp"
#include "../Utils/Reader/CFileReader.hpp"
#include "../Utils/Reader/CFile.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        template <class C> struct Media
        {
            typedef std::map<std::string, UTILS::SmartPtr<UTILS::ILoader<C>, UTILS::RefCountPtr> > LoadersMap;
            LoadersMap loaders;
        };

        typedef TYPELIST_3(char, CPicture, MODEL::IStaticModel) ListMedias;

        class CMediaManager : public UTILS::Singleton<CMediaManager>, UTILS::Hierarchy<ListMedias, Media>
        {

        public:

            CMediaManager();

            void AddFilePath(const std::string &path);

            std::string FindFilePath(const std::string & file) const throw(EXCP::ReadException);

            template <class C> void AddLoader(UTILS::ILoader<C> * loader, const std::string & ext);

            template <class C> C * LoadFromFile(const std::string &resource) throw(EXCP::ReadException);


        private:

            typedef std::vector<std::string> PathFile;
            PathFile _paths;

            template <class C, class Reader> C * Load(const std::string & resource);


            struct FileReader
            {
                static UTILS::CBuffer Read(const std::string & resource) throw(EXCP::ReadException);
            };
        };

        template <class C> void CMediaManager::AddLoader(UTILS::ILoader<C> * loader, const std::string & ext)
        {
            Media<C>::loaders[ext] = loader;
        }

        template <class C> C * CMediaManager::LoadFromFile(const std::string & resource) throw(EXCP::ReadException)
        {
            std::string filePath = FindFilePath(resource);
            return Load<C, FileReader>(filePath);
        }

        template <class C, class Reader> C * CMediaManager::Load(const std::string & resource)
        {
            int ext_pos = resource.find_last_of(".");
            std::string ext = resource.substr(ext_pos+1);

            UTILS::CBuffer buffer = Reader::Read(resource);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_DEBUG) << "[" << UTILS::ILogger::GetCurrentDate() << " " << UTILS::ILogger::GetCurrentTime() << "] Media Manager : buffer read for " << resource << UTILS::OMGL_LOGGER_FLUSH;

            if( Media<C>::loaders.find(ext) != Media<C>::loaders.end() )
            {
                UTILS::ILoader<C> * loader = Media<C>::loaders[ext];
                C * c = loader->Load(buffer);
                return c;
            }

            return 0;
        }
    }
}

#endif
