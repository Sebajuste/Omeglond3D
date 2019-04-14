#ifndef _DEF_OMEGLOND3D_CLIGHT_HPP
#define _DEF_OMEGLOND3D_CLIGHT_HPP

#include "ILight.hpp"
#include <map>

namespace OMGL3D
{
    namespace CORE
    {
        class CLight : public ILight
        {

        public:

            CLight(const std::string & name);

            virtual ~CLight();

            LightType GetType() const;

            void SetType(const LightType & type);

            void SetPosition(const MATH::Vector3f & vector);

            MATH::Vector3f GetPosition() const;

            int GetCutoff() const;

            void SetCutoff(int cutoff);

            MATH::Vector3f GetBeamVector() const;

            void SetBeamVector(const MATH::Vector3f & vector);

            void SetColor(const LightColorType & type, const CColor & color);

            CColor GetColor(const LightColorType & type);

            void SetAttenuation(const LightAttenuationType & type, float value);

            float GetAttenuation(const LightAttenuationType & type);

            virtual void Enable(unsigned int canal)=0;

            virtual void Disable(unsigned int canal)=0;



        protected:

            LightType _type;
            MATH::Vector3f _position;

            int _cutoff;
            MATH::Vector3f _beamVector;

            std::map<LightColorType, CColor> _colors;
            std::map<LightAttenuationType, float> _attenuations;
        };
    }
}

#endif
