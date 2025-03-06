#ifndef SMOOLLD_VECTOR_DECLARATION
#define SMOOLLD_VECTOR_DECLARATION

#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <type_traits>

namespace smoolld
{
    template<class T, class Allocator = std::allocator<T>>
    class vector
    {
        public:
            template<std::random_access_iterator IteratorType>
            class iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = typename std::remove_pointer<IteratorType>::type;
                using pointer = value_type*;
                using reference = value_type&;

                public:
                    iterator();
                    iterator(IteratorType pointer);
                    iterator(const iterator& other);

                    iterator& operator=(const iterator& other);
                    iterator& operator++();
                    iterator& operator--();
                    iterator& operator+=(std::size_t n);
                    iterator& operator-=(std::size_t n);

                    iterator operator++(int);
                    iterator operator--(int);
                    iterator operator+(std::size_t n) const;
                    iterator operator-(std::size_t n) const;

                    bool operator==(const iterator& other) const;
                    bool operator!=(const iterator& other) const;
                    bool operator>(const iterator& other) const;
                    bool operator<(const iterator& other) const;
                    bool operator>=(const iterator& other) const;
                    bool operator<=(const iterator& other) const;

                    reference operator*() const;
                    reference operator[](std::size_t index) const;

                    pointer operator->() const;

                    difference_type operator-(const iterator& other);

                    [[nodiscard]] pointer base() const;
                private:
                    pointer mPointer;
            };
            template<std::random_access_iterator IteratorType>
            class const_iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = const typename std::remove_pointer<IteratorType>::type;
                using pointer = value_type*;
                using reference = value_type&;

                public:
                    const_iterator();
                    const_iterator(IteratorType pointer);
                    const_iterator(const const_iterator& other);
                    const_iterator(const iterator<IteratorType>& other);

                    const_iterator& operator=(const const_iterator& other);
                    const_iterator& operator++();
                    const_iterator& operator--();
                    const_iterator& operator+=(std::size_t n);
                    const_iterator& operator-=(std::size_t n);

                    const_iterator operator++(int);
                    const_iterator operator--(int);
                    const_iterator operator+(std::size_t n) const;
                    const_iterator operator-(std::size_t n) const;

                    bool operator==(const const_iterator& other) const;
                    bool operator!=(const const_iterator& other) const;
                    bool operator>(const const_iterator& other) const;
                    bool operator<(const const_iterator& other) const;
                    bool operator>=(const const_iterator& other) const;
                    bool operator<=(const const_iterator& other) const;

                    reference operator*() const;
                    reference operator[](std::size_t index) const;

                    pointer operator->() const;

                    difference_type operator-(const const_iterator& other);

