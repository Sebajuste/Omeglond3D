#include "CCubeMap.hpp"

#include "CMediaManager.hpp"

#include "../Utils/Ptr/SmartPtr.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CCubeMap::CCubeMap(const std::string &name) : ICubeMap(name), _bpp(0), _width(0), _height(0)
        {
        }

        CCubeMap::~CCubeMap()
        {
        }

        unsigned int CCubeMap::GetBpp() const
        {
            return _bpp;
        }

        unsigned int CCubeMap::GetWidth() const
        {
            return _width;
        }

        unsigned int CCubeMap::GetHeight() const
        {
            return _height;
        }

         void CCubeMap::SetTexture(const CubeMapOrientation & orient, const std::string & picture_name) const
         {
             OMGL3D::UTILS::ptr<OMGL3D::CORE::CPicture>::SharedPtr img;
             img = OMGL3D::CORE::CMediaManager::GetInstance().LoadFromFile<OMGL3D::CORE::CPicture>(picture_name);
             this->SetTexture(orient, *img);
         }
    }
}
