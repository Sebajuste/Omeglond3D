namespace OMGL3D
{
    namespace UTILS
    {
        template <typename T> Singleton<T>::Singleton()
        {
        }

        template <typename T> Singleton<T>::~Singleton()
        {
        }

        template <typename T> T & Singleton<T>::GetInstance()
        {
            if( m_Instance == 0 )
            {
                m_Life = typename Singleton<T>::Life();
                m_Instance = new T();
            }
            return *m_Instance;
        }

        template <typename T> void Singleton<T>::Destroy()
        {
            delete m_Instance;
            m_Instance = 0;
        }

        template <typename T> Singleton<T>::Life::~Life()
        {
            T::Destroy();
        }

        template <typename T> T * Singleton<T>::m_Instance = 0;
        template <typename T> typename Singleton<T>::Life Singleton<T>::m_Life;

    } // end UTILS
} // end OMGL3D
