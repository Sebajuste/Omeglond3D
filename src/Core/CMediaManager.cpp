#include "CMediaManager.hpp"

#include "../Debug/DebugAllocation.hpp"

#include "../Utils/Loader/Picture/TgaLoader.hpp"
#include "../Utils/Loader/Picture/BmpLoader.hpp"
#include "../Utils/Loader/Model/CObjLoader.hpp"
#include "../Utils/Loader/Shader/CShaderLoader.hpp"

#include <iostream>

namespace OMGL3D
{
    namespace CORE
    {
        CMediaManager::CMediaManager()
        {
            AddLoader(new UTILS::BmpLoader(), "bmp");
            AddLoader(new UTILS::TgaLoader(), "tga");
            AddLoader(new UTILS::CObjLoader(), "obj");
            AddLoader(new UTILS::CShaderLoader(), "vert");
            AddLoader(new UTILS::CShaderLoader(), "frag");
        }

        void CMediaManager::AddFilePath(const std::string & path)
        {
            _paths.push_back(path);
        }

        std::string CMediaManager::FindFilePath(const std::string & file) const throw(EXCP::ReadException)
        {
            for(PathFile::const_iterator it=_paths.begin(); it!=_paths.end(); ++it)
            {
                std::string name = (*it) + file;
                UTILS::CFile file(name);

                if( file.IsExists() )
                    return file.GetFullName();
            }

            throw EXCP::ReadException("file not found : " +file);
        }

        UTILS::CBuffer CMediaManager::FileReader::Read(const std::string & resource) throw(EXCP::ReadException)
        {
            UTILS::CFileReader fileReader;
            return fileReader.Read(resource, UTILS::OMGL_STREAM_BINARY);
        }
    }
}
