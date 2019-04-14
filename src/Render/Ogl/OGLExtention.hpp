#ifndef _DEF_OMEGLOND3D_OGLEXTENTION_HPP
#define _DEF_OMEGLOND3D_OGLEXTENTION_HPP

#if defined (WIN32)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
#else
    #include <GL/glx.h>
#endif

#include <string>

#define GL_NORMAL_MAP_ARB                   0x8511
#define GL_REFLECTION_MAP_ARB               0x8512
#define GL_TEXTURE_CUBE_MAP_ARB             0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB     0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB  0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB       0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB    0x851C

#define WGL_SAMPLE_BUFFERS_ARB	0x2041
#define WGL_SAMPLES_ARB		    0x2042


namespace OMGL3D
{
    namespace OGL
    {
        class OGLExtention
        {

        public:

            static OGLExtention & GetInstance();

            std::string CheckExtentions();

            bool FindExtention(const std::string &extention) const;

            void LoadAllExtention();

            bool AntiAliasing;

            bool VertexArray;
            bool VertexBufferObject;

            bool MultiTexturing;

            bool ShaderGLSL;

            bool TextureCubeMap;
            bool FrameBufferObject;

            // Antialiasing



            // pour les VBO
            PFNGLGENBUFFERSARBPROC glGenBuffersARB;
            PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
            PFNGLBINDBUFFERARBPROC glBindBufferARB;
            PFNGLBUFFERDATAARBPROC  glBufferDataARB;
            PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
            PFNGLMAPBUFFERARBPROC glMapBufferARB;
            PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;

            // texturing
            PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
            PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
            PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB;


            // Point Sprite
            PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;
            PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB;

            // Shaders
            PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
            PFNGLCREATESHADERPROC glCreateShader;
            PFNGLDELETESHADERPROC glDeleteShader;
            PFNGLSHADERSOURCEARBPROC glShaderSource;
            PFNGLCOMPILESHADERARBPROC glCompileShader;
            PFNGLGETSHADERIVPROC glGetShaderiv;
            PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

            PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgram;
            PFNGLDELETEOBJECTARBPROC glDeleteProgram;
            PFNGLATTACHOBJECTARBPROC glAttachShader;
            PFNGLDETACHOBJECTARBPROC glDetachShader;
            PFNGLLINKPROGRAMARBPROC glLinkProgram;
            PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocation;
            PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocation;
            PFNGLUNIFORM1IARBPROC glUniform1i;
            PFNGLUNIFORM1FARBPROC glUniform1f;
            PFNGLUSEPROGRAMOBJECTARBPROC glUseProgram;

            // Frame Buffer Object
            PFNGLISRENDERBUFFEREXTPROC glIsRenderbuffer;
            PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbuffer;
            PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffers;
            PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffers;
            PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorage;
            PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameteriv;
            PFNGLISFRAMEBUFFEREXTPROC glIsFramebuffer;
            PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebuffer;
            PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffers;
            PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffers;
            PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatus;
            PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1D;
            PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2D;
            PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3D;
            PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbuffer;
            PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameteriv;
            PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmap;

        private:

            OGLExtention();

            std::string m_Extentions;

            static OGLExtention m_Instance;
        };
    }
}

#endif
