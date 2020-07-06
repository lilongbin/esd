/*****************************************
 * Copyright (C) 2019 * Ltd. All rights reserved.
 * File name   : singleton.hpp
 * Created date: 2019-07-25 18:45:05
 *******************************************/

#ifndef _SINGLETON_H
#define _SINGLETON_H

template <class T>
class Singleton
{
private:
    static std::mutex m_MuxLock_Singleton;
    using MuxGuard = std::lock_guard<std::mutex>;
    static T* m_pInstance;
    Singleton(const Singleton& src){(void)src;}
    Singleton &operator=(const Singleton& src){(void)src;};

    class Garbo
    {
    public:
        ~Garbo()
        {
            // std::cout<<"Singleton<"<<typeid(T).name()<<">::Garbo::~Garbo()" << std::endl;
            if (Singleton::m_pInstance)
            {
                delete Singleton::m_pInstance;
                Singleton::m_pInstance = NULL;
            }
        }
        void touch() { return; }
    };
    static Garbo m_garbo;

protected:
    Singleton() {
        m_garbo.touch(); //prevent optimised and no garbo instance to trigger deconstruct
    }
    ~Singleton() {}

public:
    static T* getInstance()
    {
        if (m_pInstance == NULL)
        {
            MuxGuard mlk(m_MuxLock_Singleton);
            if (m_pInstance == NULL)
            {
                m_pInstance = new T();
            }
        }
        return m_pInstance;
    }
};

template <class T> std::mutex Singleton<T>::m_MuxLock_Singleton;
template <class T> typename Singleton<T>::Garbo Singleton<T>::m_garbo;
template <class T> T* Singleton<T>::m_pInstance = NULL;

#endif //SINGLETON_H

