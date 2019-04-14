#ifndef _DEF_OMEGLOND3D_DEBUGMEMORYMANAGER_HPP
#define _DEF_OMEGLOND3D_DEBUGMEMORYMANAGER_HPP

#include <string>
#include <map>
#include <stack>
#include <fstream>

namespace OMGL3D
{
    namespace DEBUG
    {
        struct Block
        {
            std::size_t size;
            std::string file;
            int line;
            bool array;
        };



        class MemoryManager
        {

        public:

            static MemoryManager & GetMemoryManager();

            void * Allocate(std::size_t size, const std::string &str, int line, bool array);

            void Desallocate(void * ptr, bool array);

            void NextDelete(const std::string &str, int line);


        private:

            MemoryManager();

            ~MemoryManager();

            void ReportLeaks();

            std::ofstream _file;

            typedef std::map<void*, Block> BlockMap;
            BlockMap _blocks;
            std::stack<Block> _deleteStack;

            static MemoryManager _instance;
        };
    }
}

#endif
