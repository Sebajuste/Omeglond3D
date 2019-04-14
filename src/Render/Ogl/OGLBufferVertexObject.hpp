#ifndef _DEF_OMEGLOND3D_OGLBUFFERVERTEXOBJECT_HPP
#define _DEF_OMEGLOND3D_OGLBUFFERVERTEXOBJECT_HPP

#include "../../Core/IBufferBase.hpp"

#include "OGLExtention.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL
    {
        template <GLenum Type> class OGLBufferVertexObject : public CORE::IBufferBase
        {

        public:

            OGLBufferVertexObject(unsigned int size, unsigned int stride);

            ~OGLBufferVertexObject();

            unsigned char * Lock(unsigned int offset, unsigned int size);

            const unsigned char * ConstLock(unsigned int offset, unsigned int size) const;

            void Unlock() const;

            GLuint & GetId();

        private:

            GLuint _id;
        };

        template <GLenum Type> OGLBufferVertexObject<Type>::OGLBufferVertexObject(unsigned int size, unsigned int stride) : CORE::IBufferBase(size, stride)
        {
            OGLExtention & ext = OGLExtention::GetInstance();

            ext.glGenBuffersARB(1, &_id);

            ext.glBindBufferARB(Type, _id);
            ext.glBufferDataARB(Type, size * stride, 0, GL_DYNAMIC_DRAW_ARB);

            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[VBO] create | id=" << _id << UTILS::OMGL_LOGGER_FLUSH;

            /*
            GL_STATIC_DRAW_ARB
            GL_STATIC_READ_ARB
            GL_STATIC_COPY_ARB
            GL_DYNAMIC_DRAW_ARB
            GL_DYNAMIC_READ_ARB
            GL_DYNAMIC_COPY_ARB
            GL_STREAM_DRAW_ARB
            GL_STREAM_READ_ARB
            GL_STREAM_COPY_ARB
            */
        }

        template <GLenum Type> OGLBufferVertexObject<Type>::~OGLBufferVertexObject()
        {
            OGLExtention::GetInstance().glDeleteBuffersARB(1, &_id);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[VBO] delete | id=" << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        template <GLenum Type> unsigned char * OGLBufferVertexObject<Type>::Lock(unsigned int offset, unsigned int size)
        {
            OGLExtention & ext = OGLExtention::GetInstance();

            ext.glBindBufferARB(Type, _id);
            unsigned char * buffer = reinterpret_cast<unsigned char*>(ext.glMapBufferARB(Type, GL_READ_WRITE_ARB));

            return buffer + offset;
        }

        template <GLenum Type> const unsigned char * OGLBufferVertexObject<Type>::ConstLock(unsigned int offset, unsigned int size) const
        {
            OGLExtention & ext = OGLExtention::GetInstance();

            ext.glBindBufferARB(Type, _id);
            unsigned char * buffer = reinterpret_cast<unsigned char*>(ext.glMapBufferARB(Type, GL_READ_WRITE_ARB));

            return buffer + offset;
        }

        template <GLenum Type> void OGLBufferVertexObject<Type>::Unlock() const
        {
            OGLExtention::GetInstance().glUnmapBufferARB(Type);
        }

        template <GLenum Type> GLuint & OGLBufferVertexObject<Type>::GetId()
        {
            return _id;
        }

        typedef OGLBufferVertexObject<GL_ARRAY_BUFFER_ARB> OGLVertexBufferObject;
        typedef OGLBufferVertexObject<GL_ELEMENT_ARRAY_BUFFER_ARB> OGLIndexBufferObject;
    }
}

#endif
