#include "OGL3MatrixManager.hpp"

namespace OMGL3D
{
namespace OGL3
{

void OGL3MatrixManager::PushMatrix(const CORE::MatrixType &type)
{
    switch(type)
    {
        case CORE::OMGL_MATRIX_PROJECTION:
            _queueMatrixProjection.push(_currentMatrixProjection);
            break;

        case CORE::OMGL_MATRIX_VIEW:
            _queueMatrixView.push(_currentMatrixView);
            break;

        case CORE::OMGL_MATRIX_MODEL:
            _queueMatrixModel.push(_currentMatrixModel);
            break;

        case CORE::OMGL_MATRIX_TEXTURE:
            _queueMatrixTexture.push(_currentMatrixTexture);
            break;
    }
        }

void OGL3MatrixManager::PopMatrix(const CORE::MatrixType &type)
{
    switch(type)
    {
        case CORE::OMGL_MATRIX_PROJECTION:
            _currentMatrixProjection = _queueMatrixProjection.front();
            _queueMatrixProjection.pop();
            break;

        case CORE::OMGL_MATRIX_VIEW:
            _currentMatrixView = _queueMatrixView.front();
            _queueMatrixView.pop();
            break;

        case CORE::OMGL_MATRIX_MODEL:
            _currentMatrixModel = _queueMatrixModel.front();
            _queueMatrixModel.pop();
            break;

        case CORE::OMGL_MATRIX_TEXTURE:
            _currentMatrixTexture = _queueMatrixTexture.front();
            _queueMatrixTexture.pop();
            break;
    }
}

void OGL3MatrixManager::MultMatrix(const MATH::Matrix4f &matrix, const CORE::MatrixType &type)
{
    switch(type)
    {
        case CORE::OMGL_MATRIX_PROJECTION:
            _currentMatrixProjection = matrix * _currentMatrixProjection;
            break;

        case CORE::OMGL_MATRIX_VIEW:
        {
            _currentMatrixView = matrix * _currentMatrixView;
            return;
        }
        case CORE::OMGL_MATRIX_MODEL:
            _currentMatrixModel = matrix * _currentMatrixModel;
            break;

        case CORE::OMGL_MATRIX_TEXTURE:
            _currentMatrixTexture = matrix * _currentMatrixTexture;
            break;
    }
}

void OGL3MatrixManager::LoadMatrix(const MATH::Matrix4f & matrix, const CORE::MatrixType & type)
{
    switch(type)
    {
        case CORE::OMGL_MATRIX_PROJECTION:
            _currentMatrixProjection = matrix;
            break;

        case CORE::OMGL_MATRIX_VIEW:
            _currentMatrixView = matrix;
            break;

        case CORE::OMGL_MATRIX_MODEL:
            _currentMatrixModel = matrix;
            break;

        case CORE::OMGL_MATRIX_TEXTURE:
            _currentMatrixTexture = matrix;
            break;
    }
}

const MATH::Matrix4f & OGL3MatrixManager::GetMatrix(const CORE::MatrixType & type)
{
    switch(type)
    {
        case CORE::OMGL_MATRIX_PROJECTION:
            return _currentMatrixProjection;
            break;

        case CORE::OMGL_MATRIX_VIEW:
            return _currentMatrixView;
            break;

        case CORE::OMGL_MATRIX_MODEL:
            return _currentMatrixModel;
            break;

        case CORE::OMGL_MATRIX_TEXTURE:
            return _currentMatrixTexture;
            break;
    }
    return _currentMatrixView;
}

} // namespace OGL3
} // namespace OMGL3D
