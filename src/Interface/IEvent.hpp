#ifndef _DEF_OMEGLOND3D_IEVENT_HPP
#define _DEF_OMEGLOND3D_IEVENT_HPP

#include "../Utils/Export.hpp"

namespace OMGL3D
{
    namespace UI
    {
        //class CComponent;

        struct MouseEvent
        {
            enum Type {
                Pressed,
                Release,
                Moved
            };

            enum Button {
                Right,
                Middle,
                MiddleUp,
                MiddleDown,
                Left
            };

            Type type;
            Button button;
            int x, y;
        };

        class EXPORT IMouseAction
        {

        public:

            virtual ~IMouseAction() {}

            virtual void OnClick(const MouseEvent & event) {}

            virtual void UnClick(const MouseEvent & event) {}

            virtual void OnMoved(const MouseEvent & event) {}

            virtual void OnFocus(const MouseEvent & event) {}

            virtual void UnFocus(const MouseEvent & event) {}

/*
            CComponent * getParentComponent() {
                return _parent;
            }
*/
        private:

            //friend class CComponent;

            //CComponent * _parent;
        };
    }
}

#endif
