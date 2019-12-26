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
        static T* m_pInstance;
        Singleton(const Singleton& src){(void)src;}
        Singleton &operator=(const Singleton& src){(void)src;}

        class Garbo
        {
            public:
                ~Garbo()
                {
                    if (Singleton::m_pInstance)
                    {
                        delete Singleton::m_pInstance;
                        Singleton::m_pInstance = NULL;
                    }
                }
        };
        static Garbo garbo;

    protected:
        Singleton(){}
        ~Singleton(){}

    public:
        static T* getInstance()
        {
            if (NULL == m_pInstance)
            {
                m_pInstance = new T();
            }
            return m_pInstance;
        }
};

template <class T>
T* Singleton<T>::m_pInstance = NULL;
#endif //SINGLETON_H

