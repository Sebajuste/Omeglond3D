#include "MemoryManager.hpp"

#include "../Exception/WriteException.hpp"

#include <cstdlib>

namespace OMGL3D
{
    namespace DEBUG
    {
        MemoryManager::MemoryManager() : _file("leaks.log")
        {
            if( !_file) throw EXCP::WriteException("Failed to write leaks.log");
        }

        MemoryManager::~MemoryManager()
        {
            if( _blocks.empty() )
            {
                _file << "\n\n--- No memory leaks ---" << std::endl;
            }
            else
            {
                _file << "\n\n--- Memory leaks detected ---" << std::endl;
                ReportLeaks();
            }
            _file.close();
        }

        MemoryManager & MemoryManager::GetMemoryManager()
        {
            return _instance;
        }

        void * MemoryManager::Allocate(std::size_t size, const std::string &str, int line, bool array)
        {
            void * ptr = malloc(size);

            Block block;
            block.size = size;
            block.file = str;
            block.line = line;
            block.array = array;
            _blocks[ptr] = block;

            _file << "New allocation  " << ptr << " | " << size << " octets | " << str << " line " << line << std::endl;

            return ptr;
        }

        void MemoryManager::Desallocate(void * ptr, bool array)
        {
            BlockMap::iterator it = _blocks.find(ptr);

            if( it == _blocks.end() )
            {
                free(ptr);
                return;
            }

            if( it->second.array != array )
            {
                _file << "Bad delete " << ptr << " | " << it->second.size << " octets | " << it->second.file << " line " << it->second.line << std::endl;
                return;
            }

            _file << "Delete          " << ptr << " | " << it->second.size << " octets | " << it->second.file << " line " << it->second.line << std::endl;

            _blocks.erase(it);
            _deleteStack.pop();

            free(ptr);
        }

        void MemoryManager::NextDelete(const std::string &str, int line)
        {
            Block b_delete;
            b_delete.file = str;
            b_delete.line = line;
            _deleteStack.push(b_delete);
        }

        void MemoryManager::ReportLeaks()
        {
            std::size_t size = 0;
            BlockMap::iterator it;
            for(it = _blocks.begin(); it!=_blocks.end(); ++it)
            {
                size += it->second.size;
                _file << it->first << " | " << it->second.size << " octets | " << it->second.file << ", line " << it->second.line << std::endl;
                free(it->first);
            }

            _file << _blocks.size() << " blocks not free, " << size << " octets" << std::endl;
        }

        MemoryManager MemoryManager::_instance;
    }
}
