#include "OGLExtention.hpp"

#include <iostream>

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
    namespace OGL
    {

        template <typename T> inline void LoadExtention(T & proc, const char * name)
        {
            if( !(proc = reinterpret_cast<T>( getProcAddress((TYPE*)name)) ) )
            {
                proc = 0;
            }
        }

        OGLExtention::OGLExtention()
        {
            VertexArray = false;
            VertexBufferObject = false;
            MultiTexturing = false;
            ShaderGLSL = false;
            TextureCubeMap = false;
            FrameBufferObject = false;

            glGenBuffersARB = 0;
            glDeleteBuffersARB = 0;
            glBindBufferARB = 0;
            glBufferDataARB = 0;
            glBufferSubDataARB = 0;
            glMapBufferARB = 0;

            // texturing
            glMultiTexCoord2fARB =0;
            glActiveTextureARB = 0;
            glClientActiveTextureARB = 0;


            // Point Sprite
            glPointParameterfvARB = 0;
            glPointParameterfARB = 0;

            // Shaders
            glCreateShaderObjectARB = 0;
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

        OGLExtention & OGLExtention::GetInstance()
        {
            return m_Instance;
        }

        std::string OGLExtention::CheckExtentions()
        {
            m_Extentions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
            return m_Extentions;
        }

        bool OGLExtention::FindExtention(const std::string &extention) const
        {
            if (m_Extentions.find(extention) != std::string::npos) {
                return true;
            }
            return false;
        }

        void OGLExtention::LoadAllExtention()
        {
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
                LOAD_EXTENTION(glGenBuffersARB);
                LOAD_EXTENTION(glDeleteBuffersARB);
                LOAD_EXTENTION(glBindBufferARB);
                LOAD_EXTENTION(glBufferDataARB);
                LOAD_EXTENTION(glBufferSubDataARB);
                LOAD_EXTENTION(glMapBufferARB);
                LOAD_EXTENTION(glUnmapBufferARB);
                VertexBufferObject = true;
            }

            if( FindExtention("GL_ARB_multitexture") )
            {
                MultiTexturing = true;
                LOAD_EXTENTION(glMultiTexCoord2fARB);
                LOAD_EXTENTION(glActiveTextureARB);
                LOAD_EXTENTION(glClientActiveTextureARB);

            }

            if( FindExtention("GL_ARB_point_sprite") )
            {
                //pointSprite = true;
                LOAD_EXTENTION(glPointParameterfvARB);
                LOAD_EXTENTION(glPointParameterfARB);

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

                LOAD_EXTENTION(glCreateProgram);
                LOAD_EXTENTION(glDeleteProgram);
                LOAD_EXTENTION(glAttachShader);
                LOAD_EXTENTION(glDetachShader);
                LOAD_EXTENTION(glLinkProgram);

                LOAD_EXTENTION(glUseProgram);
            }

            if( FindExtention("GL_ARB_vertex_shader") )
            {
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
            }

            if( FindExtention("GL_ARB_fragment_shader") )
            {

            }

            if( FindExtention("GL_EXT_framebuffer_object") )
            {
                FrameBufferObject = true;

                glIsRenderbuffer = (PFNGLISRENDERBUFFEREXTPROC) getProcAddress((TYPE*)"glIsRenderbufferEXT");
                glBindRenderbuffer = (PFNGLBINDRENDERBUFFEREXTPROC) getProcAddress((TYPE*)"glBindRenderbufferEXT");
                glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSEXTPROC) getProcAddress((TYPE*)"glDeleteRenderbuffersEXT");
                glGenRenderbuffers = (PFNGLGENRENDERBUFFERSEXTPROC) getProcAddress((TYPE*)"glGenRenderbuffersEXT");
                glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEEXTPROC) getProcAddress((TYPE*)"glRenderbufferStorageEXT");
                glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC) getProcAddress((TYPE*)"glGetRenderbufferParameterivEXT");
                glIsFramebuffer = (PFNGLISFRAMEBUFFEREXTPROC) getProcAddress((TYPE*)"glIsFramebufferEXT");
                glBindFramebuffer = (PFNGLBINDFRAMEBUFFEREXTPROC) getProcAddress((TYPE*)"glBindFramebufferEXT");
                glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSEXTPROC) getProcAddress((TYPE*)"glDeleteFramebuffersEXT");
                glGenFramebuffers = (PFNGLGENFRAMEBUFFERSEXTPROC) getProcAddress((TYPE*)"glGenFramebuffersEXT");
                glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) getProcAddress((TYPE*)"glCheckFramebufferStatusEXT");
                glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC) getProcAddress((TYPE*)"glFramebufferTexture1DEXT");
                glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) getProcAddress((TYPE*)"glFramebufferTexture2DEXT");
                glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC) getProcAddress((TYPE*)"glFramebufferTexture3DEXT");
                glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) getProcAddress((TYPE*)"glFramebufferRenderbufferEXT");
                glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) getProcAddress((TYPE*)"glGetFramebufferAttachmentParameterivEXT");
                glGenerateMipmap = (PFNGLGENERATEMIPMAPEXTPROC) getProcAddress((TYPE*)"glGenerateMipmapEXT");

            }
        }

        OGLExtention OGLExtention::m_Instance;
    }
}
