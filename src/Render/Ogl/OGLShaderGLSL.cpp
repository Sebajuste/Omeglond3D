#include "OGLShaderGLSL.hpp"

#include "OGLExtention.hpp"
#include "OGLShaderBaseGLSL.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLShaderGLSL::OGLShaderGLSL(const std::string & name, OGLShaderBaseGLSL * vertex_shader, OGLShaderBaseGLSL * pixel_shader) : CShader(name), _id(0)
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            _id = ext.glCreateProgram();

            ext.glAttachShader(_id, vertex_shader->GetId() );
            ext.glAttachShader(_id, pixel_shader->GetId() );

            ext.glLinkProgram(_id);

            _vertexShader = vertex_shader;
            _pixelShader = pixel_shader;

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] shader created : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGLShaderGLSL::~OGLShaderGLSL()
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            ext.glDeleteProgram(_id);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] shader deleted : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGLShaderGLSL::Enable()
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            ext.glUseProgram(_id);
        }

        void OGLShaderGLSL::Disable()
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            ext.glUseProgram(0);
        }

        void OGLShaderGLSL::SetParameter(const std::string & name, const float & value)
        {
            OGLExtention & ext = OGLExtention::GetInstance();

            ext.glUseProgram(_id);
            GLuint object = ext.glGetUniformLocation(_id, name.c_str());
            if( object != 0 )
            {
                ext.glUniform1f(object, value);
            }
            ext.glUseProgram(0);
        }

        void OGLShaderGLSL::SetParameter(const std::string & name, const int & value)
        {
            OGLExtention & ext = OGLExtention::GetInstance();

            ext.glUseProgram(_id);
            GLuint object = ext.glGetUniformLocation(_id, name.c_str());
            if( object != 0 )
            {
                ext.glUniform1i(object, value);
            }
            ext.glUseProgram(0);
        }
    }
}
