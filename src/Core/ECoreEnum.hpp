#ifndef _DEF_OMEGLOND3D_ENUMERATIONS_HPP
#define _DEF_OMEGLOND3D_ENUMERATIONS_HPP

namespace OMGL3D
{
    namespace CORE
    {
        enum MatrixType
        {
            OMGL_MATRIX_PROJECTION,
            OMGL_MATRIX_VIEW,
            OMGL_MATRIX_MODEL,
            OMGL_MATRIX_TEXTURE
        };

        enum TextureEnvironement {
            OMGL_TEXENV_STANDART,
            OMGL_TEXENV_SPLATTING,
        };

        enum TexCoordGeneration {
            OMGL_TEXCOORD_LINEAR,
            OMGL_TEXCOORD_EYE,
            OMGL_TEXCOORD_SPHERE
        };

        struct TexCoordPlane {
            float x, y, z, w;
            TexCoordGeneration type;
        };

        enum CubeMapOrientation {

            OMGL_CUBEMAP_LEFT,
            OMGL_CUBEMAP_RIGHT,

            OMGL_CUBEMAP_UP,
            OMGL_CUBEMAP_DOWN,

            OMGL_CUBEMAP_BEHIND,
            OMGL_CUBEMAP_FRONT
        };

        enum AlphaMode {
            OMGL_ALPHATEST_EQUAL,
            OMGL_ALPHATEST_GREATER
        };

        enum ColorBufferType {
            OMGL_COLOR_BUFFER_RGB,
            OMGL_COLOR_BUFFER_RGBA,
            OMGL_COLOR_BUFFER_DEPTH,
        };

        enum BlendingType
        {
            OMGL_BLENDING_ZERO,
            OMGL_BLENDING_ONE,

            OMGL_BLENDING_DESTINATION_COLOR,
            OMGL_BLENDING_SOURCE_COLOR,

            OMGL_BLENDING_MINUS_DESTINATION_COLOR,
            OMGL_BLENDING_MINUS_SOURCE_COLOR,

            OMGL_BLENDING_SOURCE_ALPHA,
            OMGL_BLENDING_MINUS_SOURCE_ALPHA,

            OMGL_BLENDING_DESTINATION_ALPHA,
            OMGL_BLENDING_MINUS_DESTINATION_ALPHA,

            OMGL_BLENDING_SOURCE_ALPHA_SATURATE
        };

        struct AlphaTest
        {
            AlphaTest() {}
            AlphaTest(const AlphaMode &m, float v) : mode(m), value(v) {}

            AlphaMode mode;
            float value;
        };

        struct BlendingMode
        {
            BlendingMode() {}
            BlendingMode(const BlendingType& source, const BlendingType &target) : mode_source(source), mode_target(target) {}

            BlendingType mode_source;
            BlendingType mode_target;
        };

        enum LightType {
            OMGL_LIGHT_POSITIONAL,
            OMGL_LIGHT_SPOT,
            OMGL_LIGHT_INFINITE,
        };

        enum LightColorType {
            OMGL_LIGHT_COLOR_AMBIENT,
            OMGL_LIGHT_COLOR_DIFUSE,
            OMGL_LIGHT_COLOR_SPECULAR
        };

        enum LightAttenuationType {
            OMGL_LIGHT_ATTENUATION_CONSTANT,
            OMGL_LIGHT_ATTENUATION_LINEAR,
            OMGL_LIGHT_ATTENUATION_QUADRATIC
        };

        enum ShaderType {
            OMGL_SHADERTYPE_VERTEX,
            OMGL_SHADERTYPE_PIXEL,
        };
    }
}

#endif
