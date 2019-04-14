#ifndef _DEF_OMEGLOND3D_CDECLARATION_HPP
#define _DEF_OMEGLOND3D_CDECLARATION_HPP

#include "IDeclaration.hpp"

#include <vector>

namespace OMGL3D
{
    namespace CORE
    {
        class CDeclaration : public IDeclaration
        {

        public:

            ~CDeclaration();

            IDeclaration * Copy() const;

            void AddElement(const Element & element);

            template <std::size_t S> void AddElements(const Element (&elements)[S]);

        private:

            std::vector<Element> _elements;
        };

        template <std::size_t S> void CDeclaration::AddElements(const Element (&elements)[S])
        {
            for(unsigned int index=0; index<S; ++index)
            {
                AddElement(elements[index]);
            }
        }
    }
}

#endif
