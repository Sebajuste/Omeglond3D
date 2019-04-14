#include "CLight.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        CLight::CLight(const std::string & name) : ILight(name), _type(OMGL_LIGHT_INFINITE), _cutoff(0)
        {
            _attenuations[OMGL_LIGHT_ATTENUATION_CONSTANT] = 1.0f;
            _attenuations[OMGL_LIGHT_ATTENUATION_LINEAR] = 0.0f;
            _attenuations[OMGL_LIGHT_ATTENUATION_QUADRATIC] = 0.0f;
        }

        CLight::~CLight()
        {
        }

        LightType CLight::GetType() const
        {
            return _type;
        }

        void CLight::SetType(const LightType & type)
        {
            _type = type;
        }

        void CLight::SetPosition(const MATH::Vector3f & vector)
        {
            _position = vector;
        }

        MATH::Vector3f CLight::GetPosition() const
        {
            return _position;
        }

        int CLight::GetCutoff() const
        {
            return _cutoff;
        }

        void CLight::SetCutoff(int cutoff)
        {
            _cutoff = cutoff;
        }

        MATH::Vector3f CLight::GetBeamVector() const
        {
            return _beamVector;
        }

        void CLight::SetBeamVector(const MATH::Vector3f & vector)
        {
            _beamVector = vector;
        }

        void CLight::SetColor(const LightColorType & type, const CColor & color)
        {
            _colors[type] = color;
        }

        CColor CLight::GetColor(const LightColorType & type)
        {
            return _colors[type];
        }

        void CLight::SetAttenuation(const LightAttenuationType & type, float value)
        {
            _attenuations[type] = value;
        }

        float CLight::GetAttenuation(const LightAttenuationType & type)
        {
            return _attenuations[type];
        }
    }
}
