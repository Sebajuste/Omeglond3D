#ifndef _DEF_OMEGLOND3D_OGLEXTENTION_HPP
#define _DEF_OMEGLOND3D_OGLEXTENTION_HPP

#if defined (WIN32)

    #define GL3_PROTOTYPES 1

    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL3/gl3.h>
    //#include <GL/glext.h>
#else
    #include <GL/glx.h>
#endif

#include <string>
#include <vector>

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
    namespace OGL3
    {
        class OGL3Extention
        {

        public:

            static OGL3Extention & GetInstance();

            void CheckExtentions();

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
            PFNGLGENBUFFERSPROC glGenBuffers;
            PFNGLDELETEBUFFERSPROC glDeleteBuffers;
            PFNGLBINDBUFFERPROC glBindBuffer;
            PFNGLBUFFERDATAPROC  glBufferData;
            PFNGLBUFFERSUBDATAPROC glBufferSubData;
            PFNGLMAPBUFFERPROC glMapBuffer;
            PFNGLUNMAPBUFFERPROC glUnmapBuffer;

            PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
            PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
            PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

            // texturing
            //PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
            PFNGLACTIVETEXTUREPROC glActiveTexture;
            //PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;


            // Point Sprite
            PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
            PFNGLPOINTPARAMETERFPROC glPointParameterf;

            // Shaders
            //PFNGLCREATESHADEROBJECTPROC glCreateShaderObject;
            PFNGLCREATESHADERPROC glCreateShader;
            PFNGLDELETESHADERPROC glDeleteShader;
            PFNGLSHADERSOURCEPROC glShaderSource;
            PFNGLCOMPILESHADERPROC glCompileShader;
            PFNGLGETSHADERIVPROC glGetShaderiv;
            PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

            PFNGLCREATEPROGRAMPROC glCreateProgram;
            PFNGLDELETEPROGRAMPROC glDeleteProgram;
            PFNGLATTACHSHADERPROC glAttachShader;
            PFNGLDETACHSHADERPROC glDetachShader;
            PFNGLLINKPROGRAMPROC glLinkProgram;
            PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
            PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
            PFNGLUNIFORM1IPROC glUniform1i;
            PFNGLUNIFORM1FPROC glUniform1f;
            PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
            PFNGLUSEPROGRAMPROC glUseProgram;

            // Frame Buffer Object
            PFNGLISRENDERBUFFERPROC glIsRenderbuffer;
            PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
            PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
            PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
            PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
            PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;
            PFNGLISFRAMEBUFFERPROC glIsFramebuffer;
            PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
            PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
            PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
            PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
            PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
            PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
            PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;
            PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
            PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
            PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

        private:

            OGL3Extention();

            //std::string m_Extentions;
            std::vector<std::string> m_Extentions;

            static OGL3Extention m_Instance;
        };
    }
}

#endif
