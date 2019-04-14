#ifndef _DEF_OMEGLOND3D_BUFFEROPERATION_HPP
#define _DEF_OMEGLOND3D_BUFFEROPERATION_HPP

#include <fstream>
#include <sstream>

namespace OMGL3D
{
    namespace UTILS
    {
        /**
        * Réalise des opérations facilitant l'utilisation de fichiers
        * en mode en texte ou en mode binaire
        */
        class CBufferOperation
        {
            public:

            // gestion de la lecture en mode binaire
            template <typename T> static void Read(std::istream & in, T & value) {
                in.read(reinterpret_cast<char*>(&value), sizeof(T));
            }

            template <typename T> static void Write(std::ostream & out, T & value) {
                //out.write(reinterpret_cast<char*>(&value), sizeof(T));
                out.write(reinterpret_cast<const char*>(&value), sizeof(T));
            }

            /*
             * Positionne le curseur de lecture sur la ligne où se trouve la chaine de caractère "str"
             * Retourne le reste de la ligne après la chaine "str"
             */
            static std::string FindInformation(std::stringstream & buffer, const std::string & str);


            /*
             * Retourne la valeur d'une variable "str" d'un fichier XML dont la ligne est passée en paramètre
             */
            static std::string FindXMLInformation(const std::string & line, const std::string & str);


            // Retourne un float à partir d'une chaine de caractère
            static float StringToFloat(const std::string & str);


            // Retourne un chaine emputée de tous les espaces en début de chaine
            static std::string Trim(const std::string & str);

        };
    }
}

 #endif
