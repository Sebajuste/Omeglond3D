#ifndef _DEF_OMEGLOND3D_VECTOR_HPP
#define _DEF_OMEGLOND3D_VECTOR_HPP

#include <limits>
#include <cmath>

namespace OMGL3D
{
    namespace MATH
    {
        template <typename T> class Vector3
        {

        public:

            Vector3();

            Vector3(T x, T y, T z);

            Vector3( const Vector3<T> &vector);

            Vector3 GetNormalize() const;

            T GetLength() const;

            Vector3<T> operator+(const Vector3<T> &vector) const;

            const Vector3<T> operator+=(const Vector3<T> &vector);

            Vector3<T> operator+(const T &t) const;

            const Vector3<T> operator+=(const T &t);

            Vector3<T> operator-(const Vector3<T> &vector) const;

            const Vector3<T> operator-=(const Vector3<T> &vector);

            Vector3<T> operator-(const T &t) const;

            const Vector3<T> operator-=(const T &t);

            Vector3<T> operator*(const Vector3<T> &vector) const;

            const Vector3<T> operator*=(const Vector3<T> &vector);

            Vector3<T> operator*(const T &t) const;

            const Vector3<T> operator*=(const T &t);

            static Vector3<T> VectorCross(const Vector3<T> &v1, const Vector3<T> &v2);

            static T VectorDot(const Vector3<T> &v1, const Vector3<T> &v2);

            static T VectorLength(const Vector3<T> &v1, const Vector3<T> &v2);

            T x, y, z;
        };

        template <typename T> Vector3<T>::Vector3() : x(0), y(0), z(0)
        {
        }

        template <typename T> Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z)
        {
        }

        template <typename T> Vector3<T>::Vector3(const Vector3<T> &vector) : x(vector.x), y(vector.y), z(vector.z)
        {
        }

        template <typename T> Vector3<T> Vector3<T>::GetNormalize() const
        {
            float norm = sqrt(x*x + y*y + z*z);
            Vector3<T> vector(x, y, z);
            if( std::fabs(norm) > std::numeric_limits<T>::epsilon() )
            {
                vector.x /= norm;
                vector.y /= norm;
                vector.z /= norm;
            }
            return vector;
        }

        template <typename T> T Vector3<T>::GetLength() const
        {
            return sqrt(x*x + y*y + z*z);
        }

        template <typename T> Vector3<T> Vector3<T>::operator+(const Vector3<T> &vector) const
        {
            return Vector3<T>(x+vector.x, y+vector.y, z+vector.z);
        }

        template <typename T> const Vector3<T> Vector3<T>::operator+=(const Vector3<T> &vector)
        {
            return *this = *this + vector;
        }

        template <typename T> Vector3<T> Vector3<T>::operator+(const T &t) const
        {
            return Vector3<T>(x+t, y+t, z+t);
        }

        template <typename T> const Vector3<T> Vector3<T>::operator+=(const T &t)
        {
            return *this = *this + t;
        }

        template <typename T> Vector3<T> Vector3<T>::operator-(const Vector3<T> &vector) const
        {
            return Vector3<T>(x-vector.x, y-vector.y, z-vector.z);
        }

        template <typename T> const Vector3<T> Vector3<T>::operator-=(const Vector3<T> &vector)
        {
            return *this = *this - vector;
        }

        template <typename T> Vector3<T> Vector3<T>::operator-(const T &t) const
        {
            return Vector3<T>(x-t, y-t, z-t);
        }

        template <typename T> const Vector3<T> Vector3<T>::operator-=(const T &t)
        {
            return *this = *this - t;
        }

        template <typename T> Vector3<T> Vector3<T>::operator*(const Vector3 &vector) const
        {
            return Vector3<T>(x*vector.x, y*vector.y, z*vector.z);
        }

        template <typename T> const Vector3<T> Vector3<T>::operator*=(const Vector3 &vector)
        {
            return *this = *this * vector;
        }

        template <typename T> Vector3<T> Vector3<T>::operator*(const T &t) const
        {
            return Vector3<T>(x*t, y*t, z*t);
        }

        template <typename T> const Vector3<T> Vector3<T>::operator*=(const T &t)
        {
            return *this = *this * t;
        }

        template <typename T> Vector3<T> Vector3<T>::VectorCross(const Vector3<T> &v1, const Vector3<T> &v2)
        {
            return Vector3<T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
        }

        template <typename T> T Vector3<T>::VectorDot(const Vector3<T> &v1, const Vector3<T> &v2)
        {
                    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
        }

        template <typename T> T Vector3<T>::VectorLength(const Vector3<T> &v1, const Vector3<T> &v2)
        {
            T x = v2.x - v1.x;
            T y = v2.y - v1.y;
            T z = v2.z - v1.z;
            return sqrt(x*x + y*y + z*z);
        }

        typedef Vector3<int> Vector3i;
        typedef Vector3<float> Vector3f;
        typedef Vector3<double> Vector3d;
    }
}

#endif
