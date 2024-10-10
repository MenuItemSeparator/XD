#pragma once
#include "XD_Engine_Minimal.h"

namespace XD
{
    template<typename T>
    class XD_ENGINE_API XD_Array final
    {
    public:
        XD_Array(XD_Allocator* _allocator);
        XD_Array(const XD_Array<T>& _other);
        ~XD_Array();
        const T& operator[](u8 _index) const;
        T& operator[](u8 _index);
        XD_Array<T>& operator=(const XD_Array& _other);

        bool fIsEmpty() const { return m_size == 0; }
        u8 fGetSize() const { return m_size; }
        u8 fGetCapacity() const { return m_capacity; }
        void fResize(u8 _newSize);
        void fReserve(u8 _newCapacity);
        void fAdd(const T& _item);
        void fRemoveLast();
        void fClear();

        T* fBegin() { return m_data; }
        const T* fBegin() const { return m_data; }
        T* fEnd() { return m_data + m_size; }
        const T* fEnd() const { return m_data + m_size; }
        T* fFirst() { mXD_ASSERT(m_size > 0); return m_data; }
        const T* fFirst() const { mXD_ASSERT(m_size > 0); return m_data; }
        T* fLast() { mXD_ASSERT(m_size > 0); return m_data + (m_size - 1); }
        const T* fLast() const { mXD_ASSERT(m_size > 0); return m_data + (m_size - 1); }

    private:
        XD_Allocator* m_allocator;
        u8 m_capacity;
        u8 m_size;
        T* m_data;

        void fSetCapacity(u8 _newCapacity);
        u8 fCalculateNewCapacity(u8 _minCapacity);
    };

    template <typename T>
    inline XD_Array<T>::XD_Array(XD_Allocator* _allocator) :
        m_allocator(_allocator),
        m_capacity(0),
        m_size(0),
        m_data(nullptr)
    {}

    template <typename T>
    inline XD_Array<T>::XD_Array(const XD_Array<T> &_other) :
        m_allocator(_allocator),
        m_capacity(0),
        m_size(0),
        m_data(nullptr)
    {
        const u8 size = _other.fGetSize();
        fResize(size);

        for (size_t i = 0; i < size; ++i
        {
            new (&m_data[i]) T(_other.m_data[i]);
        }
        
    }
    template <typename T>
    inline XD_Array<T>::~XD_Array()
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i].~T();
        }
        
        m_allocator->fFree(m_data);
    }

    template <typename T>
    inline const T&
    XD_Array<T>::operator[](u8 _index) const
    {
        mXD_ASSERT(_index < m_size);
        return m_data[_index];
    }

    template <typename T>
    inline T&
    XD_Array<T>::operator[](u8 _index)
    {
        mXD_ASSERT(_index < m_size);
        return m_data[_index];
    }

    template <typename T>
    inline XD_Array<T>&
    XD_Array<T>::operator=(const XD_Array &_other)
    {
        mXD_NOT_IMPLEMENTED();
        
        const u8 size = _other.fGetSize();
        fResize(size);

        for (sz i = 0; i < size; ++i)
        {
            new (m_data + i) T (_other.m_data[i]);
        }

        return *this;
    }
    template <typename T>
    inline void 
    XD_Array<T>::fResize(u8 _newSize)
    { 
        if(m_size == _newSize) return;

        mLOG("Resizing from " << m_size << " to " << _newSize);

        if(_newSize > m_capacity)
        {
            fSetCapacity(fCalculateNewCapacity(_newSize));
        }

        if(_newSize > m_size)
        {
            for (sz i = m_size; i < _newSize; ++i)
            {
                new (m_data + i) T ();
            }
        
        }
        else
        {
            for (sz i = m_size - 1; i >= _newSize; --i)
            {
                m_data[i].~T();
            }
        }

        m_size = _newSize;
    }

    template <typename T>
    inline void 
    XD_Array<T>::fReserve(u8 _newCapacity)
    {
        if(m_capacity < _newCapacity)
        {
            fSetCapacity(fCalculateNewCapacity(_newCapacity));
        }
    }

    template <typename T>
    inline void 
    XD_Array<T>::fAdd(const T &_item)
    {
        if(m_size == m_capacity)
        {
            fSetCapacity(fCalculateNewCapacity(m_capacity + 1));
        }

        new (m_data + m_size) T (_item);
        ++m_size;    
    }

    template <typename T>
    inline void 
    XD_Array<T>::fRemoveLast()
    {
        mXD_ASSERT(m_size > 0);
        fLast()->~T();
        --m_size;
    }

    template <typename T>
    inline void 
    XD_Array<T>::fClear()
    {
        for (sz i = 0; i < m_size; ++i)
        {
            m_data[i].~T();
        }
        
        m_size = 0;
    }

    template <typename T>
    inline void 
    XD_Array<T>::fSetCapacity(u8 _newCapacity)
    {
        if(m_capacity == _newCapacity) return;
        if(_newCapacity < m_size)
        {
            fResize(_newCapacity);
        }

        mLOG("Changing capacity from " << m_capacity << " to " << _newCapacity);

        if(_newCapacity == 0)
        {
            fClear();
            m_capacity = 0;
            return;            
        }

        T* tmpData = m_data;
        m_data = reinterpret_cast<T*>(m_allocator->fAllocate(_newCapacity * sizeof(T), alignof(T)));

        if(!tmpData)
        {
            m_capacity = _newCapacity;
            return;
        } 

        for (sz i = 0; i < m_size; ++i)
        {
            new(m_data + i) T (tmpData[i]);
        }

        for (sz i = 0; i < m_size; ++i)
        {
            tmpData[i].~T();
        }

        m_allocator->fFree(tmpData);
        m_capacity = _newCapacity;
    }

    template <typename T>
    inline u8 
    XD_Array<T>::fCalculateNewCapacity(u8 _minCapacity)
    {
        u8 newCapacity = m_capacity * 2 + 1;
        if(_minCapacity > newCapacity)
            return _minCapacity;
        return newCapacity;
    }
}