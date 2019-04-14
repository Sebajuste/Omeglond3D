#include "CInterfaceManager.hpp"

#include "../Core/CDevice.hpp"
#include "../Core/IVideoDriver.hpp"

#include "CFrame.hpp"
#include "CLabel.hpp"
#include "CImage.hpp"

namespace OMGL3D
{
    namespace UI
    {
        CInterfaceManager::CInterfaceManager() : _width(0), _height(0)
        {

        }

        CFrame * CInterfaceManager::CreateFrame(const std::string & name)
        {
            return new CFrame(name);
        }

        CLabel * CInterfaceManager::CreateLabel(const std::string & name)
        {
            return new CLabel(name);
        }

        CImage * CInterfaceManager::CreateImage(const std::string & name)
        {
            return new CImage(name);
        }

        void CInterfaceManager::SetSize(unsigned int width, unsigned int heigth)
        {
            _width = width;
            _height = heigth;
        }

        void CInterfaceManager::AddComponent(CComponent * component)
        {
            _list_component.push_back(component);
        }

        CComponent * CInterfaceManager::GetComponent(const std::string & name)
        {
            std::vector<UTILS::ptr<CComponent>::SharedPtr>::iterator it;

            for(it=_list_component.begin(); it!=_list_component.end(); ++it)
            {
                if( (*it)->GetName() == name )
                {
                    return *it;
                }
            }
            return 0;
        }

        void CInterfaceManager::RemoveComponent(const std::string & name)
        {
            std::vector<UTILS::ptr<CComponent>::SharedPtr>::iterator it;

            for(it=_list_component.begin(); it!=_list_component.end(); ++it)
            {
                if( (*it)->GetName() == name )
                {
                    _list_component.erase(it);
                }
            }
        }

        void CInterfaceManager::Clear()
        {
            _list_component.clear();
        }

        void CInterfaceManager::OnEvent(const MouseEvent & event)
        {
            std::vector<UTILS::ptr<CComponent>::SharedPtr>::iterator it;

            for(it=_list_component.begin(); it!=_list_component.end(); ++it)
            {
                (*it)->OnEvent(event);
            }
        }

        void CInterfaceManager::Draw()
        {
            CDevice::GetDevice()->GetVideoDriver()->LoadMatrix(MATH::Matrix4f::CreateOrthoMatrix(0, _width, _height, 0, -1, 1), CORE::OMGL_MATRIX_PROJECTION);

            std::vector<UTILS::ptr<CComponent>::SharedPtr>::iterator it;

            for(it=_list_component.begin(); it!=_list_component.end(); ++it)
            {
                (*it)->Draw();
            }
        }
    }
}
