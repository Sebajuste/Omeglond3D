#ifndef _DEF_OMEGLOND3D_MATRIX4_HPP
#define _DEF_OMEGLOND3D_MATRIX4_HPP

#include <cmath>
#include <limits>

#include "Vector3.hpp"

namespace OMGL3D
{
    namespace MATH
    {
        template <typename T> class Matrix4
        {

        public:

            Matrix4();

            Matrix4(T a1, T a2, T a3, T a4,
                    T b1, T b2, T b3, T b4,
                    T c1, T c2, T c3, T c4,
                    T d1, T d2, T d3, T d4);

            void SetIdentity();

            bool IsIdentity();

            const T * GetMatrix4() const;

            Vector3<T> GetVector3() const;
            Vector3<T> GetScale() const;

            Matrix4<T> GetRotationMatrix() const;

/*
            void SetTranslation(T x, T y, T z);
            void SetTranslation(const Vector3<T> &v);
            void SetScale(T x, T y, T z);

            void SetRotationX(T angle);
            void SetRotationY(T angle);
            void SetRotationZ(T angle);
*/
            static Matrix4<T> CreateBias();

            static Matrix4<T> CreateTranslation(T x, T y, T z);
            static Matrix4<T> CreateTranslation(const Vector3<T> &vTranslation);
            static Matrix4<T> CreateScale(T x, T y, T z);
            static Matrix4<T> CreateScale(const Vector3<T> &vScale);

            static Matrix4<T> CreateRotationX(T angle);
            static Matrix4<T> CreateRotationY(T angle);
            static Matrix4<T> CreateRotationZ(T angle);

            static Matrix4<T> CreateFrustumMatrix(T left, T right, T bottom, T top, T znear, T zfar);
            static Matrix4<T> CreatePerspectiveMatrix(T angle, T ratio, T znear, T zfar);
            static Matrix4<T> CreateOrthoMatrix(T left, T right, T bottom, T top, T znear, T zfar);

            static Matrix4<T> CreateLookAtMatrix(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ);

            T GetDeterminant() const;

            Matrix4<T> GetTranspose() const;

            Matrix4<T> GetInverse() const;

            Matrix4<T> operator*(const Matrix4<T> &m) const;
            const Matrix4<T>& operator*=(const Matrix4<T> &m);

            Matrix4<T> operator*(const Vector3<T> &v) const;
            const Matrix4<T>& operator*=(const Vector3<T> &v);

            Matrix4<T> operator+(const Vector3<T> &v) const;
            const Matrix4<T>& operator+=(const Vector3<T> &v);

            const T* operator()() const;

            T operator()(unsigned int x, unsigned int y) const;


        private:

            T m11, m12, m13, m14;
            T m21, m22, m23, m24;
            T m31, m32, m33, m34;
            T m41, m42, m43, m44;
        };


        template <typename T> Matrix4<T>::Matrix4() : m11(1.0), m12(0.0), m13(0.0), m14(0.0),
                               m21(0.0), m22(1.0), m23(0.0), m24(0.0),
                               m31(0.0), m32(0.0), m33(1.0), m34(0.0),
                               m41(0.0), m42(0.0), m43(0.0), m44(1.0)
        {

        }

        template <typename T> Matrix4<T>::Matrix4(T a1, T a2, T a3, T a4,
                           T b1, T b2, T b3, T b4,
                           T c1, T c2, T c3, T c4,
                           T d1, T d2, T d3, T d4) : m11(a1), m12(a2), m13(a3), m14(a4),
                                                                         m21(b1), m22(b2), m23(b3), m24(b4),
                                                                         m31(c1), m32(c2), m33(c3), m34(c4),
                                                                         m41(d1), m42(d2), m43(d3), m44(d4)
        {

        }

        template <typename T> void Matrix4<T>::SetIdentity()
        {
            m11=1.0; m12=0.0; m13=0.0; m14=0.0;
            m21=0.0; m22=1.0; m23=0.0; m24=0.0;
            m31=0.0; m32=0.0; m33=1.0; m34=0.0;
            m41=0.0; m42=0.0; m43=0.0; m44=1.0;
        }

