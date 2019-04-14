#include "OGLShaderBaseGLSL.hpp"

#include "OGLExtention.hpp"
#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        OGLShaderBaseGLSL::OGLShaderBaseGLSL(const std::string & name, const CORE::ShaderType & type) : CORE::CShaderBase(name, type), _id(0)
        {
            OGLExtention & ext = OGLExtention::GetInstance();

            GLuint TypeShader[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
            _id = ext.glCreateShader(TypeShader[type]);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] program created : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGLShaderBaseGLSL::~OGLShaderBaseGLSL()
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            ext.glDeleteShader(_id);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] program deleted : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGLShaderBaseGLSL::SetSource(const char * source)
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            ext.glShaderSource(_id, 1, &source, 0);
        }

        void OGLShaderBaseGLSL::Compile()
        {
            OGLExtention & ext = OGLExtention::GetInstance();
            ext.glCompileShader(_id);

            GLint compile_status = GL_TRUE;
            ext.glGetShaderiv(_id, GL_COMPILE_STATUS, &compile_status);

            GLsizei logsize = 0;
            ext.glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logsize);

            char * log = new char[logsize+1];
            ext.glGetShaderInfoLog(_id, logsize, &logsize, log);

            if(logsize != 0) {
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] error compiling " << this->GetName() << " :\n" << log << UTILS::OMGL_LOGGER_FLUSH;
            }
            delete[] log;
        }

        void OGLShaderBaseGLSL::Enable()
        {
        }

        void OGLShaderBaseGLSL::Disable()
        {
        }

        void OGLShaderBaseGLSL::SetParameter(const std::string & name, const float * value)
        {
        }

        GLuint OGLShaderBaseGLSL::GetId() const
        {
            return _id;
        }
    }
}
