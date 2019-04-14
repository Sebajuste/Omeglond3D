#ifndef _DEF_OMEGLOND3D_OLG3MATRIXMANAGER_HPP
#define _DEF_OMEGLOND3D_OLG3MATRIXMANAGER_HPP

#include <queue>

#include "../../Math/Matrix4.hpp"

#include "../../Core/CVideoDriver.hpp"

#include "../../Utils/Pattern/Singleton.hpp"

namespace OMGL3D
{

namespace OGL3
{


class OGL3MatrixManager : public UTILS::Singleton<OGL3MatrixManager>
{

public:

    void PushMatrix(const CORE::MatrixType &type);

    void PopMatrix(const CORE::MatrixType &type);

    void MultMatrix(const MATH::Matrix4f &matrix, const CORE::MatrixType &type);

    void LoadMatrix(const MATH::Matrix4f & matrix, const CORE::MatrixType & type);

    const MATH::Matrix4f & GetMatrix(const CORE::MatrixType & type);


private:

    MATH::Matrix4f _currentMatrixProjection;
    MATH::Matrix4f _currentMatrixModel;
    MATH::Matrix4f _currentMatrixView;
    MATH::Matrix4f _currentMatrixTexture;

    std::queue<MATH::Matrix4f> _queueMatrixProjection;
    std::queue<MATH::Matrix4f> _queueMatrixModel;
    std::queue<MATH::Matrix4f> _queueMatrixView;
    std::queue<MATH::Matrix4f> _queueMatrixTexture;


};



} // namespace OGL3
} // namespace OMGL3D

#endif
