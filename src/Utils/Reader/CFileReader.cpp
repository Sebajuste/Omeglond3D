#include "CFileReader.hpp"

#include <sstream>
#include <fstream>

#include "../../Debug/DebugAllocation.hpp"

namespace OMGL3D
{
    namespace UTILS
    {
        CFileReader::CFileReader()
        {
        }

        CFileReader::~CFileReader()
        {
        }

        CBuffer CFileReader::Read(const std::string & source, const StreamType & stream) throw(EXCP::ReadException)
        {
            // On récupère le nom du fichier (on supprime le chemin d'acces et l'extention)
            int offset_begin_name = source.find_last_of("/");
            int offset_end_name = source.find_last_of(".");
            std::string name(source, offset_begin_name+1, offset_end_name-offset_begin_name-1);

            // On crée le buffer pour stocker le contenu du fichier
            std::stringstream buffer;

            // On crée un flux de lecture de fichier
            std::ifstream file;

            // Ouverture du fichier en lecture
            switch(stream)
            {
                case OMGL_STREAM_ASCII:
                    file.open(source.c_str(), std::ios::in);
                    break;

                case OMGL_STREAM_BINARY:
                    file.open(source.c_str(), std::ios_base::binary);
                    break;
            }


            // Si l'ouverture à échouer, on rapporte l'erreure
            if( file.fail() ) {
                throw EXCP::ReadException("Error to read file "+source);
            }

            // Lecture complète du fichier dans le buffer
            buffer << file.rdbuf();

            // fermeture du fichier
            file.close();

            // on retourne le buffer
            return CBuffer(std::string(source, offset_begin_name+1), buffer.str());
        }

        void CFileReader::Write(const std::string &source, const CBuffer &buffer, const StreamType &stream) throw(EXCP::WriteException)
        {
            std::ofstream file;

            switch(stream)
            {
                case OMGL_STREAM_ASCII:
                    file.open(source.c_str(), std::ios::in);
                    break;

                case OMGL_STREAM_BINARY:
                    file.open(source.c_str(), std::ios_base::binary);
                    break;
            }

            if( file.fail() ) {
                throw EXCP::WriteException("Error to write "+source);
            }

            std::stringstream local_buffer;
            local_buffer << buffer.GetBuffer();

            file << local_buffer.rdbuf();

            file.close();
        }
    }
}
