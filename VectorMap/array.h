#ifndef KTSTD_ARRAY_H
#define KTSTD_ARRAY_H

#include <cstddef>
#include <memory>

namespace ktstd {

    /*
     * Wrap built-in array in a container to better manipulate it
     * It does not allowed to change size, just as the built-in one
     */

    template <class T, size_t N=1>
    class array {
        using this_type                 = array<T,N>;
        using value_type                = T;
        using reference                 = value_type&;
        using const_reference           = const value_type&;
        //iterator types
        using iterator                  = value_type*;
        using const_iterator            = const value_type*;
        using reverse_iterator          = std::reverse_iterator<iterator>;
        using const_reverse_iterator    = std::reverse_iterator<const_iterator>;
        using size_type                 = std::size_t;
        using difference_type           = std::ptrdiff_t;

    public:
        //data and number of data is public
        //No constructor destructor needed
        const size_type count = N;
        value_type mData[N];

        //For iterator
        iterator       begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;

        iterator       end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;

        reverse_iterator       rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;

        reverse_iterator       rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept;

        //array method
        void fill(const value_type& value);
        void swap(this_type& x);
        bool      empty() const;
        size_type size() const;
        size_type max_size() const;

        T*       data() noexcept;
        const T* data() const noexcept;

        reference       operator[](size_type i);
        const_reference operator[](size_type i) const;
        const_reference at(size_type i) const;
        reference       at(size_type i);

        reference       front();
        const_reference front() const;

        reference       back();
        const_reference back() const;

        bool validate() const;
        int  validate_iterator(const_iterator i) const;

    };

    /*=================================================
     * For iterator
     =================================================*/
    template <class T, size_t N>
    inline typename array<T,N>::iterator array<T,N>::begin() noexcept
    {
        return &mData[0];
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_iterator array<T,N>::begin() const noexcept
    {
        return &mData[0];
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_iterator array<T,N>::cbegin() const noexcept
    {
        return &mData[0];
    }


    template <class T, size_t N>
    inline typename array<T,N>::iterator array<T,N>::end() noexcept
    {
        return &mData[N];
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_iterator array<T,N>::end() const noexcept
    {
        return &mData[N];
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_iterator array<T,N>::cend() const noexcept
    {
        return &mData[N];
    }


    template <class T, size_t N>
    inline typename array<T,N>::reverse_iterator array<T,N>::rbegin() noexcept
    {
        return reverse_iterator(&mData[N]);
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_reverse_iterator array<T,N>::rbegin() const noexcept
    {
        return const_reverse_iterator(&mData[N]);
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_reverse_iterator array<T,N>::crbegin() const noexcept
    {
        return const_reverse_iterator(&mData[N]);
    }

    template <class T, size_t N>
    inline typename array<T,N>::reverse_iterator array<T,N>::rend() noexcept
    {
        return reverse_iterator(&mData[0]);
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_reverse_iterator array<T,N>::rend() const noexcept
    {
        return const_reverse_iterator(&mData[0]);
    }

    template <class T, size_t N>
    inline typename array<T,N>::const_reverse_iterator array<T,N>::crend() const noexcept
    {
        return const_reverse_iterator(&mData[0]);
    }


    /*=================================================
     * For array
     =================================================*/
    template <class T, size_t N>
    void array<T,N>::fill(const value_type& value)
    {
        std::fill_n(begin(), N, value);
    }

    //both has N elements
    template <class T, size_t N>
    void array<T,N>::swap(this_type& x)
    {
        std::swap(mData,x.mData);
    }

    template <class T, size_t N>
    bool  array<T,N>::empty() const
    {
        return (N==0);
    }

    template <class T, size_t N>
    typename array<T,N>::size_type array<T,N>::size() const
    {
        return size_type(N);
    }

    template <class T, size_t N>
    typename array<T,N>::size_type array<T,N>::max_size() const
    {
        return size_type(N);
    }

    template <class T, size_t N>
    T* array<T,N>::data() noexcept
    {
        return mData;
    }

    template <class T, size_t N>
    const T* array<T,N>::data() const noexcept
    {
        return mData;
    }

    template <class T, size_t N>
    typename array<T,N>::reference array<T,N>::operator[](size_type i)
    {
        return mData[i];
    }

    template <class T, size_t N>
    typename array<T,N>::const_reference array<T,N>::operator[](size_type i) const
    {
        return mData[i];
    }

    template <class T, size_t N>
    typename array<T,N>::const_reference array<T,N>::at(size_type i) const
    {
        return mData[i];
    }

    template <class T, size_t N>
    typename array<T,N>::reference array<T,N>::at(size_type i)
    {
        return mData[i];
    }

    template <class T, size_t N>
    typename array<T,N>::reference array<T,N>::front()
    {
        return mData[0];
    }

    template <class T, size_t N>
    typename array<T,N>::const_reference array<T,N>::front() const
    {
        return mData[0];
    }

    template <class T, size_t N>
    typename array<T,N>::reference  array<T,N>::back()
    {
        return mData[N-1];
    }

    template <class T, size_t N>
    typename array<T,N>::const_reference array<T,N>::back() const
    {
        return mData[N-1];
    }

    template <class T, size_t N>
    bool array<T,N>::validate() const
    {
        return true;
    }

    template <class T, size_t N>
    int  array<T,N>::validate_iterator(const_iterator i) const
    {
        auto pos = i - &mData[0];
        if ((pos>=0) && (pos<N)) return 2;
        if (pos == N) return 1;
        return 0;
    }

    /*=================================================
     * Helper function
     =================================================*/
    template <class T, size_t N>
    inline bool operator==(const array<T,N>& a, const array<T,N>& b)
    {
        return std::equal(a.begin(), a.end(), b.begin());
    }


    template <class T, size_t N>
    inline bool operator<(const array<T,N>& a, const array<T,N>& b)
    {
        return std::lexicographical_compare(a.begin(),a.end(),b.begin(),b.end());
    }


    template <class T, size_t N>
    inline bool operator!=(const array<T,N>& a, const array<T,N>& b)
    {
        return !std::equal(a.begin(), a.end(), b.begin());
    }


    template <class T, size_t N>
    inline bool operator>(const array<T,N>& a, const array<T,N>& b)
    {
        return std::lexicographical_compare(b.begin(),b.end(),a.begin(),a.end());
    }


    template <class T, size_t N>
    inline bool operator<=(const array<T,N>& a, const array<T,N>& b)
    {
        return !std::lexicographical_compare(b.begin(),b.end(),a.begin(),a.end());
    }


    template <class T, size_t N>
    inline bool  operator>=(const array<T,N>& a, const array<T,N>& b)
    {
        return !std::lexicographical_compare(a.begin(),a.end(),b.begin(),b.end());
    }


    template <class T, size_t N>
    inline void swap(array<T,N>& a, array<T,N>& b)
    {
        std::swap(a.mData, b.mData);
    }


}//end ktstd

#endif // KTSTD_ARRAY_H

