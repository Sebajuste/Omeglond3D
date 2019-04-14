#include "CObjLoader.hpp"

#include "../../../Debug/DebugAllocation.hpp"

#include "../../../Core/CDevice.hpp"
#include "../../../Core/IVideoDriver.hpp"
#include "../../../Core/CMesh.hpp"
#include "../../../Core/CBufferBase.hpp"
#include "../../../Core/CDeclaration.hpp"

#include "../../../Model/CStaticModel.hpp"

#include "../CBufferOperation.hpp"

#include <sstream>
#include <vector>



#include <iostream>

namespace OMGL3D
{
    namespace UTILS
    {
        struct ObjVertex
        {
            float x, y, z;
        };

        struct ObjIndices
        {
            int vertex[4];
            int normal[4];
            int texcoord[4];

            //int v1[3];
            //int v2[3];
            //int v3[3];
            //int v4[3];
        };

        struct ObjMesh
        {
            std::string name;
            std::vector<ObjIndices> objIndices;
        };

        inline ObjVertex ReadVertex(const std::string & line);

        inline ObjIndices ReadIndices(const std::string & line);

        inline unsigned short AddVertex(std::vector<CORE::vertex_normal_texcoord> & list, const CORE::vertex_normal_texcoord & vertex);

        MODEL::IStaticModel * CObjLoader::Load(const CBuffer & buffer) throw(EXCP::LoadException)
        {
            // On utilise un flux pour gérer nos données reçus par le buffer
            std::stringstream stream;
            stream << buffer.GetBuffer();


            // On déclare une collection de Mesh
            std::vector<ObjMesh> objMeshes;

            // Nos collections pour stocker l'ensemble des données sur les sommets
            std::vector<ObjVertex> objVertex;   // coordonnées de position
            std::vector<ObjVertex> objTexcoord; // coordonnées de texture
            std::vector<ObjVertex> objNormal;   // normales


            // Lecture du fichier OBJ
            {
                // On déclare le mesh courant
                ObjMesh objMesh;

                // pour chaque ligne du fichier
                std::string line;
                while(std::getline(stream, line))
                {
                    switch(line[0])
                    {
                        case 'g': // information sur un mesh
                        {
                            std::stringstream stream;
                            std::string flag;
                            stream << line;
                            stream >> flag >> objMesh.name; // on récupère le nom

                            // si le mesh courant est déjà remplis, nous avons alors un nouveau mesh
                            if( !objMesh.objIndices.empty() )
                            {
                                objMeshes.push_back(objMesh); // on ajoute le mesh courant, qui est désormais remplis
                                objMesh.objIndices.clear(); // on vide le mesh courant pour remplir les données avec le nouveau mesh
                            }
                            break;
                        }

                        // lectures des informations générale
                        case 'v':
                        {
                            switch(line[1])
                            {
                                case ' ':
                                    objVertex.push_back(ReadVertex(line));
                                    break;

                                case 't':
                                    objTexcoord.push_back(ReadVertex(line));
                                    break;

                                case 'n':
                                    objNormal.push_back(ReadVertex(line));
                                    break;
                            }
                            break;
                        }

                        // lecture d'une face du mesh courant
                        case 'f':
                            objMesh.objIndices.push_back(ReadIndices(line));
                            break;
                    }
                }

                // Si le fichier OBJ ne possède qu'un seul mesh, notre tableau de mesh est vide
                // Si nous sommes dans ce cas, il faut rajouter l'unique mesh à la collection
                if( objMeshes.empty() )
                {
                    objMeshes.push_back(objMesh);
                    //objMesh.objIndices.clear();
                }
                //objMeshes.push_back(objMesh);
            }


            // Création du model et des mesh OMGL

            MODEL::IStaticModel * model = new MODEL::CStaticModel(buffer.GetName());

            // Pour chaque mesh OBJ chargé...
            std::vector<ObjMesh>::iterator it_mesh;
            for(it_mesh=objMeshes.begin(); it_mesh!=objMeshes.end(); ++it_mesh)
            {
                // On définit les paramétrages du mesh
                OMGL3D::CORE::Element elements[] = {
                    {0, OMGL3D::CORE::OMGL_ELEMENT_TARGET_POSITIONAL, OMGL3D::CORE::OMGL_ELEMENT_TYPE_FLOAT3},
                    {0, OMGL3D::CORE::OMGL_ELEMENT_TARGET_NORMAL, OMGL3D::CORE::OMGL_ELEMENT_TYPE_FLOAT3},
                    {0, OMGL3D::CORE::OMGL_ELEMENT_TARGET_TEXCOORD0, OMGL3D::CORE::OMGL_ELEMENT_TYPE_FLOAT2}
                };
                CORE::CDeclaration * declaration = new CORE::CDeclaration();
                declaration->AddElements(elements);

                // On crée notre tableau de sommet de d'indices typés pour l'API 3D
                std::vector<CORE::vertex_normal_texcoord> vertices;
                std::vector<unsigned short> indices;

                // On crée un mesh "logique". Il ne sera pas envoyé à l'API 3D, et restera en mémoire dans le moteur 3D
                CORE::IMesh * mesh = new CORE::CMesh((*it_mesh).name);
                mesh->SetDeclaration(declaration); // on lui donné le paramétrage réalisé

                // On identifie le type de polygone: ligne, triangle ou carré
                unsigned int stride_indices=0;

                if( (*it_mesh).objIndices[0].vertex[2] == -1 )
                {
                    stride_indices = 2;
                    mesh->SetType(CORE::OMGL_MESH_LINES);
                } else if( (*it_mesh).objIndices[0].vertex[3] == -1 )
                {
                    stride_indices = 3;
                    mesh->SetType(CORE::OMGL_MESH_TRIANGLE);
                } else
                {
                    stride_indices = 4;
                    mesh->SetType(CORE::OMGL_MESH_QUAD);
                }

                // pointeur facilitant la lecture des indices du mesh OBJ
                const ObjIndices * objIndices = &(*it_mesh).objIndices[0];

                // pour chaque sommet de chaque polygone
                for(unsigned int index_face=0; index_face<(*it_mesh).objIndices.size()*stride_indices; ++index_face)
                {
                    // On crée le polygone
                    CORE::vertex_normal_texcoord vertex;

                    int i = index_face==0 ? 0 : index_face%stride_indices;

                    // On le remplis avec les informations du format OBJ
                    vertex.x = objVertex[objIndices[index_face/stride_indices].vertex[i]-1].x;
                    vertex.y = objVertex[objIndices[index_face/stride_indices].vertex[i]-1].y;
                    vertex.z = objVertex[objIndices[index_face/stride_indices].vertex[i]-1].z;

                    vertex.nx = objNormal[objIndices[index_face/stride_indices].normal[i]-1].x;
                    vertex.ny = objNormal[objIndices[index_face/stride_indices].normal[i]-1].y;
                    vertex.nz = objNormal[objIndices[index_face/stride_indices].normal[i]-1].z;

                    vertex.s = objTexcoord[objIndices[index_face/stride_indices].texcoord[i]-1].x;
                    vertex.t = objTexcoord[objIndices[index_face/stride_indices].texcoord[i]-1].y;

                    // On le rajoute si nécéssaire (test de doublons) et on récupère son indice
                    unsigned short pos = AddVertex(vertices, vertex);
                    indices.push_back(pos); // ajout de l'indice
                }


                // Création des buffers de sommet et d'indice au format de l'API
                CORE::IBufferBase * buffer_vertex = new CORE::CBufferBase(vertices.size(), sizeof(CORE::vertex_normal_texcoord));
                CORE::IBufferBase * buffer_indices = new CORE::CBufferBase(indices.size(), sizeof(unsigned short));

                // Ajout des buffer au mesh final
                mesh->AddVertexBuffer(buffer_vertex);
                mesh->SetIndexBuffer(buffer_indices);

                // on remplis les buffer
                mesh->FillVertexBuffer(vertices.size(), &vertices[0]);
                mesh->FillIndexBuffer(indices.size(), &indices[0]);



                // Ajout du mesh au modèle
                model->AddMesh(mesh);
            }

            return model;
        }

