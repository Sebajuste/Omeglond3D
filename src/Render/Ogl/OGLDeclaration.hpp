#ifndef _DEF_OMEGLOND3D_OGLDECLARATION_HPP
#define _DEF_OMEGLOND3D_OGLDECLARATION_HPP

#include "../../Core/IDeclaration.hpp"

#include <GL/gl.h>
#include <vector>

namespace OMGL3D
{
    namespace OGL
    {
        // Tables de correspondance avec les énumérations ElementType
        static const unsigned int Size[] = {4, 4, 3, 2, 1 };
        static const unsigned int Type[] = {GL_UNSIGNED_BYTE, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT };
        static const unsigned int SizeOf[] = {1, 4, 4, 4};

        struct OGLElement
        {
            unsigned int channel;
            unsigned int offset;
            CORE::ElementTarget target;
            CORE::ElementType type;
        };

        class OGLDeclaration : public CORE::IDeclaration
        {

        public:

            OGLDeclaration();

            ~OGLDeclaration();

            void AddElement(const OGLElement &element);

            CORE::IDeclaration * Copy() const;

            std::vector<OGLElement> _elements;
        };
    }
}

#endif
