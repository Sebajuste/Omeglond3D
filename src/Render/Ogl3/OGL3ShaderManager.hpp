#ifndef _DEF_OMEGLOND3D_OGL3SHADERMANAGER_HPP
#define _DEF_OMEGLOND3D_OGL3SHADERMANAGER_HPP

#include "../../Utils/Pattern/Singleton.hpp"

#include <string>
#include <map>

namespace OMGL3D
{

namespace OGL3
{

enum OGL3AttribType {
    OMGL_OGL3_ATTRIB_VERTEX_POSITION,
    OMGL_OGL3_ATTRIB_VERTEX_COLOR,
    OMGL_OGL3_ATTRIB_VERTEX_NORMAL,
    OMGL_OGL3_ATTRIB_VERTEX_TEX_COORD
};

enum OGL3UniformType {
    OMGL_OGL3_UNIFORM_MODELVIEWPROJECTION_MATRIX
};

class OGL3ShaderManager : public UTILS::Singleton<OGL3ShaderManager>
{

public:

    OGL3ShaderManager();

    void SetAttrib(unsigned int id, const OGL3AttribType & type);

    unsigned int GetAttrib(const OGL3AttribType & type);

    void SetDefaultNameAttrib(const std::string & name, const OGL3AttribType & type);

    std::string GetDefaultNameAttrib(const OGL3AttribType & type);

    void SetUniform(unsigned int id, const OGL3UniformType & type);

    unsigned int GetUniform(const OGL3UniformType & type);

    void SetDefaultNameUniform(const std::string & name, const OGL3UniformType & type);

    std::string GetDefaultNameUniform(const OGL3UniformType & type);


private:

    typedef std::map<OGL3AttribType, unsigned int> AttribMap;
    typedef std::map<OGL3AttribType, std::string> AttribNameMap;

    typedef std::map<OGL3UniformType, unsigned int> UniformMap;
    typedef std::map<OGL3UniformType, std::string> UniformNameMap;

    AttribMap m_AttribMap;
    AttribNameMap m_AttribNameMap;

    UniformMap m_UniformMap;
    UniformNameMap m_UniformNameMap;

};


} // namespace OGL3

} // namespace OMGL3D

#endif
