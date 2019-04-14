#include "CPicture.hpp"

#include "../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CPicture::CPicture(const std::string &name, unsigned int bpp, unsigned int width, unsigned int height, unsigned char* datas) : _name(name), _bpp(bpp), _width(width), _height(height), _datas(datas)
        {
        }

        CPicture::CPicture(const CPicture & picture) : _name(picture.GetName()), _bpp(picture.GetBpp()), _width(picture.GetWidth()), _height(picture.GetHeight())
        {
            const unsigned char * source = picture.GetDatas();
            int size = _width*_height*(_bpp/8);

            _datas = new unsigned char[size];
            std::copy(&source[0], &source[size], &_datas[0]);
        }

        CPicture::~CPicture()
        {
            delete[] _datas;
        }

        const std::string & CPicture::GetName() const
        {
            return _name;
        }

        unsigned int CPicture::GetBpp() const
        {
            return _bpp;
        }

        unsigned int CPicture::GetWidth() const
        {
            return _width;
        }

        unsigned int CPicture::GetHeight() const
        {
            return _height;
        }

        const unsigned char* CPicture::GetDatas() const
        {
            return _datas;
        }
    }
}
