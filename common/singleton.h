#ifndef _SING_H_
#define _SING_H_
/*
 * 单态类模板
 * Singleton.h
 * */
#define DECLARE_SINGLETON(className) \
    private: \
className(){} \
friend Singleton<className>;


template<class T>
class Singleton
{
    public:
        Singleton(void){}
        static T* GetInstance()
        {
            if(!m_Instance)
                m_Instance = new T;
            return m_Instance;
        }
        friend T;
    private:
        static T* m_Instance;
};

#endif 
