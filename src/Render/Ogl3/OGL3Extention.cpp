#include "OGL3Extention.hpp"

//#include <iostream>

#include "../../Utils/Logger/ILogger.hpp"

#if defined (WIN32)
    #define getProcAddress wglGetProcAddress
    #define TYPE char
#else
    #define TYPE GLubyte
    #if defined(__APPLE__)
        #define getProcAddress NSGLGetProcAddress
    #else
        #define getProcAddress glXGetProcAddress
    #endif
#endif

#define LOAD_EXTENTION(ext) LoadExtention(ext, #ext)

namespace OMGL3D
{
    namespace OGL3
    {

        template <typename T> inline void LoadExtention(T & proc, const char * name)
        {
            if( !(proc = reinterpret_cast<T>( getProcAddress((TYPE*)name)) ) )
            {
                proc = 0;
                UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "Error loading extention " << name << UTILS::OMGL_LOGGER_FLUSH;
            }
        }

        OGL3Extention::OGL3Extention()
        {
            VertexArray = false;
            VertexBufferObject = false;
            MultiTexturing = false;
            ShaderGLSL = false;
            TextureCubeMap = false;
            FrameBufferObject = false;

            glGenBuffers = 0;
            glDeleteBuffers = 0;
            glBindBuffer = 0;
            glBufferData = 0;
            glBufferSubData = 0;
            glMapBuffer = 0;

            // texturing
            //glMultiTexCoord2f =0;
            glActiveTexture = 0;
            //glClientActiveTexture = 0;


            // Point Sprite
            glPointParameterfv = 0;
            glPointParameterf = 0;

            // Shaders
            //glCreateShaderObjectARB = 0;
            glCreateShader = 0;
            glDeleteShader = 0;
            glShaderSource = 0;
            glCompileShader = 0;
            glGetShaderiv = 0;
            glGetShaderInfoLog = 0;

            glCreateProgram = 0;
            glDeleteProgram = 0;
            glAttachShader = 0;
            glDetachShader = 0;
            glLinkProgram = 0;
            glGetAttribLocation = 0;
            glGetUniformLocation = 0;
            glUniform1i = 0;
            glUniform1f = 0;
            glUseProgram = 0;

            // Frame Buffer Object
            glIsRenderbuffer = 0;
            glBindRenderbuffer = 0;
            glDeleteRenderbuffers = 0;
            glGenRenderbuffers = 0;
            glRenderbufferStorage = 0;
            glGetRenderbufferParameteriv = 0;
            glIsFramebuffer = 0;
            glBindFramebuffer = 0;
            glDeleteFramebuffers = 0;
            glGenFramebuffers = 0;
            glCheckFramebufferStatus = 0;
            glFramebufferTexture1D = 0;
            glFramebufferTexture2D = 0;
            glFramebufferTexture3D = 0;
            glFramebufferRenderbuffer = 0;
            glGetFramebufferAttachmentParameteriv = 0;
            glGenerateMipmap = 0;


        }

        OGL3Extention & OGL3Extention::GetInstance()
        {
            return m_Instance;
        }

        void OGL3Extention::CheckExtentions()
        {
            GLint n, i;
            glGetIntegerv(GL_NUM_EXTENSIONS, &n);
            for (i=0; i<n; i++) {

                //std::string extention = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
                //m_Extentions.push_back(extention);
            }

        }

        bool OGL3Extention::FindExtention(const std::string &extention) const
        {
            std::vector<std::string>::const_iterator it;

            for(it=m_Extentions.begin(); it!=m_Extentions.end(); ++it)
            {
                if( *it == extention ) return true;
            }

            return false;
        }

