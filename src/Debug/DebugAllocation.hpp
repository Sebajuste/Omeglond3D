#ifdef OMGL3D_DEBUG

#ifndef _DEF_OMEGLOND3D_DEBUGALLOCATION_HPP
#define _DEF_OMEGLOND3D_DEBUGALLOCATION_HPP


#include "MemoryManager.hpp"

inline void * operator new(std::size_t size, const char* file, int line)
{
    return OMGL3D::DEBUG::MemoryManager::GetMemoryManager().Allocate(size, file, line, false);
}

inline void * operator new[](std::size_t size, const char* file, int line)
{
    return OMGL3D::DEBUG::MemoryManager::GetMemoryManager().Allocate(size, file, line, true);
}

inline void operator delete(void * ptr) throw()
{
    OMGL3D::DEBUG::MemoryManager::GetMemoryManager().Desallocate(ptr, false);
}

inline void operator delete[](void * ptr) throw()
{
    OMGL3D::DEBUG::MemoryManager::GetMemoryManager().Desallocate(ptr, true);
}

#ifndef __BORLANDC__

inline void operator delete(void * ptr, const char * file, int line) throw()
{
    OMGL3D::DEBUG::MemoryManager::GetMemoryManager().NextDelete(file, line);
    OMGL3D::DEBUG::MemoryManager::GetMemoryManager().Desallocate(ptr, false);
}

inline void operator delete[](void * ptr, const char * file, int line) throw()
{
    OMGL3D::DEBUG::MemoryManager::GetMemoryManager().NextDelete(file, line);
    OMGL3D::DEBUG::MemoryManager::GetMemoryManager().Desallocate(ptr, true);
}

#endif // __BORLANDC__

#endif // _DEF_OMEGLOND3D_DEBUGALLOCATION_HPP

#ifndef new
    #define new new(__FILE__, __LINE__)
    #define delete OMGL3D::DEBUG::MemoryManager::GetMemoryManager().NextDelete(__FILE__, __LINE__), delete
#endif

#endif  // _DEBUG
