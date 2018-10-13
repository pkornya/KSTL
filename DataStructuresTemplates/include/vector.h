#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

namespace pkl {
    ///////////// vector /////////////
    // 
    template <typename T>
    class vector {
        typedef vector<T>       this_type;

    public:
        typedef T               value_type;
        typedef T*              pointer;
        typedef const T*        const_pointer;
        typedef T&              reference;
        typedef const T&        const_reference;
        typedef T*              iterator;
        typedef const T*        const_iterator;

    public:
        vector();
        explicit vector(size_t size);
        explicit vector(size_t n, const value_type& val);
        vector(std::initializer_list<value_type> il);

        vector(const this_type& another);
        vector(this_type&& another);

        this_type& operator=(const this_type& another);
        this_type& operator=(this_type&& another);
        this_type& operator=(std::initializer_list<value_type> il);

        void swap(this_type& another);

        //void assign(size_t n, const value_type& val);
        //void assign(std::initializer_list<value_type> ilist);

        ~vector();

        reference       back();
        const_reference back() const;

        reference       front();
        const_reference front() const;

        size_t      size() const;
        size_t      capacity() const;
        void        clear();
        void        reserve(const size_t size);
        bool        empty();
        //void        shrink_to_fit();
        //void        resize();

        reference operator[](const size_t index);
        const_reference operator[](const size_t index) const;
        //reference at(const size_t index);

        iterator        begin();
        const_iterator  begin() const;
        const_iterator  cbegin() const;

        iterator        end();
        const_iterator  end() const;
        const_iterator  cend() const;

    protected:
        // Function which help to maintain vector and to avoid code duplication
        void doAllocateMemory(size_t size);
        void doDeallocateMemory();
        void doCopyElements(const this_type & another, size_t size);

    private:
        pointer     pBegin;
        pointer     pEnd;
        size_t      mSize;
        size_t      mCapacity;
    };




    ///////////// vector /////////////
    // 

    template<typename T>
    vector<T>::vector() : 
        pBegin(nullptr), pEnd(nullptr), mSize(0), mCapacity(0)
    {
        
    }

    template<typename T>
    vector<T>::vector(size_t size)
    {
        doAllocatoMemory(size);
    }


    template<typename T>
    vector<T>::vector(size_t n, const value_type & val) : vector()
    {
        doAllocateMemory(n);

        typename vector<T>::pointer pTemp = pBegin;

        for (size_t i = 0; i < n; i++, pTemp++) {
            *pTemp = val;
            mSize++;
        }

        pEnd = pBegin + mSize;
    }

    template <typename T>
    vector<T>::vector(std::initializer_list<value_type> il) : vector()
    {
        doAllocateMemory(il.size());
        typename vector<T>::pointer pTemp = pBegin;

        for (auto it = il.begin(); it != il.end(); ++it, pTemp++) {
            *pTemp = *it;
            mSize++;
        }

        pEnd = pBegin + mSize;
    }


    template <typename T>
    vector<T>::vector(const this_type & another) : vector()
    {
        doAllocateMemory(another.size());
        doCopyElements(another, another.size());
    }


    template<typename T>
    vector<T>::vector(this_type && another) : vector()
    {
        swap(another);
    }


    template<typename T>
    typename vector<T>::this_type& 
    vector<T>::operator=(const this_type & another)
    {
        if (this != &another) {
            clear();
            this_type(another).swap(*this); 
        }
        return *this;
    }


    template<typename T>
    typename vector<T>::this_type& 
    vector<T>::operator=(this_type && another)
    {
        if (this != &another) {
            clear();
            swap(another);
        }
        return *this;
    }


    template<typename T>
    typename vector<T>::this_type&
    vector<T>::operator=(std::initializer_list<value_type> il)
    {
        clear();

        doAllocateMemory(il.size());

        typename vector<T>::pointer pTemp = pBegin;

        for (auto it = il.begin(); it != il.end(); ++it, pTemp++) {
            *pTemp = *it;
            mSize++;
        }

        pEnd = pBegin + mSize;

        return *this;
    }


    template<typename T>
    vector<T>::~vector()
    {
        clear();
    }


    template<typename T>
    void vector<T>::swap(this_type & another)
    {
        std::swap(pBegin, another.pBegin);
        std::swap(mSize, another.mSize);
        std::swap(mCapacity, another.mCapacity);
    }


    template <typename T>
    size_t vector<T>::size() const
    {
        return mSize;
    }


    template <typename T>
    size_t vector<T>::capacity() const
    {
        return mCapacity;
    }


    template <typename T>
    void vector<T>::reserve(const size_t size)
    {
        if (size <= capacity)
            return;

        if (pHead == nullptr) {
            doAllocatoMemory(size);
            return;
        }

        clear();
        doAllocatoMemory(size);
    }


    template<typename T>
    bool vector<T>::empty()
    {
        return mSize == 0 ? true : false;
    }


    template <typename T>
    void vector<T>::clear()
    {
        doDeallocateMemory();
    }


    template <typename T>
    typename vector<T>::reference
    vector<T>::operator[](const size_t index)
    {
        return *(pBegin + index);
    }


    template<typename T>
    typename vector<T>::const_reference 
    vector<T>::operator[](const size_t index) const
    {
        return *(pBegin + index);
    }


    template <typename T>
    typename vector<T>::reference
    vector<T>::front()
    {
        return *pBegin;
    }


    template <typename T>
    typename vector<T>::const_reference
    vector<T>::front() const
    {
        return *pBegin;
    }


    template <typename T>
    typename vector<T>::reference
    vector<T>::back()
    {
        return *(pBegin + mSize - 1);
    }


    template <typename T>
    typename vector<T>::const_reference
    vector<T>::back() const
    {
        return *(pBegin + mSize - 1);
    }


    template <typename T>
    typename vector<T>::iterator
    vector<T>::begin()
    {
        return iterator(pBegin);
    }


    template <typename T>
    typename vector<T>::const_iterator
    vector<T>::begin() const
    {
        return const_iterator(pBegin);
    }


    template <typename T>
    typename vector<T>::const_iterator
    vector<T>::cbegin() const
    {
        return const_iterator(pBegin);
    }


    template <typename T>
    typename vector<T>::iterator
    vector<T>::end()
    {
        return iterator(pEnd);
    }


    template <typename T>
    typename vector<T>::const_iterator
    vector<T>::end() const
    {
        return const_iterator(pEnd);
    }


    template <typename T>
    typename vector<T>::const_iterator
    vector<T>::cend() const
    {
        return const_iterator(pEnd);
    }


    // Functions which help to maintain vector
    template <typename T>
    void vector<T>::doAllocateMemory(size_t size)
    {
        pBegin = new T[size];
        mCapacity = size;
    }


    template<typename T>
    void vector<T>::doDeallocateMemory()
    {
        delete[] pBegin;
        pBegin = pEnd = nullptr;
        mCapacity = 0;
        mSize = 0;
    }


    template<typename T>
    void vector<T>::doCopyElements(const this_type & another, size_t size)
    {
        typename vector<T>::pointer pTemp = pBegin;

        for (size_t i = 0; i < size; i++, pTemp++) {
            *pTemp = another[i];
            mSize++;
        }

        pEnd = pBegin + size;
    }
}


#endif // !VECTOR_H