                    [[nodiscard]] pointer base() const;
                private:
                    pointer mPointer;
            };
            template<std::random_access_iterator IteratorType>
            class reverse_iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = typename std::remove_pointer<IteratorType>::type;
                using pointer = value_type*;
                using reference = value_type&;

                public:
                    reverse_iterator();
                    reverse_iterator(IteratorType pointer);
                    reverse_iterator(const reverse_iterator& other);
                    reverse_iterator(const iterator<IteratorType>& iterator);

                    reverse_iterator& operator=(const reverse_iterator& other);
                    reverse_iterator& operator++();
                    reverse_iterator& operator--();
                    reverse_iterator& operator+=(std::size_t n);
                    reverse_iterator& operator-=(std::size_t n);

                    reverse_iterator operator++(int);
                    reverse_iterator operator--(int);
                    reverse_iterator operator+(std::size_t n) const;
                    reverse_iterator operator-(std::size_t n) const;

                    bool operator==(const reverse_iterator& other) const;
                    bool operator!=(const reverse_iterator& other) const;
                    bool operator>(const reverse_iterator& other) const;
                    bool operator<(const reverse_iterator& other) const;
                    bool operator>=(const reverse_iterator& other) const;
                    bool operator<=(const reverse_iterator& other) const;

                    reference operator*() const;
                    reference operator[](std::size_t index) const;

                    pointer operator->() const;

                    difference_type operator-(const reverse_iterator& other);
                private:
                    pointer mPointer;
            };
            template<std::random_access_iterator IteratorType>
            class const_reverse_iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = const typename std::remove_pointer<IteratorType>::type;
                using pointer = value_type*;
                using reference = value_type&;

                public:
                    const_reverse_iterator();
                    const_reverse_iterator(IteratorType pointer);
                    const_reverse_iterator(const const_reverse_iterator& other);
                    const_reverse_iterator(const const_iterator<IteratorType>& iterator);

                    const_reverse_iterator& operator=(const const_reverse_iterator& other);
                    const_reverse_iterator& operator++();
                    const_reverse_iterator& operator--();
                    const_reverse_iterator& operator+=(std::size_t n);
                    const_reverse_iterator& operator-=(std::size_t n);

                    const_reverse_iterator operator++(int);
                    const_reverse_iterator operator--(int);
                    const_reverse_iterator operator+(std::size_t n) const;
                    const_reverse_iterator operator-(std::size_t n) const;

                    bool operator==(const const_reverse_iterator& other) const;
                    bool operator!=(const const_reverse_iterator& other) const;
                    bool operator>(const const_reverse_iterator& other) const;
                    bool operator<(const const_reverse_iterator& other) const;
                    bool operator>=(const const_reverse_iterator& other) const;
                    bool operator<=(const const_reverse_iterator& other) const;

                    reference operator*() const;
                    reference operator[](std::size_t index) const;

                    pointer operator->() const;

                    difference_type operator-(const const_reverse_iterator& other);
                private:
                    pointer mPointer;
            };
        public:
            using value_type = T;
            using allocator_type = Allocator;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type&;
            using const_reference = const value_type&;

            constexpr vector() noexcept(noexcept(allocator_type()));
            constexpr vector(const allocator_type& allocator) noexcept;
            vector(size_type count, const allocator_type& allocator = allocator_type());
            constexpr vector(size_type count, const_reference value, const allocator_type& allocator = allocator_type());
            template<class InputIt>
            constexpr vector(InputIt first, InputIt last, const allocator_type& allocator = allocator_type());
            constexpr vector(const vector& other);
            constexpr vector(vector&& other) noexcept;
            constexpr vector(const vector& other, const std::type_identity_t<allocator_type>& allocator);
            constexpr vector(vector&& other, const std::type_identity_t<allocator_type>& allocator) noexcept;
            vector(std::initializer_list<value_type> ilist, const allocator_type& allocator = allocator_type());
            constexpr ~vector();

            constexpr vector& operator=(const vector& other);
            vector& operator=(vector&& other) noexcept;
            constexpr vector& operator=(std::initializer_list<value_type> ilist);

            constexpr void assign(size_type count, const_reference value);
            template<class InputIt>
            constexpr void assign(InputIt first, InputIt last);
            constexpr void assign(std::initializer_list<T> ilist);

            [[nodiscard]] constexpr allocator_type get_allocator() const noexcept;

            // ELEMENT ACCESS
            [[nodiscard]] constexpr reference at(size_type index);
            [[nodiscard]] constexpr const_reference at(size_type index) const;

            [[nodiscard]] constexpr reference operator[](size_type index);
            [[nodiscard]] constexpr const_reference operator[](size_type index) const;

            [[nodiscard]] constexpr reference front();
            [[nodiscard]] constexpr const_reference front() const;

            [[nodiscard]] constexpr reference back();
            [[nodiscard]] constexpr const_reference back() const;

            [[nodiscard]] constexpr value_type* data() noexcept;
            [[nodiscard]] constexpr const value_type* data() const noexcept;

            // ITERATORS
            [[nodiscard]] constexpr iterator<value_type*> begin() noexcept;
            [[nodiscard]] constexpr const_iterator<value_type*> begin() const noexcept;
            [[nodiscard]] constexpr const_iterator<value_type*> cbegin() const noexcept;

            [[nodiscard]] constexpr iterator<value_type*> end() noexcept;
            [[nodiscard]] constexpr const_iterator<value_type*> end() const noexcept;
            [[nodiscard]] constexpr const_iterator<value_type*> cend() const noexcept;

            [[nodiscard]] constexpr reverse_iterator<value_type*> rbegin() noexcept;
            [[nodiscard]] constexpr const_reverse_iterator<value_type*> rbegin() const noexcept;
            [[nodiscard]] constexpr const_reverse_iterator<value_type*> crbegin() const noexcept;

            [[nodiscard]] constexpr reverse_iterator<value_type*> rend() noexcept;
            [[nodiscard]] constexpr const_reverse_iterator<value_type*> rend() const noexcept;
            [[nodiscard]] constexpr const_reverse_iterator<value_type*> crend() const noexcept;

            // CAPACITY
            [[nodiscard]] constexpr bool empty() const noexcept;

            [[nodiscard]] constexpr size_type size() const noexcept;

            [[nodiscard]] constexpr size_type max_size() const noexcept;

            void constexpr reserve(size_type newCapacity);

            [[nodiscard]] constexpr size_type capacity() const noexcept;

            void constexpr shrink_to_fit();

            // MODIFIERS
            constexpr void clear() noexcept;

            [[maybe_unused]] constexpr iterator<value_type*> insert(const_iterator<value_type*> position, const_reference value);
            [[maybe_unused]] constexpr iterator<value_type*> insert(const_iterator<value_type*> position, value_type&& value);
            [[maybe_unused]] constexpr iterator<value_type*> insert(const_iterator<value_type*> position, size_type count, const_reference value);
            template<class InputIt>
            [[maybe_unused]] constexpr iterator<value_type*> insert(const_iterator<value_type*> position, InputIt first, InputIt last);
            [[maybe_unused]] constexpr iterator<value_type*> insert(const_iterator<value_type*> position, std::initializer_list<value_type> ilist);

            template<class... Args>
            [[maybe_unused]] constexpr iterator<value_type*> emplace(const_iterator<value_type*> position, Args&&... args)
            {
                size_type index = position - cbegin();

                if (mNeedsResize() || mSize + 1 >= mCapacity)
                { mGrow(); }

                for (size_type i = mSize; i > index; i--)
                {
                    std::allocator_traits<allocator_type>::construct(mAllocator, &mData[i], static_cast<T&&>(mData[i - 1]));
                    std::allocator_traits<allocator_type>::destroy(mAllocator, &mData[i - 1]);
                }

                std::allocator_traits<allocator_type>::construct(mAllocator, &mData[index], std::forward<Args>(args)...);

                mSize++;

                return iterator(mData + index);
            }

            [[maybe_unused]] constexpr iterator<value_type*> erase(const_iterator<value_type*> position);
            [[maybe_unused]] constexpr iterator<value_type*> erase(const_iterator<value_type*> first, const_iterator<value_type*> last);

            constexpr void push_back(const_reference value);
            constexpr void push_back(T&& value);

            template<class... Args>
            constexpr reference emplace_back(Args&&... args)
            {
                if (mNeedsResize() || mSize + 1 >= mCapacity)
                { mGrow(); }

                std::allocator_traits<allocator_type>::construct(mAllocator, &mData[mSize], std::forward<Args>(args)...);

                mSize++;

                return mData[mSize - 1];
            }

            constexpr void pop_back();

            constexpr void resize(size_type count);
            constexpr void resize(size_type count, const_reference value);

            constexpr void swap(vector& other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value ||
                                                        std::allocator_traits<allocator_type>::is_always_equal::value);
        private:
            void mGrow();
            void mDestroy();

            [[nodiscard]] bool mExceedsMaxSize() const;
            [[nodiscard]] bool mNeedsResize() const;

            value_type* mData;

            size_type mSize;
            size_type mCapacity;

            allocator_type mAllocator;
    };
}

#include "iterator.tpp"
#include "const_iterator.tpp"
#include "reverse_iterator.tpp"
#include "const_reverse_iterator.tpp"

#include "vector.tpp"

#endif // SMOOLLD_VECTOR_DECLARATION
