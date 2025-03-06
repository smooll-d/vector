#ifndef SMOOLLD_VECTOR_DEFINITION
#define SMOOLLD_VECTOR_DEFINITION

#include "vector.hpp"

#include <format>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <compare>

namespace smoolld
{
    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector() noexcept(noexcept(allocator_type()))
     : mData{nullptr},
       mSize{0},
       mCapacity{0},
       mAllocator{allocator_type()}
    {}

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector(const allocator_type& allocator) noexcept
     : mData{nullptr},
       mSize{0},
       mCapacity{0},
       mAllocator{allocator}
    {}

    template<class T, class Allocator>
    vector<T, Allocator>::vector(size_type count, const allocator_type& allocator)
     : mData{nullptr},
       mSize{count},
       mCapacity{count},
       mAllocator{allocator}
    {
        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], static_cast<T&&>(T())); }
    }

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector(size_type count, const_reference value, const allocator_type& allocator)
     : mData{nullptr},
       mSize{count},
       mCapacity{count},
       mAllocator{allocator}
    {
        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], value); }
    }

    template<class T, class Allocator>
    template<class InputIt>
    constexpr
    vector<T, Allocator>::vector(InputIt first, InputIt last, const allocator_type& allocator)
     : mData{nullptr},
       mSize{0},
       mCapacity{0},
       mAllocator{allocator}
    {
        mSize = last - first;
        mCapacity = last - first;

        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], *(first + i)); }
    }

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector(const vector& other)
     : mData{nullptr},
       mSize{0},
       mCapacity{0},
       mAllocator{allocator_type()}
    {
        if (!other.mData)
        { return; }

        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mAllocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.get_allocator());

        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], other.mData[i]); }
    }

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector(vector&& other) noexcept
     : mData{other.mData},
       mSize{other.mSize},
       mCapacity{other.mCapacity},
       mAllocator{other.get_allocator()}
    {
        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;
        other.mAllocator = nullptr;
    }

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector(const vector& other, const std::type_identity_t<allocator_type>& allocator)
     : mData{nullptr},
       mSize{0},
       mCapacity{0},
       mAllocator{allocator}
    {
        if (!other.mData)
        { return; }

        mSize = other.mSize;
        mCapacity = other.mCapacity;

        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], other.mData[i]); }
    }

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::vector(vector&& other, const std::type_identity_t<allocator_type>& allocator) noexcept
     : mData{other.mData},
       mSize{other.mSize},
       mCapacity{other.mCapacity},
       mAllocator{allocator}
    {
        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;
        other.mAllocator = nullptr;
    }

    template<class T, class Allocator>
    vector<T, Allocator>::vector(std::initializer_list<value_type> ilist, const allocator_type& allocator)
     : vector(ilist.begin(), ilist.end(), allocator)
    {}

    template<class T, class Allocator>
    constexpr
    vector<T, Allocator>::~vector()
    {
        if (mData)
        { mDestroy(); }
        mAllocator.deallocate(mData, mCapacity);
    }

    template<class T, class Allocator>
    constexpr vector<T, Allocator>&
    vector<T, Allocator>::operator=(const vector& other)
    {
        if (this == &other)
        { return *this; }

        allocator_type old = mAllocator;

        if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value)
        { mAllocator = other.get_allocator(); }

        if (mAllocator != old)
        {
            for (size_type i = 0; i < mSize; i++)
            { std::allocator_traits<allocator_type>::destroy(old, &mData[i]); }
            old.deallocate(mData, mCapacity);
        }
        else
        {
            mDestroy();
            mAllocator.deallocate(mData, mCapacity);
        }

        mSize = other.mSize;
        mCapacity = other.mCapacity;

        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], other.mData[i]); }

        return *this;
    }

    template<class T, class Allocator>
    vector<T, Allocator>&
    vector<T, Allocator>::operator=(vector&& other) noexcept
    {
        if (this == &other)
        { return *this; }

        if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value)
        { mAllocator = other.get_allocator(); }
        else if constexpr (!std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value && mAllocator != other.get_allocator())
        {
            mDestroy();
            mAllocator.deallocate(mData, mCapacity);

            mSize = other.mSize;
            mCapacity = other.mCapacity;

            mData = mAllocator.allocate(mCapacity);

            for (size_type i = 0; i < mSize; i++)
            { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], static_cast<value_type&&>(other.mData[i])); }

            other.mData = nullptr;
            other.mSize = 0;
            other.mCapacity = 0;

            return *this;
        }

        mDestroy();
        mAllocator.deallocate(mData, mCapacity);

        mData = other.mData;
        mSize = other.mSize;
        mCapacity = other.mCapacity;

        other.mData = nullptr;
        other.mSize = 0;
        other.mCapacity = 0;

        return *this;
    }

    template<class T, class Allocator>
    constexpr vector<T, Allocator>&
    vector<T, Allocator>::operator=(std::initializer_list<value_type> ilist)
    {
        mDestroy();
        mAllocator.deallocate(mData, mCapacity);

        mSize = ilist.size();
        mCapacity = ilist.size();

        mData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], *(ilist.begin() + i)); }

        return *this;
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::assign(size_type count, const_reference value)
    {
        while (mNeedsResize() || count >= mCapacity)
        { mGrow(); }

        for (size_type i = 0; i < count; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], value); }

        mSize = count;
    }

    template<class T, class Allocator>
    template<class InputIt>
    constexpr void
    vector<T, Allocator>::assign(InputIt first, InputIt last)
    {
        while (mNeedsResize() || last - first >= mCapacity)
        { mGrow(); }

        for (size_type i = 0; i < last - first; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], *(first + i)); }

        mSize = last - first;
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::assign(std::initializer_list<T> ilist)
    {
        while (mNeedsResize() || ilist.size() >= mCapacity)
        { mGrow(); }

        for (size_type i = 0; i < ilist.size(); i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], *(ilist.begin() + i)); }

        mSize = ilist.size();
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::allocator_type
    vector<T, Allocator>::get_allocator() const noexcept
    { return mAllocator; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::reference
    vector<T, Allocator>::at(size_type index)
    {
        if (index >= mSize)
        { throw std::out_of_range(std::format("index ({}) exceedes size of vector ({})!", index, mSize)); }

        return mData[index];
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reference
    vector<T, Allocator>::at(size_type index) const
    {
        if (index >= mSize)
        { throw std::out_of_range(std::format("index ({}) exceedes size of vector ({})!", index, mSize)); }

        return mData[index];
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::reference
    vector<T, Allocator>::operator[](size_type index)
    { return mData[index]; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reference
    vector<T, Allocator>::operator[](size_type index) const
    { return mData[index]; }

    template<class T, class Allocator>
    std::ostream& operator<<(std::ostream& os, const vector<T, Allocator>& vector)
    {
        os << '[';

        for (auto it = vector.cbegin(); it != vector.cend(); ++it)
        {
            if (it != vector.cbegin())
            { os << ", "; }

            os << *it;
        }

        os << ']';

        return os;
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::reference
    vector<T, Allocator>::front()
    { return mData[0]; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reference
    vector<T, Allocator>::front() const
    { return mData[0]; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::reference
    vector<T, Allocator>::back()
    { return mData[mSize - 1]; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reference
    vector<T, Allocator>::back() const
    { return mData[mSize - 1]; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::value_type*
    vector<T, Allocator>::data() noexcept
    { return mData; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr const vector<T, Allocator>::value_type*
    vector<T, Allocator>::data() const noexcept
    { return mData; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::begin() noexcept
    { return iterator<value_type*>(mData); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::begin() const noexcept
    { return iterator<value_type*>(mData); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::cbegin() const noexcept
    { return const_iterator<value_type*>(mData); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::end() noexcept
    { return iterator<value_type*>(mData + mSize); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::end() const noexcept
    { return iterator<value_type*>(mData + mSize); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::cend() const noexcept
    { return const_iterator<value_type*>(mData + mSize); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::reverse_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::rbegin() noexcept
    { return reverse_iterator<value_type*>(end()); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reverse_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::rbegin() const noexcept
    { return reverse_iterator<value_type*>(end()); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reverse_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::crbegin() const noexcept
    { return const_reverse_iterator<value_type*>(cend()); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::reverse_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::rend() noexcept
    { return reverse_iterator<value_type*>(begin()); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reverse_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::rend() const noexcept
    { return reverse_iterator<value_type*>(begin()); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::const_reverse_iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::crend() const noexcept
    { return const_reverse_iterator<value_type*>(cbegin()); }

    template<class T, class Allocator>
    [[nodiscard]] constexpr bool
    vector<T, Allocator>::empty() const noexcept
    { return mSize == 0; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::size_type
    vector<T, Allocator>::size() const noexcept
    { return mSize; }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::size_type
    vector<T, Allocator>::max_size() const noexcept
    { return std::allocator_traits<allocator_type>::max_size(mAllocator); }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::reserve(size_type newCapacity)
    {
        if (!mExceedsMaxSize() && newCapacity > mCapacity)
        {
            value_type* newData = mAllocator.allocate(newCapacity);

            mCapacity = newCapacity;

            for (size_type i = 0; i < mSize; i++)
            { std::allocator_traits<allocator_type>::construct(mAllocator, &newData[i], mData[i]); }

            mDestroy();
            mAllocator.deallocate(mData, mCapacity);

            mData = newData;
        }
    }

    template<class T, class Allocator>
    [[nodiscard]] constexpr vector<T, Allocator>::size_type
    vector<T, Allocator>::capacity() const noexcept
    { return mCapacity; }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::shrink_to_fit()
    {
        if (!mExceedsMaxSize() && mCapacity > mSize)
        {
            value_type* newData = mAllocator.allocate(mSize);

            mCapacity = mSize;

            for (size_type i = 0; i < mSize; i++)
            { std::allocator_traits<allocator_type>::construct(mAllocator, &newData[i], mData[i]); }

            mDestroy();
            mAllocator.deallocate(mData, mCapacity);
        }
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::clear() noexcept
    {
        mDestroy();

        mSize = 0;
    }

    template<class T, class Allocator>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::insert(const_iterator<value_type*> position, const_reference value)
    {
        size_type index = position - cbegin();

        mGrow();

        for (size_type i = mSize; i > index; i--)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], mData[i - 1]);
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i - 1]);
        }

        std::allocator_traits<allocator_type>::construct(mAllocator, &mData[index], value);

        mSize++;

        return iterator<value_type*>(mData + index);
    }

    template<class T, class Allocator>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::insert(const_iterator<value_type*> position, value_type&& value)
    {
        size_type index = position - cbegin();

        mGrow();

        for (size_type i = mSize; i > index; i--)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], mData[i - 1]);
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i - 1]);
        }

        std::allocator_traits<allocator_type>::construct(mAllocator, &mData[index], static_cast<value_type&&>(value));

        mSize++;

        return iterator<value_type*>(mData + index);
    }

    template<class T, class Allocator>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::insert(const_iterator<value_type*> position, size_type count, const_reference value)
    {
        size_type index = position - cbegin();

        while (mNeedsResize() || mSize + count >= mCapacity)
        { mGrow(); }

        for (size_type i = mSize + count; i > index; i--)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], mData[i - count]);
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i - count]);
        }

        for (size_type i = 0; i < count; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i + index], value); }

        mSize += count;

        return iterator<value_type*>(mData + index);
    }

    template<class T, class Allocator>
    template<class InputIt>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::insert(const_iterator<value_type*> position, InputIt first, InputIt last)
    {
        size_type index = position - cbegin();
        size_type count = last - first;

        while (mNeedsResize() || mSize + count >= mCapacity)
        { mGrow(); }

        for (size_type i = mSize + count; i > index; i--)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], mData[i - count]);
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i - count]);
        }

        for (size_type i = 0; i < count; i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i + index], *(first + i)); }

        mSize += count;

        return iterator<value_type*>(mData + index);
    }

    template<class T, class Allocator>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::insert(const_iterator<value_type*> position, std::initializer_list<value_type> ilist)
    {
        size_type index = position - cbegin();

        while (mNeedsResize() || mSize + ilist.size() >= mCapacity)
        { mGrow(); }

        for (size_type i = mSize + ilist.size(); i > index; i--)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], mData[i - ilist.size()]);
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i - ilist.size()]);
        }

        for (size_type i = 0; i < ilist.size(); i++)
        { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i + index], *(ilist.begin() + i)); }

        mSize += ilist.size();

        return iterator<T*>(mData + index);
    }

    template<class T, class Allocator>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::erase(const_iterator<value_type*> position)
    {
        size_type index = position - cbegin();

        std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[index]);

        for (size_type i = index; i < mSize - 1; i++)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], static_cast<T&&>(mData[i + 1]));
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i + 1]);
        }

        mSize--;

        return iterator(mData + index);
    }

    template<class T, class Allocator>
    [[maybe_unused]] constexpr vector<T, Allocator>::iterator<typename vector<T, Allocator>::value_type*>
    vector<T, Allocator>::erase(const_iterator<value_type*> first, const_iterator<value_type*> last)
    {
        size_type index = last - first;

        for (size_type i = first - cbegin(); i < last - cbegin(); i++)
        { std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i]); }

        for (size_type i = first - cbegin(); i < mSize - index; i++)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], static_cast<T&&>(mData[i + index]));
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i + index]);
        }

        mSize -= index;

        return iterator(mData + index);
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::push_back(const_reference value)
    {
        if (mSize < mCapacity)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[mSize], value);
            mSize++;
        }
        else if (!mExceedsMaxSize() && mNeedsResize())
        {
            mGrow();

            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[mSize], value);
            mSize++;
        }
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::push_back(T&& value)
    {
        if (mSize < mCapacity)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[mSize], static_cast<T&&>(value));
            mSize++;
        }
        else if (!mExceedsMaxSize() && mNeedsResize())
        {
            mGrow();

            std::allocator_traits<allocator_type>::construct(mAllocator, &mData[mSize], static_cast<T&&>(value));
            mSize++;
        }
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::pop_back()
    { mSize--; }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::resize(size_type count)
    {
        if (count == mSize)
        { return; }
        else if (count < mSize)
        {
            for (size_type i = count; i < mSize; i++)
            { std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i]); }

            mSize = count;
        }
        else if (count > mSize)
        {
            reserve(count);

            for (size_type i = mSize; i < count; i++)
            { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], T()); }

            mSize = count;
        }
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::resize(size_type count, const_reference value)
    {
        if (count == mSize)
        { return; }
        else if (count < mSize)
        {
            for (size_type i = count; i < mSize; i++)
            { std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i]); }

            mSize = count;
        }
        else if (count > mSize)
        {
            reserve(count);

            for (size_type i = mSize; i < count; i++)
            { std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], value); }

            mSize = count;
        }
    }

    template<class T, class Allocator>
    constexpr void
    vector<T, Allocator>::swap(vector& other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value ||
                                                       std::allocator_traits<allocator_type>::is_always_equal::value)
    {
        T* dataToSwap = mData;
        T* dataSwappedWith = other.mData;
        size_type sizeToSwap = mSize;
        size_type sizeSwappedWith = other.mSize;
        size_type capacityToSwap = mCapacity;
        size_type capacitySwappedWith = other.mCapacity;

        mData = dataSwappedWith;
        mSize = sizeSwappedWith;
        mCapacity = capacitySwappedWith;

        other.mData = dataToSwap;
        other.mSize = sizeToSwap;
        other.mCapacity = capacitySwappedWith;

        if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_swap::value)
        {
            allocator_type allocatorToSwap = mAllocator;
            allocator_type allocatorSwappedWith = other.mAllocator;

            mAllocator = allocatorSwappedWith;

            other.mAllocator = allocatorToSwap;
        }
    }

    template<class T, class Allocator>
    constexpr bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
        { return false; }

        for (std::size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
            { return false; }
        }

        return true;
    }

    template<class T, class Allocator>
    constexpr auto operator<=>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
        { return lhs.size() <=> rhs.size(); }

        for (std::size_t i = 0; i < lhs.size(); i++)
        {
            if (auto cmp = lhs[i] <=> rhs[i]; cmp != 0)
            { return cmp; }
        }

        return std::strong_ordering::equal;
    }

    template<class T, class Allocator>
    void
    vector<T, Allocator>::mGrow()
    {
        mCapacity = mCapacity == 0 ? 1 : mCapacity * 2;

        value_type* newData = mAllocator.allocate(mCapacity);

        for (size_type i = 0; i < mSize; i++)
        {
            std::allocator_traits<allocator_type>::construct(mAllocator, &newData[i], mData[i]);
            std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i]);
        }

        mAllocator.deallocate(mData, mCapacity);

        mData = newData;
    }

    template<class T, class Allocator>
    void
    vector<T, Allocator>::mDestroy()
    {
        for (size_type i = 0; i < mSize; i++)
        { std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i]); }
    }

    template<class T, class Allocator>
    [[nodiscard]] bool
    vector<T, Allocator>::mExceedsMaxSize() const
    { return mCapacity >= max_size() || mSize >= max_size(); }

    template<class T, class Allocator>
    [[nodiscard]] bool
    vector<T, Allocator>::mNeedsResize() const
    { return mSize >= mCapacity; }
}

#endif // SMOOLLD_VECTOR_DEFINITION
