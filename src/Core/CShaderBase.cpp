#include "CShaderBase.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CShaderBase::CShaderBase(const std::string & name, const ShaderType & type) : IShaderBase(name), _type(type)
        {
        }

        CShaderBase::~CShaderBase()
        {
        }

        ShaderType CShaderBase::GetType() const
        {
            return _type;
        }
    }
}
