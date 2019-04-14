#ifndef _DEF_OMEGLOND3D_IDECLARATION_HPP
#define _DEF_OMEGLOND3D_IDECLARATION_HPP

#include "../Utils/Ptr/SmartPtr.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        enum ElementTarget {
            OMGL_ELEMENT_TARGET_POSITIONAL,
            OMGL_ELEMENT_TARGET_NORMAL,
            OMGL_ELEMENT_TARGET_COLOR,
            OMGL_ELEMENT_TARGET_TEXCOORD0,
            OMGL_ELEMENT_TARGET_TEXCOORD1,
            OMGL_ELEMENT_TARGET_TEXCOORD2,
            OMGL_ELEMENT_TARGET_TEXCOORD3,
            OMGL_ELEMENT_TARGET_TEXCOORD4,
            OMGL_ELEMENT_TARGET_TEXCOORD5,
            OMGL_ELEMENT_TARGET_TEXCOORD6,
            OMGL_ELEMENT_TARGET_TEXCOORD7,
            OMGL_ELEMENT_TARGET_TEXCOORD8
        };

        enum ElementType {
            OMGL_ELEMENT_TYPE_UNSIGNED_BYTE4,
            OMGL_ELEMENT_TYPE_FLOAT4,
            OMGL_ELEMENT_TYPE_FLOAT3,
            OMGL_ELEMENT_TYPE_FLOAT2,
            OMGL_ELEMENT_TYPE_FLOAT1
        };

        struct Element
        {
            unsigned int stream;
            ElementTarget target;
            ElementType type;
        };

        class IDeclaration
        {

        public:

            virtual ~IDeclaration() { }

            virtual IDeclaration * Copy() const=0;

        protected:

            IDeclaration() { }
        };

        typedef UTILS::SmartPtr<IDeclaration, UTILS::RefCountPtr> DeclarationPtr;
    }
}

#endif
