#ifndef _DEF_OMEGLOND3D_GENHIERARCHY_HPP
#define _DEF_OMEGLOND3D_GENHIERARCHY_HPP

namespace OMGL3D
{
    namespace UTILS
    {
        // TypeList

        template<typename T1, typename T2>
        struct TypeList
        {
            typedef T1 Head;
            typedef T2 Tail;
        };

        struct NullType
        {
        };

        #define TYPELIST_1(t1)                              OMGL3D::UTILS::TypeList<t1, OMGL3D::UTILS::NullType>
        #define TYPELIST_2(t1, t2)                          OMGL3D::UTILS::TypeList<t1, TYPELIST_1(t2) >
        #define TYPELIST_3(t1, t2, t3)                      OMGL3D::UTILS::TypeList<t1, TYPELIST_2(t2, t3) >
        #define TYPELIST_4(t1, t2, t3, t4)                  OMGL3D::UTILS::TypeList<t1, TYPELIST_3(t2, t3, t4) >
        #define TYPELIST_5(t1, t2, t3, t4, t5)              OMGL3D::UTILS::TypeList<t1, TYPELIST_4(t2, t3, t4, t5) >
        #define TYPELIST_6(t1, t2, t3, t4, t5, t6)          OMGL3D::UTILS::TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6) >
        #define TYPELIST_7(t1, t2, t3, t4, t5, t6, t7)      OMGL3D::UTILS::TypeList<t1, TYPELIST_6(t2, t3, t4, t5, t6, t7) >
        #define TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8)  OMGL3D::UTILS::TypeList<t1, TYPELIST_7(t2, t3, t4, t5, t6, t7, t8) >


        // Hierarchy

        template<typename TypeList, template <class> class Handler>
        struct Hierarchy;

        template<typename T1, typename T2, template <class> class Handler>
        struct Hierarchy<TypeList<T1, T2>, Handler> : public Hierarchy<T2, Handler>, Handler<T1>
        {
        };

        template <typename T, template <class> class Handler>
        struct Hierarchy<TypeList<T, NullType>, Handler> : public Handler<T>
        {
        };
    }
}

#endif
