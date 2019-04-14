#include "OGL3ShaderManager.hpp"

namespace OMGL3D
{

namespace OGL3
{

OGL3ShaderManager::OGL3ShaderManager()
{
    m_AttribNameMap[OMGL_OGL3_ATTRIB_VERTEX_POSITION] = "VertexPosition";
    m_AttribNameMap[OMGL_OGL3_ATTRIB_VERTEX_COLOR] = "VertexColor";
    m_AttribNameMap[OMGL_OGL3_ATTRIB_VERTEX_NORMAL] = "VertexNormal";
    m_AttribNameMap[OMGL_OGL3_ATTRIB_VERTEX_TEX_COORD] = "VertexTexCoord";

    m_UniformNameMap[OMGL_OGL3_UNIFORM_MODELVIEWPROJECTION_MATRIX] = "ModelViewProjectionMatrix";
}

void OGL3ShaderManager::SetAttrib(unsigned int id, const OGL3AttribType & type)
{
    m_AttribMap[type] = id;
}

unsigned int OGL3ShaderManager::GetAttrib(const OGL3AttribType & type)
{
    AttribMap::const_iterator it = m_AttribMap.find(type);

    if( it != m_AttribMap.end() )
        return (*it).second;

    return 0;
}

void OGL3ShaderManager::SetDefaultNameAttrib(const std::string & name, const OGL3AttribType & type)
{
    m_AttribNameMap[type] = name;
}

std::string OGL3ShaderManager::GetDefaultNameAttrib(const OGL3AttribType & type)
{
    AttribNameMap::const_iterator it = m_AttribNameMap.find(type);

    if( it != m_AttribNameMap.end() )
        return (*it).second;

    return "";
}

void OGL3ShaderManager::SetUniform(unsigned int id, const OGL3UniformType & type)
{
    m_UniformMap[type] = id;
}

unsigned int OGL3ShaderManager::GetUniform(const OGL3UniformType & type)
{
    UniformMap::const_iterator it = m_UniformMap.find(type);

    if( it != m_UniformMap.end() )
        return (*it).second;

    return 0;
}

void OGL3ShaderManager::SetDefaultNameUniform(const std::string & name, const OGL3UniformType & type)
{
    m_UniformNameMap[type] = name;
}

std::string OGL3ShaderManager::GetDefaultNameUniform(const OGL3UniformType & type)
{
    UniformNameMap::const_iterator it = m_UniformNameMap.find(type);

    if( it != m_UniformNameMap.end() )
        return (*it).second;

    return "";
}

} // namespace OGL3

} // namespace OMGL3D
