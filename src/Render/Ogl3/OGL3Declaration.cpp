#include "OGL3Declaration.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3Declaration::OGL3Declaration()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "OGLDeclaration create" << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGL3Declaration::~OGL3Declaration()
        {
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "OGLDeclaration delete" << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGL3Declaration::AddElement(const OGL3Element &element)
        {
            _elements.push_back(element);
        }

        CORE::IDeclaration * OGL3Declaration::Copy() const
        {
            OGL3Declaration * copy = new OGL3Declaration();
            copy->_elements = _elements;
            return copy;
        }
    }
}