        ObjVertex ReadVertex(const std::string & line)
        {
            std::stringstream stream;
            std::string flag;
            ObjVertex objVertex = {0, 0, 0};

            stream << line;
            stream >> flag >> objVertex.x >> objVertex.y >> objVertex.z;

            return objVertex;
        }

        ObjIndices ReadIndices(const std::string & line)
        {
            std::stringstream stream;
            std::string flag;
            ObjIndices v_index = {{0, 0, -1, -1}, { 0, 0, -1, -1}, {0, 0, -1, -1} };

            stream << line;
            stream >> flag;

            for(unsigned int i=0; i<4; ++i)
            {
                std::string sequence;
                stream >> sequence;

                unsigned int index = 0;

                std::string nb;
                std::istringstream iss(sequence);
                while(std::getline(iss, nb, '/'))
                {
                    std::istringstream convert(nb);

                    switch(index)
                    {
                        case 0:
                            convert >> v_index.vertex[i];
                            break;

                        case 1:
                            convert >> v_index.texcoord[i];
                            break;

                        case 2:
                            convert >> v_index.normal[i];
                            break;
                    }
/*
                    switch(i)
                    {
                        case 0:
                            //convert >> v_index.v1[index];
                            //convert >> v_index.v1[index+i];
                            break;

                        case 1:
                            //convert >> v_index.v2[index];
                            break;

                        case 2:
                            //convert >> v_index.v3[index];
                            break;

                        case 3:
                            //convert >> v_index.v4[index];
                            break;
                    }
                    */
                    index++;
                }
            }

            return v_index;
        }

        unsigned short AddVertex(std::vector<CORE::vertex_normal_texcoord> & list, const CORE::vertex_normal_texcoord & vertex)
        {
            unsigned short index=0;
            std::vector<CORE::vertex_normal_texcoord>::iterator it;
            for(it=list.begin(); it!=list.end(); ++it)
            {
                if( (*it).x == vertex.x &&
                    (*it).y == vertex.y &&
                    (*it).z == vertex.z &&
                    (*it).nx == vertex.nx &&
                    (*it).ny == vertex.ny &&
                    (*it).nz == vertex.nz &&
                    (*it).s == vertex.s &&
                    (*it).t == vertex.t )
                {
                    return index;
                }
                index++;
            }
            list.push_back(vertex);
            return index;
        }
    }
}
