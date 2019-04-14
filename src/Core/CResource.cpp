#include "CResource.hpp"

#include "CResourceManager.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CResource::CResource() : IResource(), _name(""), _counter(1)
        {
        }

        CResource::CResource(const std::string & name) : _name(name), _counter(1)
        {
        }

        CResource::~CResource()
        {
            CResourceManager::GetInstance().RemoveResource(_name);
        }

        std::string CResource::GetName() const
        {
            return _name;
        }

        void CResource::SetName(const std::string & name)
        {
            _name = name;
        }

        void CResource::AddRef()
        {
            _counter++;
        }

        unsigned int CResource::GetCount() const
        {
            return _counter;
        }

        void CResource::Release()
        {
            _counter--;
            if( _counter == 0)
            {
                delete this;
            }
        }
    }
}
