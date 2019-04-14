#include "OGL3ShaderBaseGLSL.hpp"

#include "OGL3Extention.hpp"
#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3ShaderBaseGLSL::OGL3ShaderBaseGLSL(const std::string & name, const CORE::ShaderType & type) : CORE::CShaderBase(name, type), _id(0)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            GLuint TypeShader[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
            _id = ext.glCreateShader(TypeShader[type]);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] program created : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGL3ShaderBaseGLSL::~OGL3ShaderBaseGLSL()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glDeleteShader(_id);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] program deleted : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGL3ShaderBaseGLSL::SetSource(const char * source)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glShaderSource(_id, 1, &source, 0);
        }

        void OGL3ShaderBaseGLSL::Compile()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
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

        void OGL3ShaderBaseGLSL::Enable()
        {
        }

        void OGL3ShaderBaseGLSL::Disable()
        {
        }

        void OGL3ShaderBaseGLSL::SetParameter(const std::string & name, const float * value)
        {
        }

        GLuint OGL3ShaderBaseGLSL::GetId() const
        {
            return _id;
        }
    }
}
