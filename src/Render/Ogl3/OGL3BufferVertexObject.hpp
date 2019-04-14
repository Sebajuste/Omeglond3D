#ifndef _DEF_OMEGLOND3D_OGL3BUFFERVERTEXOBJECT_HPP
#define _DEF_OMEGLOND3D_OGL3BUFFERVERTEXOBJECT_HPP

#define GL3_PROTOTYPES 1

#include <GL3/gl3.h>

#include "../../Core/IBufferBase.hpp"

#include "OGL3Extention.hpp"

#include "../../Debug/DebugAllocation.hpp"

#include "../../Utils/Logger/ILogger.hpp"

namespace OMGL3D
{
    namespace OGL3
    {
        template <GLenum Type> class OGL3BufferVertexObject : public CORE::IBufferBase
        {

        public:

            OGL3BufferVertexObject(unsigned int size, unsigned int stride);

            ~OGL3BufferVertexObject();

            unsigned char * Lock(unsigned int offset, unsigned int size);

            const unsigned char * ConstLock(unsigned int offset, unsigned int size) const;

            void Unlock() const;

            GLuint & GetId();

        private:

            GLuint _id;
        };

        template <GLenum Type> OGL3BufferVertexObject<Type>::OGL3BufferVertexObject(unsigned int size, unsigned int stride) : CORE::IBufferBase(size, stride)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();

            ext.glGenBuffers(1, &_id);

            ext.glBindBuffer(Type, _id);
            ext.glBufferData(Type, size * stride, 0, GL_DYNAMIC_DRAW);

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

        template <GLenum Type> OGL3BufferVertexObject<Type>::~OGL3BufferVertexObject()
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glDeleteBuffers(1, &_id);
            UTILS::ILogger::GetLogger(UTILS::OMGL_LOGGER_RENDERER) << "[VBO] delete | id=" << _id << UTILS::OMGL_LOGGER_FLUSH;
        }

        template <GLenum Type> unsigned char * OGL3BufferVertexObject<Type>::Lock(unsigned int offset, unsigned int size)
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glBindBuffer(Type, _id);
            unsigned char * buffer = reinterpret_cast<unsigned char*>(ext.glMapBuffer(Type, GL_READ_WRITE));
            return buffer + offset;
        }

        template <GLenum Type> const unsigned char * OGL3BufferVertexObject<Type>::ConstLock(unsigned int offset, unsigned int size) const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glBindBuffer(Type, _id);
            unsigned char * buffer = reinterpret_cast<unsigned char*>(ext.glMapBuffer(Type, GL_READ_WRITE));
            return buffer + offset;
        }

        template <GLenum Type> void OGL3BufferVertexObject<Type>::Unlock() const
        {
            OGL3Extention & ext = OGL3Extention::GetInstance();
            ext.glUnmapBuffer(Type);
        }

        template <GLenum Type> GLuint & OGL3BufferVertexObject<Type>::GetId()
        {
            return _id;
        }

        typedef OGL3BufferVertexObject<GL_ARRAY_BUFFER> OGL3VertexBufferObject;
        typedef OGL3BufferVertexObject<GL_ELEMENT_ARRAY_BUFFER> OGL3IndexBufferObject;
    }
}

#endif
