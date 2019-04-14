#ifndef _DEF_OMEGLOND3D_ILIGHT_HPP
#define _DEF_OMEGLOND3D_ILIGHT_HPP

#include "CResource.hpp"
#include "ECoreEnum.hpp"
#include "CColor.hpp"

#include "../Math/Vector3.hpp"

namespace OMGL3D
{
    namespace CORE
    {
        class ILight : public CResource
        {

        public:

            ILight(const std::string & name) : CResource(name) {}

            virtual ~ILight() {}

            virtual LightType GetType() const=0;

            virtual void SetType(const LightType & type)=0;

            virtual void SetPosition(const MATH::Vector3f & vector)=0;

            virtual MATH::Vector3f GetPosition() const=0;

            virtual int GetCutoff() const=0;

            virtual void SetCutoff(int cutoff)=0;

            virtual MATH::Vector3f GetBeamVector() const=0;

            virtual void SetBeamVector(const MATH::Vector3f & vector)=0;

            virtual void SetColor(const LightColorType & type, const CColor & color)=0;

            virtual CColor GetColor(const LightColorType & type)=0;

            virtual void SetAttenuation(const LightAttenuationType & type, float value)=0;

            virtual float GetAttenuation(const LightAttenuationType & type)=0;

            virtual void Enable(unsigned int canal=0)=0;

            virtual void Disable(unsigned int canal=0)=0;
        };
    }
}

#endif
