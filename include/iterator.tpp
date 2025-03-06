#ifndef SMOOLLD_VECTOR_ITERATOR
#define SMOOLLD_VECTOR_ITERATOR

#include "vector.hpp"

#include <iterator>

namespace smoolld
{
    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::iterator()
     : mPointer{nullptr}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::iterator(IteratorType pointer)
     : mPointer{pointer}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::iterator(const iterator& other)
    {
        if (!other.mPointer)
        { return; }

        mPointer = other.mPointer;
    }


    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>&
    vector<T, Allocator>::iterator<IteratorType>::operator=(const iterator& other)
    {
        if (this == &other)
        { return *this; }

        pointer newPointer = other.mPointer;

        delete mPointer;

        mPointer = newPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>&
    vector<T, Allocator>::iterator<IteratorType>::operator++()
    {
        ++mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>&
    vector<T, Allocator>::iterator<IteratorType>::operator--()
    {
        --mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>&
    vector<T, Allocator>::iterator<IteratorType>::operator+=(std::size_t n)
    {
        mPointer += n;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>&
    vector<T, Allocator>::iterator<IteratorType>::operator-=(std::size_t n)
    {
        mPointer -= n;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::operator++(int)
    {
        iterator temp = *this;

        ++mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::operator--(int)
    {
        iterator temp = *this;

        --mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::operator+(std::size_t n) const
    {
        iterator temp = *this;

        return temp += n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::operator-(std::size_t n) const
    {
        iterator temp = *this;

        return temp -= n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::iterator<IteratorType>::operator==(const iterator& other) const
    { return mPointer == other.mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::iterator<IteratorType>::operator!=(const iterator& other) const
    { return mPointer != other.mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::iterator<IteratorType>::operator>(const iterator& other) const
    { return other.mPointer < mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::iterator<IteratorType>::operator<(const iterator& other) const
    { return other.mPointer - mPointer > 0; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::iterator<IteratorType>::operator>=(const iterator& other) const
    { return !(mPointer < other.mPointer); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::iterator<IteratorType>::operator<=(const iterator& other) const
    { return !(mPointer > other.mPointer); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::reference
    vector<T, Allocator>::iterator<IteratorType>::operator*() const
    { return *mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::reference
    vector<T, Allocator>::iterator<IteratorType>::operator[](std::size_t index) const
    { return *(mPointer + index); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::pointer
    vector<T, Allocator>::iterator<IteratorType>::operator->() const
    { return mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::iterator<IteratorType>::difference_type
    vector<T, Allocator>::iterator<IteratorType>::operator-(const iterator& other)
    {
        difference_type n = mPointer - other.mPointer;

        return n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    [[nodiscard]] vector<T, Allocator>::iterator<IteratorType>::pointer
    vector<T, Allocator>::iterator<IteratorType>::base() const
    { return mPointer; }
}

#endif // SMOOLLD_VECTOR_ITERATOR
