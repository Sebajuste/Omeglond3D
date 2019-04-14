#ifndef _DEF_OMEGLOND3D_OGL3DECLARATION_HPP
#define _DEF_OMEGLOND3D_OGL3DECLARATION_HPP

#include "../../Core/IDeclaration.hpp"

#include <GL3/gl3.h>
#include <vector>

namespace OMGL3D
{
    namespace OGL3
    {
        // Tables de correspondance avec les énumérations ElementType
        static const unsigned int Size[] = {4, 4, 3, 2, 1 };
        static const unsigned int Type[] = {GL_UNSIGNED_BYTE, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT };
        static const unsigned int SizeOf[] = {1, 4, 4, 4};

        struct OGL3Element
        {
            unsigned int channel;
            unsigned int offset;
            CORE::ElementTarget target;
            CORE::ElementType type;
        };

        class OGL3Declaration : public CORE::IDeclaration
        {

        public:

            OGL3Declaration();

            ~OGL3Declaration();

            void AddElement(const OGL3Element &element);

            CORE::IDeclaration * Copy() const;

            std::vector<OGL3Element> _elements;
        };
    }
}

#endif
