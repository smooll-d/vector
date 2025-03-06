#ifndef SMOOLLD_VECTOR_CONST_ITERATOR
#define SMOOLLD_VECTOR_CONST_ITERATOR

#include "vector.hpp"

#include <iterator>

namespace smoolld
{
    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::const_iterator()
     : mPointer{nullptr}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::const_iterator(IteratorType pointer)
     : mPointer{pointer}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::const_iterator(const const_iterator& other)
    {
        if (!other.mPointer)
        { return; }

        mPointer = other.mPointer;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::const_iterator(const iterator<IteratorType>& other)
     : mPointer{other.base()}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>&
    vector<T, Allocator>::const_iterator<IteratorType>::operator=(const const_iterator& other)
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
    vector<T, Allocator>::const_iterator<IteratorType>&
    vector<T, Allocator>::const_iterator<IteratorType>::operator++()
    {
        ++mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>&
    vector<T, Allocator>::const_iterator<IteratorType>::operator--()
    {
        --mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>&
    vector<T, Allocator>::const_iterator<IteratorType>::operator+=(std::size_t n)
    {
        mPointer += n;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>&
    vector<T, Allocator>::const_iterator<IteratorType>::operator-=(std::size_t n)
    {
        mPointer -= n;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::operator++(int)
    {
        const_iterator temp = *this;

        ++mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::operator--(int)
    {
        const_iterator temp = *this;

        --mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::operator+(std::size_t n) const
    {
        const_iterator temp = *this;

        return temp += n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::operator-(std::size_t n) const
    {
        const_iterator temp = *this;

        return temp -= n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::const_iterator<IteratorType>::operator==(const const_iterator& other) const
    { return mPointer == other.mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::const_iterator<IteratorType>::operator!=(const const_iterator& other) const
    { return mPointer != other.mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::const_iterator<IteratorType>::operator>(const const_iterator& other) const
    { return other.mPointer < mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::const_iterator<IteratorType>::operator<(const const_iterator& other) const
    { return other.mPointer - mPointer > 0; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::const_iterator<IteratorType>::operator>=(const const_iterator& other) const
    { return !(mPointer < other.mPointer); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::const_iterator<IteratorType>::operator<=(const const_iterator& other) const
    { return !(mPointer > other.mPointer); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::reference
    vector<T, Allocator>::const_iterator<IteratorType>::operator*() const
    { return *mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::reference
    vector<T, Allocator>::const_iterator<IteratorType>::operator[](std::size_t index) const
    { return *(mPointer + index); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::pointer
    vector<T, Allocator>::const_iterator<IteratorType>::operator->() const
    { return mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::const_iterator<IteratorType>::difference_type
    vector<T, Allocator>::const_iterator<IteratorType>::operator-(const const_iterator& other)
    {
        difference_type n = mPointer - other.mPointer;

        return n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    [[nodiscard]] vector<T, Allocator>::const_iterator<IteratorType>::pointer
    vector<T, Allocator>::const_iterator<IteratorType>::base() const
    { return mPointer; }
}

#endif // SMOOLLD_VECTOR_CONST_ITERATOR
