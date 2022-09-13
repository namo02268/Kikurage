#pragma once

template <class T>
class Singleton 
{
protected:
    static T* m_pInstance;

    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    virtual ~Singleton() = default;

public:
    static T& GetInstance() { return *m_pInstance; }

    static void Create() {
        if (!m_pInstance) {
            m_pInstance = new T();
        }
    }

    static void Destroy() {
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
};

template <class T>
T* Singleton<T>::m_pInstance = nullptr;
