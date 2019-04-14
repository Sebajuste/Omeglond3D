#include "OGLLight.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLLight::OGLLight(const std::string & name) : CORE::CLight(name)
        {
            glGetIntegerv(GL_MAX_LIGHTS, &_max_lights);
        }

        OGLLight::~OGLLight()
        {
        }

        void OGLLight::Enable(unsigned int canal)
        {
            GLfloat position[4] = {0.0f, 0.0f, 1.0f, 0.0f};

            GLenum enum_light = GL_LIGHT0;

            if( (int)canal < _max_lights ) {
                enum_light += canal;
            }

            glEnable(enum_light);
            glEnable( GL_LIGHTING );

            glLightfv(enum_light, GL_AMBIENT, *_colors[CORE::OMGL_LIGHT_COLOR_AMBIENT]);
            glLightfv(enum_light, GL_DIFFUSE, *_colors[CORE::OMGL_LIGHT_COLOR_DIFUSE]);
            glLightfv(enum_light, GL_SPECULAR, *_colors[CORE::OMGL_LIGHT_COLOR_SPECULAR]);

            position[0] = _position.x;
            position[1] = _position.y;
            position[2] = _position.z;

            switch(_type)
            {
                case CORE::OMGL_LIGHT_INFINITE:
                {
                    position[3] = 0.0f;
                    break;
                }

                case CORE::OMGL_LIGHT_POSITIONAL:
                    position[3]=1.0;
                    break;

                case CORE::OMGL_LIGHT_SPOT:
                    position[3]=1.0;
                    glLighti(enum_light, GL_SPOT_CUTOFF, (GLint)_cutoff);
                    break;

                default:
                    position[3]=1.0;
                    break;
            }

            glLightfv(enum_light, GL_POSITION, position);

            glLightfv(enum_light, GL_SPOT_DIRECTION, &_beamVector.x);

            glLightf(enum_light, GL_CONSTANT_ATTENUATION, _attenuations[CORE::OMGL_LIGHT_ATTENUATION_CONSTANT]);
            glLightf(enum_light, GL_LINEAR_ATTENUATION, _attenuations[CORE::OMGL_LIGHT_ATTENUATION_LINEAR]);
            glLightf(enum_light, GL_QUADRATIC_ATTENUATION, _attenuations[CORE::OMGL_LIGHT_ATTENUATION_QUADRATIC]);

        }

        void OGLLight::Disable(unsigned int canal)
        {
            glDisable( GL_LIGHTING );

            GLenum enum_light = GL_LIGHT0;

            if( (int)canal < _max_lights ) {
                enum_light += canal;
            }

            glDisable(enum_light);
        }

        GLint OGLLight::_max_lights=0;
    }
}
