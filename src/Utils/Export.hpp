#ifndef _DEF_OMEGLOND3D_EXPORT_HPP
#define _DEF_OMEGLOND3D_EXPORT_HPP

#if defined (WIN32)

    #if defined (_OMGL3D_EXPORT)
        #define EXPORT __declspec(dllexport)
    #elseif defined (_OMGL3D_IMPORT)
        #define EXPORT __declspec(dllimport)
    #else
        #define EXPORT
    #endif
#else
    #define EXPORT
#endif

#endif
