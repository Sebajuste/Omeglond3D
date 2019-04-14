#ifndef _DEF_OMEGLOND3D_CFRAME_HPP
#define _DEF_OMEGLOND3D_CFRAME_HPP

#include "CComponent.hpp"
#include "../Core/ITexture.hpp"
#include "../Font/IFont.hpp"
#include "../Model/IStaticModel.hpp"
#include "../Utils/Export.hpp"

#include <vector>

namespace OMGL3D
{
    namespace UI
    {
        class EXPORT CFrame : public CComponent
        {

        public:

            CFrame(const std::string & name);

            void SetBackground(const std::string & name);

            void SetTitle(const std::string & title, const std::string & font);

            void SetDrawnable(bool drawn);

            bool IsDrawnable() const;

            void AddComponent(CComponent * component);

            std::vector<UTILS::ptr<CComponent>::SharedPtr> & GetListComponent();

            void OnEvent(const MouseEvent & event);

            void Draw();


        private:

            bool _hold;
            int _mousex, _mousey;

            bool _drawn;

            UTILS::ptr<MODEL::IStaticModel>::ResourcePtr _model;
            UTILS::ptr<CORE::ITexture>::ResourcePtr _background;
            UTILS::ptr<FONT::IFont>::ResourcePtr _font;
            std::string _title;



            std::vector<UTILS::ptr<CComponent>::SharedPtr> _list_component;
        };
    }
}

#endif
