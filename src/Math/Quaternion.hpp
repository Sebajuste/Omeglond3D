#ifndef _DEF_OMEGLOND3D_QUATERNION_HPP
#define _DEF_OMEGLOND3D_QUATERNION_HPP

namespace OMGL3D
{
    namespace MATH
    {
        template <typename T> struct Euler
        {
            T x, y, z;
        };

        typedef Euler<float> Eulerf;
        typedef Euler<double> Eulerd;

        template <typename T> struct RotateAxis
        {
            T x, y, z;
            T angle;
        };

        typedef RotateAxis<float> RotateAxisf;
        typedef RotateAxis<double> RotateAxisd;

        template <typename T> class Quaternion
        {

        public:

            Quaternion();

            Quaternion(T x, T y, T z, T w=1.0);

            Quaternion(const Quaternion &q);

            void SetIdentity();

            static Quaternion CreateQuaternion(T x, T y, T z, T w);
            static Quaternion CreateQuaternion(T x, T y, T z);
            static Quaternion CreateQuaternion(const RotateAxis<T> &rotation);
            static Quaternion CreateQuaternion(const Euler<T> &euler);
            static Quaternion CreateQuaternion(const Matrix4<T> &matrix);
            static Quaternion CreateQuaternion(const Quaternion &q);

            Quaternion GetConjugate() const; // conjugé
            Quaternion GetNormalize() const; // norme

            void Mult(const Quaternion<T> &q);

            Matrix4<T> GetMatrix4() const;

            RotateAxis<T> GetRotateAxis();

            Vector3<T> GetVector3() const;

            // Rélisation une roation autour du quaterion courant ( note: le quaternion doit être normalisé ! )
            Vector3<T> Rotate(const Vector3<T> &v) const;

            void CreateW();

            T GetX() const;
            T GetY() const;
            T GetZ() const;
            T GetW() const;

            Quaternion<T> operator*(const Quaternion<T> &q) const;
            const Quaternion<T>& operator*=(const Quaternion<T> &q);

            Quaternion<T> operator*(const Vector3<T> &v) const;

            static T QuatDot(const Quaternion<T> &q1, const Quaternion<T> &q2);

            static Quaternion<T> QuatSlerp(const Quaternion<T> &q1, const Quaternion<T> &q2, const T &interpolation);


        private:

            T _x, _y, _z, _w;
        };

        template <typename T> Quaternion<T>::Quaternion() : _x(0), _y(0), _z(0), _w(1)
        {
        }

        template <typename T> Quaternion<T>::Quaternion(T x, T y, T z, T w) : _x(x), _y(y), _z(z), _w(w)
        {
        }

        template <typename T> Quaternion<T>::Quaternion(const Quaternion<T> &q) : _x(q._x), _y(q._y), _z(q._z), _w(q._w)
        {
        }

        template <typename T> void Quaternion<T>::SetIdentity()
        {
            _x = _y = _z = 0;
            _w = 1;
        }

        template <typename T> Quaternion<T> Quaternion<T>::CreateQuaternion(T x, T y, T z, T w)
        {
            T sin_w = sin((w*M_PI/180) / 2);
            T cos_w = cos((w*M_PI/180) / 2);

            return Quaternion<T>(x*sin_w, y*sin_w, z*sin_w, cos_w).GetNormalize();
        }

        template <typename T> Quaternion<T> Quaternion<T>::CreateQuaternion(T x, T y, T z)
        {
            return (Quaternion<T>(1, 0, 0, x) * Quaternion<T>(0, 1, 0, z)) * Quaternion<T>(0, 0, 1, z);
        }

        template <typename T> Quaternion<T> Quaternion<T>::CreateQuaternion(const RotateAxis<T> &rotation)
        {
            T sin_a = sin(rotation.angle / 2);
            T cos_a = cos(rotation.angle / 2);

            return Quaternion<T>(rotation.x * sin_a, rotation.y * sin_a, rotation.z * sin_a, cos_a).normalize();
        }

        template <typename T> Quaternion<T> Quaternion<T>::CreateQuaternion(const Euler<T> & euler)
        {
            return (Quaternion<T>(1, 0, 0, euler.x) * Quaternion<T>(0, 1, 0, euler.z)) * Quaternion<T>(0, 0, 1, euler.z);
        }

