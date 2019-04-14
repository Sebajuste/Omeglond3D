#include "CShader.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CShader::CShader(const std::string & name) : IShader(name)
        {
        }

        CShader::~CShader()
        {
        }

        IShaderBase * CShader::GetVertexShader()
        {
            return _vertexShader;
        }

        IShaderBase * CShader::GetPixelShader()
        {
            return _pixelShader;
        }
    }
}
