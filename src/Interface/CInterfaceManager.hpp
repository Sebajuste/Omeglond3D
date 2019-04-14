#ifndef _DEF_OMEGLOND3D_CINTERFACEMANAGER_HPP
#define _DEF_OMEGLOND3D_CINTERFACEMANAGER_HPP

#include "CComponent.hpp"
#include "IEvent.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"
#include "../Utils/Export.hpp"

#include <vector>

namespace OMGL3D
{
    namespace UI
    {
        class CFrame;
        class CLabel;
        class CImage;

        class EXPORT CInterfaceManager
        {

        public:

            CInterfaceManager();

            static CFrame * CreateFrame(const std::string & name);

            static CLabel * CreateLabel(const std::string & name);

            static CImage * CreateImage(const std::string & name);

            void SetSize(unsigned int width, unsigned int heigth);

            void AddComponent(CComponent * component);

            CComponent * GetComponent(const std::string & name);

            void RemoveComponent(const std::string & name);

            void Clear();

            void OnEvent(const MouseEvent & event);

            void Draw();


        private:

            std::vector<UTILS::ptr<CComponent>::SharedPtr> _list_component;
            unsigned int _width, _height;
        };
    }
}

#endif