        void OGL3Extention::LoadAllExtention()
        {

            // VBO
            LOAD_EXTENTION(glGenBuffers);
            LOAD_EXTENTION(glDeleteBuffers);
            LOAD_EXTENTION(glBindBuffer);
            LOAD_EXTENTION(glBufferData);
            LOAD_EXTENTION(glBufferSubData);
            LOAD_EXTENTION(glMapBuffer);
            LOAD_EXTENTION(glUnmapBuffer);

            LOAD_EXTENTION(glEnableVertexAttribArray);
            LOAD_EXTENTION(glDisableVertexAttribArray);
            LOAD_EXTENTION(glVertexAttribPointer);


            // Multi-texturing
            //LOAD_EXTENTION(glMultiTexCoord2f);
            LOAD_EXTENTION(glActiveTexture);
            //LOAD_EXTENTION(glClientActiveTexture);


            // Shader
            LOAD_EXTENTION(glCreateProgram);
            LOAD_EXTENTION(glDeleteProgram);
            LOAD_EXTENTION(glAttachShader);
            LOAD_EXTENTION(glDetachShader);
            LOAD_EXTENTION(glLinkProgram);
            LOAD_EXTENTION(glUseProgram);

            LOAD_EXTENTION(glCreateShader);
            LOAD_EXTENTION(glDeleteShader);
            LOAD_EXTENTION(glShaderSource);
            LOAD_EXTENTION(glCompileShader);
            LOAD_EXTENTION(glGetShaderiv);
            LOAD_EXTENTION(glGetShaderInfoLog);
            LOAD_EXTENTION(glGetAttribLocation);
            LOAD_EXTENTION(glGetUniformLocation);
            LOAD_EXTENTION(glUniform1i);
            LOAD_EXTENTION(glUniform1f);
            LOAD_EXTENTION(glUniformMatrix4fv);

            // Frame buffer
            LOAD_EXTENTION(glIsRenderbuffer);
            LOAD_EXTENTION(glBindRenderbuffer);
            LOAD_EXTENTION(glDeleteRenderbuffers);
            LOAD_EXTENTION(glGenRenderbuffers);
            LOAD_EXTENTION(glRenderbufferStorage);
            LOAD_EXTENTION(glGetRenderbufferParameteriv);
            LOAD_EXTENTION(glIsFramebuffer);
            LOAD_EXTENTION(glBindFramebuffer);
            LOAD_EXTENTION(glDeleteFramebuffers);
            LOAD_EXTENTION(glGenFramebuffers);
            LOAD_EXTENTION(glCheckFramebufferStatus);
            LOAD_EXTENTION(glFramebufferTexture1D);
            LOAD_EXTENTION(glFramebufferTexture2D);
            LOAD_EXTENTION(glFramebufferTexture3D);
            LOAD_EXTENTION(glFramebufferRenderbuffer);
            LOAD_EXTENTION(glGetFramebufferAttachmentParameteriv);
            LOAD_EXTENTION(glGenerateMipmap);

            if( FindExtention("GL_EXT_vertex_array") )
            {
                VertexArray = true;
            }

            if( FindExtention("GL_ARB_texture_cube_map") )
            {
                TextureCubeMap = true;
            }

            if( FindExtention("GL_ARB_vertex_buffer_object") )
            {

                VertexBufferObject = true;
            }

            if( FindExtention("GL_ARB_multitexture") )
            {
                MultiTexturing = true;


            }

            if( FindExtention("GL_ARB_point_sprite") )
            {
                //pointSprite = true;
                LOAD_EXTENTION(glPointParameterfv);
                LOAD_EXTENTION(glPointParameterf);

            }

            if( FindExtention("GL_ARB_shading_language_100") )
            {
            } else {
                //_messages->addMessage("[Renderer] Shaders are not supported");
            }


            if( FindExtention("GL_ARB_shader_objects") )
            {
                ShaderGLSL = true;
                //LOAD_EXTENTION(glCreateShaderObjectARB);


            }

            if( FindExtention("GL_ARB_vertex_shader") )
            {

            }

            if( FindExtention("GL_ARB_fragment_shader") )
            {

            }

            if( FindExtention("GL_EXT_framebuffer_object") )
            {
                FrameBufferObject = true;


            }
        }

        OGL3Extention OGL3Extention::m_Instance;
    }
}
