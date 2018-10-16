#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <exception>

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

        ~vector();

        reference       back();
        const_reference back() const;

        reference       front();
        const_reference front() const;

        size_t          size() const;
        void            resize(size_t n);
        void            resize(size_t n, const value_type& val);
        size_t          capacity() const;
        bool            empty();
        void            reserve(const size_t size);
        void            shrink_to_fit();
        

        pointer         data();
        const_pointer   data() const;

        reference       operator[](const size_t index);
        const_reference operator[](const size_t index) const;
        reference       at(const size_t index);
        const_reference at(const size_t index) const;

        void assign(size_t n, const value_type& val);
        void assign(std::initializer_list<value_type> il);

        void push_back(const value_type &value);

        // Doesn`t free a memory of the last element, reduces mSize by 1 and decrements pEnd
        // It`s possible to access the element which has just been popped by iterator, which is not very good
        void pop_back();                              

        iterator        begin();
        const_iterator  begin() const;
        const_iterator  cbegin() const;

        iterator        end();
        const_iterator  end() const;
        const_iterator  cend() const;

        void            clear();

    protected:
        // Functions which help to maintain vector and to avoid code duplication

        // Allocates memory and returns pointer, if size == 0 returns nullptr
        pointer     doAllocate(size_t size);

        // Just calls delete[] for p
        void        doFree(pointer p);
                    
        void        doCopyElements(pointer pWhere , const_pointer pFrom, size_t size);
        size_t      getNewCapacity(const size_t currentCapacity);

    private:
        pointer     pBegin;
        pointer     pEnd;
        size_t      mSize;
        size_t      mCapacity;
    };




    ///////////// vector /////////////
    // 

    template <typename T>
    vector<T>::vector() : 
        pBegin(nullptr), pEnd(nullptr), mSize(0), mCapacity(0)
    {
        
    }

    template <typename T>
    vector<T>::vector(size_t size)
    {
        pBegin = doAllocate(size);
        mCapacity = size;
    }


    template <typename T>
    vector<T>::vector(size_t n, const value_type & val) : vector()
    {
        T* pNewArray = doAllocate(n);
        pBegin = pNewArray;
        mCapacity = mSize = n;

        for (size_t i = 0; i < n; i++, pNewArray++) {
            *pNewArray = val;
        }

        pEnd = pBegin + mSize;
    }

    template <typename T>
    vector<T>::vector(std::initializer_list<value_type> il) : vector()
    {
        T* pNewArray = doAllocate(il.size());
        pBegin = pNewArray;
        mCapacity = mSize = il.size();

        for (auto it = il.begin(); it != il.end(); ++it, pNewArray++) {
            *pNewArray = *it;
        }

        pEnd = pBegin + mSize;
    }


    template <typename T>
    vector<T>::vector(const this_type & another) : vector()
    {
        pBegin = doAllocate(another.size());
        doCopyElements(pBegin, another.begin(), another.size());

        mCapacity = another.capacity();
        mSize = another.size();
        pEnd = pBegin + mSize;
    }


    template <typename T>
    vector<T>::vector(this_type && another) : vector()
    {
        swap(another);
    }


    template <typename T>
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


    template <typename T>
    typename vector<T>::this_type&
    vector<T>::operator=(std::initializer_list<value_type> il)
    {
        clear();

        T* pNewArray = doAllocate(il.size());
        pBegin = pNewArray;
        mCapacity = mSize = il.size();

        for (auto it = il.begin(); it != il.end(); ++it, pNewArray++) {
            *pNewArray = *it;
        }

        pEnd = pBegin + mSize;

        return *this;
    }


    template <typename T>
    vector<T>::~vector()
    {
        clear();
    }


    template <typename T>
    void vector<T>::swap(this_type & another)
    {
        std::swap(pBegin, another.pBegin);
        std::swap(pEnd, another.pEnd);
        std::swap(mSize, another.mSize);
        std::swap(mCapacity, another.mCapacity);
    }


    template <typename T>
    size_t vector<T>::size() const
    {
        return mSize;
    }


    template<typename T>
    void vector<T>::resize(size_t n)
    {
        if (n < mSize) {
            pEnd -= (mSize - n);
        }
        else if (n > mSize && n <= mCapacity) {
            for (size_t i = 0; i < (n - mSize); i++, pEnd++)
                *pEnd = T();
        }
        else if (n > mCapacity) {
            T*  pNewArray = doAllocate(n);

            if (mSize) {
                doCopyElements(pNewArray, pBegin, mSize);
            }

            doFree(pBegin);

            pBegin = pNewArray;
            pEnd = pBegin + mSize;
            mCapacity = n;

            for (size_t i = 0; i < (n - mSize); i++, pEnd++)
                *pEnd = T();  
        }

        mSize = n;
    }

    template<typename T>
    void vector<T>::resize(size_t n, const value_type & val)
    {
        if (n < mSize) {
            pEnd -= (mSize - n);
        }
        else if (n > mSize && n <= mCapacity) {
            for (size_t i = 0; i < (n - mSize); i++, pEnd++)
                *pEnd = val;
        }
        else if (n > mCapacity) {
            T*  pNewArray = doAllocate(n);

            if (mSize) {
                doCopyElements(pNewArray, pBegin, mSize);
            }

            doFree(pBegin);

            pBegin = pNewArray;
            pEnd = pBegin + mSize;
            mCapacity = n;

            for (size_t i = 0; i < (n - mSize); i++, pEnd++)
                *pEnd = val;  
        }

        mSize = n;
    }


    template <typename T>
    void vector<T>::shrink_to_fit()
    {
        if (mCapacity > mSize) {
            T* pNewArray = doAllocate(mSize);

            if (mSize) {
                doCopyElements(pNewArray, pBegin, mSize);
            }

            free(pBegin);

            pBegin      =   pNewArray;
            pEnd        =   pBegin + mSize;
            mCapacity   =   mSize;
        }
    }


    template <typename T>
    size_t vector<T>::capacity() const
    {
        return mCapacity;
    }


    template <typename T>
    void vector<T>::reserve(const size_t reservedNumber)
    {
        if (reservedNumber > mCapacity) {
            T*  pNewArray = doAllocate(reservedNumber);

            if (mSize) {
                doCopyElements(pNewArray, pBegin, mSize);
            }

            doFree(pBegin);

            pBegin      =   pNewArray;
            pEnd        =   pBegin + mSize;
            mCapacity   =   reservedNumber;
        }
    }


    template <typename T>
    bool vector<T>::empty()
    {
        return mSize == 0 ? true : false;
    }


    template <typename T>
    void vector<T>::clear()
    {
        doFree(pBegin);
        pBegin = pEnd = nullptr;
        mCapacity = 0;
        mSize = 0;
    }


    template <typename T>
    typename vector<T>::pointer
    vector<T>::data()
    {
        return pBegin;
    }


    template <typename T>
    typename vector<T>::const_pointer
    vector<T>::data() const
    {
        return pBegin;
    }


    template <typename T>
    typename vector<T>::reference
    vector<T>::operator[](const size_t index)
    {
        return *(pBegin + index);
    }


    template <typename T>
    typename vector<T>::const_reference 
    vector<T>::operator[](const size_t index) const
    {
        return *(pBegin + index);
    }


    template <typename T>
    typename vector<T>::reference 
    vector<T>::at(const size_t index)
    {
        if (pBegin == nullptr) {
            throw std::logic_error("Vector is empty. It`s impossible to get an element.");
        }

        if (index >= mSize || index < 0) {
            throw std::out_of_range("Index is out of range");
        }

        return *(pBegin + index);
    }


    template <typename T>
    typename vector<T>::const_reference
    vector<T>::at(const size_t index) const
    {
        if (pBegin == nullptr) {
            throw std::logic_error("Vector is empty. It`s impossible to get an element.");
        }

        if (index >= mSize || index < 0) {
            throw std::out_of_range("Index is out of range");
        }

        return *(pBegin + index);
    }


    template<typename T>
    void vector<T>::assign(size_t n, const value_type& val)
    {
        if (mCapacity >= n) {
            pointer pTemp = pBegin;
            for (size_t i = 0; i < n; i++, pTemp++) {
                *pTemp = val;
            }
        }
        else {
            doFree(pBegin);
            pointer pNewArray = doAllocate(n);
            pBegin = pNewArray;
            mCapacity = n;
            for (size_t i = 0; i < n; i++, pNewArray++) {
                *pNewArray = val;
            }
        }

        mSize = n;
        pEnd = pBegin + mSize;
    }


    template<typename T>
    void vector<T>::assign(std::initializer_list<value_type> il)
    {
        if (mCapacity >= il.size()) {
            pointer pTemp = pBegin;
            for (auto it = il.begin(); it != il.end(); ++it, pTemp++) {
                *pTemp = *it;
            }
        }
        else {
            doFree(pBegin);
            pointer pNewArray = doAllocate(il.size());
            pBegin = pNewArray;
            mCapacity = il.size();
            for (auto it = il.begin(); it != il.end(); ++it, pNewArray++) {
                *pNewArray = *it;
            }
        }

        mSize = il.size();
        pEnd = pBegin + mSize;
    }


    template <typename T>
    void vector<T>::push_back(const value_type &value)
    {
        if (mSize == mCapacity) {
            const size_t    prevSize    = mSize;
            const size_t    newCapacity = getNewCapacity(prevSize);
            pointer const   pNewData    = doAllocate(newCapacity);

            doCopyElements(pNewData, pBegin, mSize);
            doFree(pBegin);

            pBegin      =   pNewData;
            mCapacity   =   newCapacity;
            pEnd        =   pBegin + prevSize;
            *pEnd       =   value;

            pEnd++;
            mSize++;
        }

        else {
            *pEnd = value;

            pEnd++;
            mSize++;
        }
    }

    
    template <typename T>
    void vector<T>::pop_back()
    {
        pEnd--;
        mSize--;
        //pEnd->~value_type();
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
        return *(pEnd - 1);
    }


    template <typename T>
    typename vector<T>::const_reference
    vector<T>::back() const
    {
        return *(pEnd - 1);
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
    typename vector<T>::pointer
    vector<T>::doAllocate(size_t size)
    {
        if (size) {
            pointer p = new T[size];
            return p;
        }
        else {
            return nullptr;
        }
    }


    template <typename T>
    void vector<T>::doFree(pointer p)
    {
        delete[] p;
    }


    template <typename T>
    void vector<T>::doCopyElements(pointer pWhere, const_pointer pFrom, size_t size)
    {
        for (size_t i = 0; i < size; i++, pWhere++, pFrom++) {
            *pWhere = *pFrom;
        }
    }


    template<typename T>
    size_t vector<T>::getNewCapacity(const size_t currentCapacity)
    {
        return (currentCapacity > 0) ? (currentCapacity * 2) : 1;
    }


}


#endif // !VECTOR_H