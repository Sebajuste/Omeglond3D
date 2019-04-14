#include "CDeclaration.hpp"

#include "CDevice.hpp"
#include "IVideoDriver.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CDeclaration::~CDeclaration()
        {
        }

        IDeclaration * CDeclaration::Copy() const
        {
            IDeclaration * declaration = CDevice::GetDevice()->GetVideoDriver()->CreateDeclaration(&_elements[0], _elements.size());
            return declaration;
        }

        void CDeclaration::AddElement(const Element & element)
        {
            _elements.push_back(element);
        }
    }
}
