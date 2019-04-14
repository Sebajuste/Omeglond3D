#ifndef _DEF_OMEGLOND3D_CPICTURE_HPP
#define _DEF_OMEGLOND3D_CPICTURE_HPP

#include <string>

namespace OMGL3D
{
    namespace CORE
    {
        class CPicture
        {

        public:

            CPicture(const std::string &name, unsigned int bpp, unsigned int width, unsigned int height, unsigned char* datas);

            CPicture(const CPicture & picture);

            ~CPicture();

            const std::string & GetName() const;

            unsigned int GetBpp() const;

            unsigned int GetWidth() const;

            unsigned int GetHeight() const;

            const unsigned char* GetDatas() const;


        private:

            std::string _name;

            unsigned int _bpp, _width, _height;
            unsigned char* _datas;
        };
    }
}

#endif