        template <typename T> bool Matrix4<T>::IsIdentity()
        {
            return m11==1.0f && m12==0.0f && m13==0.0f && m14==0.0f &&
                   m21==0.0f && m22==1.0f && m23==0.0f && m24==0.0f &&
                   m31==0.0f && m32==0.0f && m33==1.0f && m24==0.0f &&
                   m41==0.0f && m42==0.0f && m43==0.0f && m44==1.0f ? true : false;
        }

        template <typename T> const T* Matrix4<T>::GetMatrix4() const
        {
            return &m11;
        }

        template <typename T> Vector3<T> Matrix4<T>::GetVector3() const
        {
            return Vector3<T>(m41, m42, m43);
        }

        template <typename T> Matrix4<T> Matrix4<T>::GetRotationMatrix() const
        {
            Matrix4<T> m = *this;
            m.m41=0.0; m.m42=0.0; m.m43=0.0;
            return m;
        }

        template <typename T> Vector3<T> Matrix4<T>::GetScale() const
        {
            return Vector3<T>(m11, m22, m33);
        }
/*
        template <typename T> void Matrix4<T>::SetTranslation(T x, T y, T z)
        {
            this->setIdentity();
            m41 = x;
            m42 = y;
            m43 = z;
        }

        template <typename T> void Matrix4<T>::SetTranslation(const Vector3<T> &v)
        {
            this->setIdentity();
            m41 = v.x;
            m42 = v.y;
            m43 = v.z;
        }

        template <typename T> void Matrix4<T>::SetScale(T x, T y, T z)
        {
            this->setIdentity();
            m11 = x;
            m22 = y;
            m33 = z;
        }

        template <typename T> void Matrix4<T>::SetRotationX(T angle)
        {
            this->setIdentity();
            m22 = cos(angle*M_PI/180);
            m23 = -sin(angle*M_PI/180);
            m32 = sin(angle*M_PI/180);
            m33 = cos(angle*M_PI/180);
        }

        template <typename T> void Matrix4<T>::SetRotationY(T angle)
        {
            this->setIdentity();
            m11 = cos(angle*M_PI/180);
            m13 = sin(angle*M_PI/180);
            m31 = -sin(angle*M_PI/180);
            m33 = cos(angle*M_PI/180);
        }

        template <typename T> void Matrix4<T>::SetRotationZ(T angle)
        {
            this->setIdentity();
            m11 = cos(angle*M_PI/180);
            m12 = -sin(angle*M_PI/180);
            m21 = sin(angle*M_PI/180);
            m22 = cos(angle*M_PI/180);
        }
*/
        template <typename T> Matrix4<T> Matrix4<T>::CreateBias()
        {
            return Matrix4<T>(0.5f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.5f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.5f, 0.0f,
                              0.5f, 0.5f, 0.5f, 1.0f);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateTranslation(T x, T y, T z)
        {

            return Matrix4<T>(1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            x, y, z, 1.0);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateTranslation(const Vector3<T> &vTranslation)
        {
            return Matrix4<T>(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            vTranslation.x, vTranslation.y, vTranslation.z, 1);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateScale(T x, T y, T z)
        {
            return Matrix4<T>(x, 0, 0, 0,
                            0, y, 0, 0,
                            0, 0, z, 0,
                            0, 0, 0, 1);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateScale(const Vector3<T> &vScale)
        {
            return Matrix4<T>(vScale.x, 0, 0, 0,
                            0, vScale.y, 0, 0,
                            0, 0, vScale.z, 0,
                            0, 0, 0, 1);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateRotationX(T angle)
        {
            return Matrix4<T>(1, 0, 0, 0,
                            0, cos(angle*M_PI/180), -sin(angle*M_PI/180), 0,
                            0, sin(angle*M_PI/180),  cos(angle*M_PI/180), 0,
                            0, 0, 0, 1);

        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateRotationY(T angle)
        {
            return Matrix4<T>(cos(angle*M_PI/180), 0, sin(angle*M_PI/180), 0,
                            0, 1, 0, 0,
                            -sin(angle*M_PI/180), 0, cos(angle*M_PI/180), 0,
                            0, 0, 0, 1);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateRotationZ(T angle)
        {
            return Matrix4<T>(cos(angle*M_PI/180), -sin(angle*M_PI/180), 0, 0,
                            sin(angle*M_PI/180), cos(angle*M_PI/180), 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateFrustumMatrix(T left, T right, T bottom, T top, T znear, T zfar)
        {
            Matrix4<T> m;
            m.m11 = (2*znear)/(right-left);
            m.m13 = (right+left)/(right-left);
            m.m22 = (2*znear)/(top-bottom);
            m.m23 = (top+bottom)/(top-bottom);
            m.m33 = -(zfar+znear)/(zfar-znear);
            m.m34 = -(2*zfar*znear)/(zfar-znear);
            m.m43 = -1.0;
            return m;
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreatePerspectiveMatrix(T fovy, T ratio, T znear, T zfar)
        {
            Matrix4<T> m;

            //T yScale = 1.0 / std::tan(fovy * M_PI / 180.0 / 2.0);
            T yScale = 1.0 / std::tan((fovy / 2) * M_PI / 180.0);
            T xScale = yScale / ratio;

            m.m11 = xScale;
            m.m22 = yScale;
            m.m33 = (znear + zfar) / ( znear - zfar);
            //m.m34 = (2.0 * znear * zfar) / (znear - zfar);
            m.m43 = (2.0 * znear * zfar) / (znear - zfar);
            //m.m43 = -1.0;
            m.m34 = -1.0;
            m.m44 = 0.0;

            return m;
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateOrthoMatrix(T left, T right, T bottom, T top, T znear, T zfar)
        {
            Matrix4<T> m;
            m.m11 = 2/(right-left);
            m.m41 = -(right+left)/(right-left);
            m.m22 = 2/(top-bottom);
            m.m42 = -(top+bottom)/(top-bottom);
            m.m33 = 2/(zfar-znear);
            m.m43 = -(zfar+znear)/(zfar-znear);
            return m;
        }

        template <typename T> Matrix4<T> Matrix4<T>::CreateLookAtMatrix(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
        {
            Matrix4<T> m;

            Vector3<T> zaxis(eyeX-centerX, eyeY-centerY, eyeZ-centerZ);
            zaxis = zaxis.GetNormalize();

            Vector3<T> xaxis(upY*zaxis.z - upZ*zaxis.y, upZ*zaxis.x - upX * zaxis.z, upX * zaxis.y - upY * zaxis.x);
            xaxis = xaxis.GetNormalize();

            Vector3<T> yaxis(zaxis.y*xaxis.z - zaxis.z*xaxis.y, zaxis.z*xaxis.x - zaxis.x*xaxis.z, zaxis.x*xaxis.y-zaxis.y*xaxis.x);
            yaxis = yaxis.GetNormalize();

            m.m11 = xaxis.x;
            m.m21 = xaxis.y;
            m.m31 = xaxis.z;
            m.m41 = -(xaxis.x * eyeX + xaxis.y * eyeY + xaxis.z * eyeZ);

            m.m12 = yaxis.x;
            m.m22 = yaxis.y;
            m.m32 = yaxis.z;
            m.m42 = -(yaxis.x * eyeX + yaxis.y * eyeY + yaxis.z * eyeZ);

            m.m13 = zaxis.x;
            m.m23 = zaxis.y;
            m.m33 = zaxis.z;
            m.m43 = -(zaxis.x * eyeX + zaxis.y * eyeY + zaxis.z * eyeZ);

            return m.GetInverse();
        }

        template <typename T> T Matrix4<T>::GetDeterminant() const
        {
            T A = m22 * (m33 * m44 - m34 * m43) - m23 * (m32 * m44 - m34 * m42) + m24 * (m32 * m43 - m33 * m42);
            T B = m21 * (m33 * m44 - m34 * m43) - m23 * (m31 * m44 - m34 * m41) + m24 * (m31 * m43 - m33 * m41);
            T C = m21 * (m32 * m44 - m34 * m42) - m22 * (m31 * m44 - m34 * m41) + m24 * (m31 * m42 - m32 * m41);
            T D = m21 * (m32 * m43 - m33 * m42) - m22 * (m31 * m43 - m33 * m41) + m23 * (m31 * m42 - m32 * m41);

            return m11 * A - m12 * B + m13 * C - m14 * D;
        }

        template <typename T> Matrix4<T> Matrix4<T>::GetTranspose() const
        {
            return Matrix4<T>(m11, m21, m31, m41,
                      m12, m22, m32, m42,
                      m13, m23, m33, m43,
                      m14, m24, m34, m44);

            //m11=m.m11; m12=m.m12; m13=m.m13; m14=m.m14;
            //m21=m.m21; m22=m.m22; m23=m.m23; m24=m.m24;
            //m31=m.m31; m32=m.m32; m33=m.m33; m34=m.m34;
            //m41=m.m41; m42=m.m42; m43=m.m43; m44=m.m44;
        }

        template <typename T> Matrix4<T> Matrix4<T>::GetInverse() const
        {
            Matrix4<T> m;

            T det = this->GetDeterminant();

            if (fabs(det) > std::numeric_limits<float>::epsilon())
            {
                m.m11 =  (m22 * (m33 * m44 - m34 * m43) - m32 * (m23 * m44 - m43 * m24) + m42 * (m23 * m34 - m33 *  m24)) / det;
                m.m12 = -(m12 * (m33 * m44 - m43 * m34) - m32 * (m13 * m44 - m43 * m14) + m42 * (m13 * m34 - m33 *  m14)) / det;
                m.m13 =  (m12 * (m23 * m44 - m43 * m24) - m22 * (m13 * m44 - m43 * m14) + m42 * (m13 * m24 - m23 *  m14)) / det;
                m.m14 = -(m12 * (m23 * m34 - m33 * m24) - m22 * (m13 * m34 - m33 * m14) + m32 * (m13 * m24 - m23 *  m14)) / det;

                m.m21 = -(m21 * (m33 * m44 - m34 * m43) - m23 * (m31 * m44 - m34 * m41) + m24 * (m31 * m43 - m33 *  m41)) / det;
                m.m22 =  (m11 * (m33 * m44 - m34 * m43) - m13 * (m31 * m44 - m34 * m41) + m14 * (m31 * m43 - m33 *  m41)) / det;
                m.m23 = -(m11 * (m23 * m44 - m24 * m43) - m13 * (m21 * m44 - m24 * m41) + m14 * (m21 * m43 - m23 *  m41)) / det;
                m.m24 =  (m11 * (m23 * m34 - m24 * m33) - m13 * (m21 * m34 - m24 * m31) + m14 * (m21 * m33 - m23 *  m31)) / det;

                m.m31 =  (m21 * (m32 * m44 - m34 * m42) - m22 * (m31 * m44 - m34 * m41) + m24 * (m31 * m42 - m32 *  m41)) / det;
                m.m32 = -(m11 * (m32 * m44 - m34 * m42) - m12 * (m31 * m44 - m34 * m41) + m14 * (m31 * m42 - m32 *  m41)) / det;
                m.m33 =  (m11 * (m22 * m44 - m24 * m42) - m12 * (m21 * m44 - m24 * m41) + m14 * (m21 * m42 - m22 *  m41)) / det;
                m.m34 = -(m11 * (m22 * m34 - m24 * m32) - m12 * (m21 * m34 - m24 * m31) + m14 * (m21 * m32 - m22 *  m31)) / det;

                m.m41 = -(m21 * (m32 * m43 - m33 * m42) - m22 * (m31 * m43 - m33 * m41) + m23 * (m31 * m42 - m32 *  m41)) / det;
                m.m42 =  (m11 * (m32 * m43 - m33 * m42) - m12 * (m31 * m43 - m33 * m41) + m13 * (m31 * m42 - m32 *  m41)) / det;
                m.m43 = -(m11 * (m22 * m43 - m23 * m42) - m12 * (m21 * m43 - m23 * m41) + m13 * (m21 * m42 - m22 *  m41)) / det;
                m.m44 =  (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 *  m31)) / det;
            }

            return m;
        }



        template <typename T> Matrix4<T> Matrix4<T>::operator*(const Matrix4<T> &m) const
        {
            Matrix4<T> mtr;

            mtr.m11 = m11*m.m11 + m12*m.m21 + m13*m.m31 + m14*m.m41;
            mtr.m12 = m11*m.m12 + m12*m.m22 + m13*m.m32 + m14*m.m42;
            mtr.m13 = m11*m.m13 + m12*m.m23 + m13*m.m33 + m14*m.m43;
            mtr.m14 = m11*m.m14 + m12*m.m24 + m13*m.m34 + m14*m.m44;

            mtr.m21 = m21*m.m11 + m22*m.m21 + m23*m.m31 + m24*m.m41;
            mtr.m22 = m21*m.m12 + m22*m.m22 + m23*m.m32 + m24*m.m42;
            mtr.m23 = m21*m.m13 + m22*m.m23 + m23*m.m33 + m24*m.m43;
            mtr.m24 = m21*m.m14 + m22*m.m24 + m23*m.m34 + m24*m.m44;

            mtr.m31 = m31*m.m11 + m32*m.m21 + m33*m.m31 + m34*m.m41;
            mtr.m32 = m31*m.m12 + m32*m.m22 + m33*m.m32 + m34*m.m42;
            mtr.m33 = m31*m.m13 + m32*m.m23 + m33*m.m33 + m34*m.m43;
            mtr.m34 = m31*m.m14 + m32*m.m24 + m33*m.m34 + m34*m.m44;

            mtr.m41 = m41*m.m11 + m42*m.m21 + m43*m.m31 + m44*m.m41;
            mtr.m42 = m41*m.m12 + m42*m.m22 + m43*m.m32 + m44*m.m42;
            mtr.m43 = m41*m.m13 + m42*m.m23 + m43*m.m33 + m44*m.m43;
            mtr.m44 = m41*m.m14 + m42*m.m24 + m43*m.m34 + m44*m.m44;

            return mtr;
        }

        template <typename T> const Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T> &m)
        {
            return *this = m * *this;
        }

        template <typename T> Matrix4<T> Matrix4<T>::operator*(const Vector3<T> &v) const
        {
            Matrix4<T> m = *this;
            m.m41 = v.x*m.m11 + v.y*m.m21 + v.z*m.m31 + m.m41;
            m.m42 = v.x*m.m12 + v.y*m.m22 + v.z*m.m32 + m.m42;
            m.m43 = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + m.m43;
            return m;
        }

        template <typename T> const Matrix4<T>& Matrix4<T>::operator*=(const Vector3<T> &v) {
            return *this = *this * v;
        }

        template <typename T> Matrix4<T> Matrix4<T>::operator+(const Vector3<T> &v) const
        {
            Matrix4<T> m = *this;
            m.m41 += v.x;
            m.m42 += v.y;
            m.m43 += v.z;
            return m;
        }

        template <typename T> const Matrix4<T>& Matrix4<T>::operator+=(const Vector3<T> &v)
        {
            m41 += v.x;
            m42 += v.y;
            m43 += v.z;
            return *this;
        }

        template <typename T> const T* Matrix4<T>::operator()() const
        {
            return &m11;
        }

        template <typename T> T Matrix4<T>::operator()(unsigned int x, unsigned int y) const
        {
            if( x >= 4 || y >= 4) return 0;
            return &m11[y*4+x];
        }

        typedef Matrix4<int> Matrix4i;
        typedef Matrix4<float> Matrix4f;
        typedef Matrix4<double> Matrix4d;
    }


}

#endif
