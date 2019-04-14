#include "OGLDeclaration.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLDeclaration::OGLDeclaration()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "OGLDeclaration create" << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGLDeclaration::~OGLDeclaration()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "OGLDeclaration delete" << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGLDeclaration::AddElement(const OGLElement &element)
        {
            _elements.push_back(element);
        }

        CORE::IDeclaration * OGLDeclaration::Copy() const
        {
            OGLDeclaration * copy = new OGLDeclaration();
            copy->_elements = _elements;
            return copy;
        }
    }
}
