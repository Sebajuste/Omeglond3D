#include "OGL3ShaderGLSL.hpp"

#include "OGL3Extention.hpp"
#include "OGL3ShaderManager.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        OGL3ShaderGLSL::OGL3ShaderGLSL(const std::string & name, OGL3ShaderBaseGLSL * vertex_shader, OGL3ShaderBaseGLSL * pixel_shader) : CShader(name), _id(0)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            _id = ext.glCreateProgram();

            ext.glAttachShader(_id, vertex_shader->GetId() );
            ext.glAttachShader(_id, pixel_shader->GetId() );

            ext.glLinkProgram(_id);

            _vertexShader = vertex_shader;
            _pixelShader = pixel_shader;


            // Récupération des variables

            OGL3ShaderManager & shader_manager = OGL3ShaderManager::GetInstance();

            std::string modelviewprojection_matrix = shader_manager.GetDefaultNameUniform(OMGL_OGL3_UNIFORM_MODELVIEWPROJECTION_MATRIX);
            std::string vertexPosition = shader_manager.GetDefaultNameAttrib(OMGL_OGL3_ATTRIB_VERTEX_POSITION);
            std::string vertexNormal = shader_manager.GetDefaultNameAttrib(OMGL_OGL3_ATTRIB_VERTEX_NORMAL);
            std::string vertexColor = shader_manager.GetDefaultNameAttrib(OMGL_OGL3_ATTRIB_VERTEX_COLOR);
            std::string vertexTexCoord = shader_manager.GetDefaultNameAttrib(OMGL_OGL3_ATTRIB_VERTEX_TEX_COORD);


            m_MatrixID = ext.glGetUniformLocation(_id, modelviewprojection_matrix.c_str());
            m_VertexPositionID = ext.glGetAttribLocation(_id, vertexPosition.c_str());
            m_VertexNormalID = ext.glGetAttribLocation(_id, vertexNormal.c_str());
            m_VertexColorID = ext.glGetAttribLocation(_id, vertexColor.c_str());
            m_VertexTexCoordID = ext.glGetAttribLocation(_id, vertexTexCoord.c_str());


            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] shader created : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        OGL3ShaderGLSL::~OGL3ShaderGLSL()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glDeleteProgram(_id);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[Shader GLSL] shader deleted : " << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        void OGL3ShaderGLSL::Enable()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glUseProgram(_id);

            OGL3ShaderManager & shader_manager = OGL3ShaderManager::GetInstance();
            shader_manager.SetUniform(m_MatrixID, OMGL_OGL3_UNIFORM_MODELVIEWPROJECTION_MATRIX);

            shader_manager.SetAttrib(m_VertexPositionID, OMGL_OGL3_ATTRIB_VERTEX_POSITION);
            shader_manager.SetAttrib(m_VertexNormalID, OMGL_OGL3_ATTRIB_VERTEX_NORMAL);
            shader_manager.SetAttrib(m_VertexColorID, OMGL_OGL3_ATTRIB_VERTEX_COLOR);
            shader_manager.SetAttrib(m_VertexTexCoordID, OMGL_OGL3_ATTRIB_VERTEX_TEX_COORD);
        }

        void OGL3ShaderGLSL::Disable()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glUseProgram(0);
        }

        void OGL3ShaderGLSL::SetParameter(const std::string & name, const float & value)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            ext.glUseProgram(_id);
            GLuint object = ext.glGetUniformLocation(_id, name.c_str());
            if( object != 0 )
            {
                ext.glUniform1f(object, value);
            }
            ext.glUseProgram(0);
        }

        void OGL3ShaderGLSL::SetParameter(const std::string & name, const int & value)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

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
