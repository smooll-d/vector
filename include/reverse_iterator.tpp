#ifndef SMOOLLD_VECTOR_REVERSE_ITERATOR
#define SMOOLLD_VECTOR_REVERSE_ITERATOR

#include "vector.hpp"

#include <iterator>

namespace smoolld
{
    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::reverse_iterator()
     : mPointer{nullptr}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::reverse_iterator(IteratorType pointer)
     : mPointer{pointer}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::reverse_iterator(const reverse_iterator& other)
    {
        if (!other.mPointer)
        { return; }

        mPointer = other.mPointer;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::reverse_iterator(const iterator<IteratorType>& iterator)
     : mPointer{iterator.base()}
    {}

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>&
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator=(const reverse_iterator& other)
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
    vector<T, Allocator>::reverse_iterator<IteratorType>&
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator++()
    {
        --mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>&
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator--()
    {
        ++mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>&
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator+=(std::size_t n)
    {
        mPointer -= n;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>&
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator-=(std::size_t n)
    {
        mPointer += n;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator++(int)
    {
        reverse_iterator temp = *this;

        --mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator--(int)
    {
        reverse_iterator temp = *this;

        ++mPointer;

        return *this;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator+(std::size_t n) const
    {
        reverse_iterator temp = *this;

        return temp -= n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator-(std::size_t n) const
    {
        reverse_iterator temp = *this;

        return temp += n;
    }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator==(const reverse_iterator& other) const
    { return mPointer == other.mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator!=(const reverse_iterator& other) const
    { return mPointer != other.mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator>(const reverse_iterator& other) const
    { return other.mPointer < mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator<(const reverse_iterator& other) const
    { return other.mPointer - mPointer > 0; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator>=(const reverse_iterator& other) const
    { return !(mPointer < other.mPointer); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    bool
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator<=(const reverse_iterator& other) const
    { return !(mPointer > other.mPointer); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::reference
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator*() const
    { return *(mPointer - 1); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::reference
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator[](std::size_t index) const
    { return *(mPointer - index - 1); }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::pointer
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator->() const
    { return mPointer; }

    template<class T, class Allocator>
    template<std::random_access_iterator IteratorType>
    vector<T, Allocator>::reverse_iterator<IteratorType>::difference_type
    vector<T, Allocator>::reverse_iterator<IteratorType>::operator-(const reverse_iterator& other)
    {
        difference_type n = mPointer - other.mPointer;

        return n;
    }
}

#endif // SMOOLLD_VECTOR_REVERSE_ITERATOR