        template <typename T> Quaternion<T> Quaternion<T>::CreateQuaternion(const Matrix4<T> & matrix)
        {
            const T * tab_matrix = matrix.GetMatrix4();

            T trace = tab_matrix[0] + tab_matrix[5] + tab_matrix[10] + 1.0f;

            if (trace > 0)
            {
                T s = 0.5 / sqrt(trace);
                return Quaternion<T>((tab_matrix[9] - tab_matrix[6]) * s,
                                  (tab_matrix[2] - tab_matrix[8]) * s,
                                  (tab_matrix[4] - tab_matrix[1]) * s,
                                  0.25 / s);
            }
            else
            {
                if (tab_matrix[0] > tab_matrix[5] && tab_matrix[0] > tab_matrix[10] )
                {
                    T s = sqrt(1.0 + tab_matrix[0] - tab_matrix[5] - tab_matrix[10]) * 2;
                    return Quaternion<T>(0.5 / s,
                                        (tab_matrix[1] + tab_matrix[4]) / s,
                                        (tab_matrix[2] + tab_matrix[8]) / s,
                                        (tab_matrix[6] + tab_matrix[9]) / s);
                }
                else if (tab_matrix[5] > tab_matrix[10])
                {
                    //float s = sqrt(1.0f - matrix[0] + matrix[5] - matrix[10]) * 2;
                    T s = sqrt(1.0 - tab_matrix[5] - tab_matrix[0] - tab_matrix[10]) * 2;
                    return Quaternion<T>((tab_matrix[1] + tab_matrix[4]) / s,
                                         0.5 / s,
                                         (tab_matrix[6] + tab_matrix[9]) / s,
                                         (tab_matrix[2] + tab_matrix[8]) / s);
                }
                else
                {
                    //float s = sqrt(1 - matrix[0] - matrix[5] + matrix[10]) * 2;
                    T s = sqrt(1.0 - tab_matrix[10] - tab_matrix[0] - tab_matrix[5]) * 2;
                    return Quaternion<T>((tab_matrix[2] + tab_matrix[8]) / s,
                                         (tab_matrix[6] + tab_matrix[9]) / s,
                                         0.5 / s,
                                         (tab_matrix[1] + tab_matrix[4]) / s);
                }
            }
        }

        template <typename T> Quaternion<T> Quaternion<T>::CreateQuaternion(const Quaternion &q)
        {
            return Quaternion<T>(q.getX(), q.getY(), q.getZ(), q.getW());
        }

        template <typename T> Quaternion<T> Quaternion<T>::GetConjugate() const
        {
            return Quaternion<T>(-_x, -_y, -_z, _w);
        }

        template <typename T> Quaternion<T> Quaternion<T>::GetNormalize() const
        {
            Quaternion<T> q(_x, _y, _z, _w);
            T norm = (T) sqrt(_x*_x + _y*_y + _z*_z + _w*_w);

            if( norm > 0.0)
            {
                norm = 1.0 / norm;
                q._x *= norm;
                q._y *= norm;
                q._z *= norm;
                q._w *= norm;
            }
            return q;
        }

        template <typename T> void Quaternion<T>::Mult(const Quaternion<T> &q)
        {
            _x = _w*q._x + _x*q._w + _y*q._z - _z*q._y;
            _y = _w*q._y + _y*q._w + _z*q._x - _x*q._z;
            _z = _w*q._z + _z*q._w + _x*q._y - _y*q._x;
            _w = _w*q._w - _x*q._x - _y*q._y - _z*q._z;

        }

        template <typename T> Matrix4<T> Quaternion<T>::GetMatrix4() const
        {
            float xx = _x * _x;
            float xy = _x * _y;
            float xz = _x * _z;
            float xw = _x * _w;
            float yy = _y * _y;
            float yz = _y * _z;
            float yw = _y * _w;
            float zz = _z * _z;
            float zw = _z * _w;

            return Matrix4<T>(1 - 2 * (yy + zz),     2 * (xy - zw),     2 * (xz + yw), 0,
                            2 * (xy + zw), 1 - 2 * (xx + zz),     2 * (yz - xw), 0,
                            2 * (xz - yw),     2 * (yz + xw), 1 - 2 * (xx + yy), 0,
                                        0,                 0,                 0, 1.0);
        }

        template <typename T> RotateAxis<T> Quaternion<T>::GetRotateAxis()
        {
            RotateAxis<T> ra;

            // Normalisation du quaternion
            //qt.normalize();

            // Récupération de l'angle de rotation
            ra.angle = (acosf(_w) * 2) * 180 / M_PI;

            // Récupération des composantes de l'axe de rotation
            T vx = _x;
            T vy = _y;
            T vz = _z;

            // Normalisation de l'axe de rotation
            T norm = sqrt(vx * vx + vy * vy + vz * vz);
            //if (norm > 0.0005)
            if (fabs(norm) > std::numeric_limits<T>::epsilon())
            {
                vx /= norm;
                vy /= norm;
                vz /= norm;
            }


            ra.x = vx;
            ra.y = vy;
            ra.z = vz;
            return ra;
        }

        template <typename T> Vector3<T>Quaternion<T>::GetVector3() const
        {
            return Vector3<T>(_x, _y, _z);
        }

        template <typename T> Vector3<T> Quaternion<T>::Rotate(const Vector3<T> &v) const
        {
            return ((*this * v) * this->conjugate()).getVector3d();
        }

        template <typename T> void Quaternion<T>::CreateW()
        {
            T t = 1.0f - (_x*_x) - (_y*_y) - (_z*_z);

            if (t < 0.0) {
                _w = 0.0;
            } else {
                _w = -sqrt(t);
            }
        }

        template <typename T> T Quaternion<T>::GetX() const
        {
            return _x;
        }

        template <typename T> T Quaternion<T>::GetY() const
        {
            return _y;
        }

        template <typename T> T Quaternion<T>::GetZ() const
        {
            return _z;
        }

        template <typename T> T Quaternion<T>::GetW() const
        {
            return _w;
        }


        template <typename T> Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &q) const
        {
            return Quaternion<T>(_w*q._x + _x*q._w + _y*q._z - _z*q._y,
                                 _w*q._y + _y*q._w + _z*q._x - _x*q._z,
                                 _w*q._z + _z*q._w + _x*q._y - _y*q._x,
                                 _w*q._w - _x*q._x - _y*q._y - _z*q._z );

        }

        template <typename T> const Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T> &q)
        {
            return *this = *this * q;
        }

        template <typename T> Quaternion<T> Quaternion<T>::operator*(const Vector3<T> &v) const
        {
            return Quaternion<T>(  (_w * v.x) + (_y * v.z) - (_z * v.y),
                                   (_w * v.y) + (_z * v.x) - (_x * v.z),
                                   (_w * v.z) + (_x * v.y) - (_y * v.x),
                                 - (_x * v.x) - (_y * v.y) - (_z * v.z) );
        }

        template <typename T> T Quaternion<T>::QuatDot(const Quaternion<T> &q1, const Quaternion<T> &q2)
        {
            return q1.getX() * q2.getX() + q1.getY() * q2.getY() + q1.getZ() * q2.getZ() + q1.getW() * q2.getW();
        }

        template <typename T> Quaternion<T> Quaternion<T>::QuatSlerp(const Quaternion<T> &q1, const Quaternion<T> &q2, const T &interpolation)
        {

            if( interpolation < 0.0 ) {
                return q1;
            }

            if( interpolation > 1.0) {
                return q2;
            }

            T cosOmega = Quaternion<T>::quatDot(q1, q2);

            T x = q2.getX();
            T y = q2.getY();
            T z = q2.getZ();
            T w = q2.getW();

            if( cosOmega < 0.0)
            {
                x = -x;
                y = -y;
                z = -z;
                w = -w;
                cosOmega = -cosOmega;
            }

            if( cosOmega >= 1.1) return q1;

            float k0, k1;

            if( cosOmega > 0.9999 )
            {
                k0 = 1.0f - interpolation;
                k1 = interpolation;
            }
            else
            {
                T sinOmega = (T)sqrt( 1.0 - (cosOmega*cosOmega));
                T omega = (T) atan2(sinOmega, cosOmega);

                T oneOverSinOmega = 1.0 / sinOmega;

                k0 = (T) sin((1.0 - interpolation) * omega) * oneOverSinOmega;
                k1 = (T) sin(interpolation * omega) * oneOverSinOmega;
            }


            return Quaternion<T>(k0*q1.getX() + k1*x, k0*q1.getY() + k1*y, k0*q1.getZ() + k1*z, k0*q1.getW() + k1*w);
        }

        typedef Quaternion<float> Quaternionf;
        typedef Quaternion<double> Quaterniond;
    }
}

#endif
