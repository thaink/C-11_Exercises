#ifndef KTSTD_VECTOR_MAP_H
#define KTSTD_VECTOR_MAP_H

#include <cstddef>
#include <memory>
#include <vector>
#include <algorithm>

namespace ktstd {
    using Key           = std::string;
    using T             = std::string;
    using Allocator     = std::allocator<std::pair<std::string,std::string>>;
    using Compare       = std::less<std::string>;
    using value_type    = std::pair<Key,T>;

    //Key = vector_map::Key
    //value_type = vector_map::value_type
    //template <typename Key, typename value_type, typename Compare>
    class vector_map_compare : public std::binary_function<value_type, value_type, bool>
    {
    public:
        Compare c;

        vector_map_compare(const Compare& x)
            : c(x) {}

    public:
        bool operator()(const value_type& a, const value_type& b) const
            { return c(a.first, b.first); }

        bool operator()(const value_type& a, const Key& b) const
            { return c(a.first, b); }

        bool operator()(const Key& a, const value_type& b) const
            { return c(a, b.first); }

        bool operator()(const Key& a, const Key& b) const
            { return c(a, b); }

    };

    //Key       = std::string
    //T         = std::string
    //Compare   = std::less<std::string>
    //Allocator = std:pair<std:string,std::string>
    //template <typename Key, typename T, typename Compare = std::less<Key>,
    //		  typename Allocator = std::allocator<std::pair<const Key,T>>>
    class vector_map : private std::vector<std::pair<Key,T>, Allocator> {
        /*
         * ivariants:
         * - the vector_must strictly ordered.
         * - [] let access the mapped_type with Key not index as vector
         * - iterator return pair<const Key, T> which does not allowed to changes Key
         */
        //basic types
    public:
        using this_type                 = vector_map;//vector_map<Key,T,Compare,Allocator>;
        using key_type                  = Key;
        using mapped_type               = T;
        using value_type                = std::pair<Key,T>; //value use will see
        using base_type                 = std::vector<value_type, Allocator>;
        using key_compare               = Compare;
        using value_compare             = vector_map_compare;//vector_map_compare<Key,value_type,Compare>
        using allocator_type            = Allocator;
        using size_type                 = base_type::size_type;

        using pointer                   = base_type::pointer;
        using const_pointer             = base_type::const_pointer;
        using reference                 = base_type::reference;
        using const_reference           = base_type::const_reference;
        //iterator types
        using iterator                  = base_type::iterator;
        using const_iterator            = base_type::const_iterator;
        using reverse_iterator          = base_type::reverse_iterator;
        using const_reverse_iterator    = base_type::const_reverse_iterator;
        using insert_return_type        = typename std::pair<iterator, bool>;

    protected:
        //vector dont have user comparison
        //so we need to store it here
        value_compare mCompare;

    public:
        //constructor, copy and move operations
        vector_map();
        explicit vector_map(const allocator_type& allocator);
        explicit vector_map(const key_compare& comp, const allocator_type& allocator = allocator_type());

        vector_map(const this_type& x);
        vector_map(this_type&& x);
        vector_map(this_type&& x, const allocator_type& allocator);
        vector_map(std::initializer_list<value_type> ilist, const key_compare& compare = key_compare(), const allocator_type& allocator = allocator_type());

        template <typename InputIterator>
        vector_map(InputIterator first, InputIterator last);

        template <typename InputIterator>
        vector_map(InputIterator first, InputIterator last, const key_compare& compare);

        this_type& operator=(const this_type& x);
        this_type& operator=(std::initializer_list<value_type> ilist);
        this_type& operator=(this_type&& x);

        //function inherited from base_type
        using base_type::begin;
        using base_type::end;
        using base_type::size;
        using base_type::rbegin;
        using base_type::rend;

        //insert, erase functions
        void swap(this_type& x);

        const key_compare& key_comp() const;
        key_compare&       key_comp();

        const value_compare& value_comp() const;
        value_compare&       value_comp();

        template <class... Args>
        std::pair<iterator, bool> emplace(Args&&... args);

        template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);

        std::pair<iterator, bool> insert(const value_type& value);
        template <typename P>
        std::pair<iterator, bool> insert(P&& otherValue);

        iterator insert(const_iterator position, const value_type& value);
        iterator insert(const_iterator position, value_type&& value);

        void insert(std::initializer_list<value_type> ilist);

        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last);

        iterator  erase(const_iterator position);
        iterator  erase(const_iterator first, const_iterator last);
        size_type erase(const key_type& k);

        reverse_iterator erase(const_reverse_iterator position);
        reverse_iterator erase(const_reverse_iterator first, const_reverse_iterator last);

        //access functions
        iterator       find(const key_type& k);
        const_iterator find(const key_type& k) const;

        template <typename U, typename BinaryPredicate>
        iterator       find_as(const U& u, BinaryPredicate predicate);

        template <typename U, typename BinaryPredicate>
        const_iterator find_as(const U& u, BinaryPredicate predicate) const;

        size_type count(const key_type& k) const;

        iterator       lower_bound(const key_type& k);
        const_iterator lower_bound(const key_type& k) const;

        iterator       upper_bound(const key_type& k);
        const_iterator upper_bound(const key_type& k) const;

        std::pair<iterator, iterator>             equal_range(const key_type& k);
        std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

        template <typename U, typename BinaryPredicate>
        std::pair<iterator, iterator>             equal_range(const U& u, BinaryPredicate predicate);

        template <typename U, typename BinaryPredicate>
        std::pair<const_iterator, const_iterator> equal_range(const U& u, BinaryPredicate) const;


        mapped_type& operator[](const key_type& k);
        mapped_type& operator[](key_type&& k);
    };


    /*==============================================
     * vector_map constructor, copy and move operations
     ==============================================*/
    vector_map::vector_map()
        :base_type(), mCompare{Compare()}
    {

    }

    vector_map::vector_map(const allocator_type& allocator)
        :base_type(allocator), mCompare{Compare()}
    {

    }

    vector_map::vector_map(const key_compare& comp, const allocator_type& allocator)
        :base_type(allocator), mCompare{comp}
    {

    }

    vector_map::vector_map(const this_type& x)
        :base_type(x), mCompare{x.mCompare}
    {

    }

    vector_map::vector_map(this_type&& x)
        :base_type(std::move(x)), mCompare(x.mCompare)
    {

    }

    vector_map::vector_map(this_type&& x, const allocator_type& allocator)
        :base_type(std::move(x),allocator), mCompare{x.mCompare}
    {

    }

    vector_map::vector_map(std::initializer_list<value_type> ilist, const key_compare& compare,
                           const allocator_type& allocator)
        :base_type(allocator), mCompare{compare}
    {
        insert(ilist);
    }

    template <typename InputIterator>
    vector_map::vector_map(InputIterator first, InputIterator last)
        :base_type(), mCompare{Compare()}
    {
        insert(first,last);
    }

    template <typename InputIterator>
    vector_map::vector_map(InputIterator first, InputIterator last, const key_compare& compare)
    :base_type(), mCompare{compare}
    {
        insert(first,last);
    }

    vector_map::this_type& vector_map::operator=(const this_type& x)
    {
        base_type::operator=(x);
        mCompare = x.mCompare;
        return *this;
    }

    vector_map::this_type& vector_map::operator=(std::initializer_list<value_type> ilist)
    {
        base_type::clear();
        insert(ilist);
        return *this;
    }

    vector_map::this_type& vector_map::operator=(this_type&& x)
    {
        mCompare = x.mCompare;
        base_type::operator =(std::move(x));
        return *this;
    }

    /*==============================================
     * vector_map insert, erase functions
     ==============================================*/

    void vector_map::swap(this_type& x)
    {
        std::swap(mCompare,x.mCompare);
        base_type::swap(x);
    }

    inline const vector_map::key_compare& vector_map::key_comp() const
    {
        return mCompare.c;
    }

    inline vector_map::key_compare& vector_map::key_comp()
    {
        return mCompare.c;
    }

    inline const vector_map::value_compare& vector_map::value_comp() const
    {
        return mCompare;
    }

    inline vector_map::value_compare& vector_map::value_comp()
    {
        return mCompare;
    }

    template <class... Args>
    std::pair<vector_map::iterator, bool> vector_map::emplace(Args&&... args)
    {
        auto val = value_type(std::forward<Args>(args)...);
        return insert(val);
    }

    template <class... Args>
    vector_map::iterator vector_map::emplace_hint(const_iterator position, Args&&... args)
    {
        auto val = value_type(std::forward<Args>(args)...);
        return insert(position,val);
    }

    std::pair<vector_map::iterator, bool> vector_map::insert(const value_type& value)
    {
        auto itLB = lower_bound(value.first);
        if((itLB != end()) && !mCompare(value,*itLB))
            return std::pair<iterator, bool>(itLB,false);
        return std::pair<iterator, bool>(base_type::insert(itLB,value),true);
    }

    template <typename P>
    std::pair<vector_map::iterator, bool> vector_map::insert(P&& otherValue)
    {
        value_type value = value_type(std::forward<P>(otherValue));
        auto itLB = lower_bound(value.first);
        if((itLB != end()) && !mCompare(value,*itLB))
            return std::pair<iterator, bool>(itLB,false);
        return std::pair<iterator, bool>(base_type::insert(itLB,std::move(value)),true);

    }

    vector_map::iterator vector_map::insert(const_iterator position, const value_type& value)
    {
        //check if position is correct
        if ((position == end()) || mCompare(value,*position))
            if((position == begin()) || mCompare(*(position),value))
                return base_type::insert(position,value);

        //if position is not correct
        return insert(value).first;
    }

    vector_map::iterator vector_map::insert(const_iterator position, value_type&& value)
    {
        //check if position is correct
        if ((position == end()) || mCompare(value,*position))
            if((position == begin()) || mCompare(*(position),value))
                return base_type::insert(position,std::move(value));

        //if position is not correct
        return insert(std::move(value)).first;
    }

    void vector_map::insert(std::initializer_list<value_type> ilist)
    {
        for(auto val:ilist)
            insert(val);
    }

    template <typename InputIterator>
    void vector_map::insert(InputIterator first, InputIterator last)
    {
        for(; first != last; ++first)
            insert(*first);
    }

    vector_map::iterator  vector_map::erase(const_iterator position)
    {
        return base_type::erase(position);
    }

    vector_map::iterator  vector_map::erase(const_iterator first, const_iterator last)
    {
        return base_type::erase(first,last);
    }

    vector_map::size_type vector_map::erase(const key_type& k)
    {
        auto itLB = lower_bound(k);
        if((itLB == end()) || mCompare(k,*itLB))
            return 0;
        base_type::erase(itLB);
        return 1;
    }

    inline vector_map::reverse_iterator vector_map::erase(const_reverse_iterator position)
    {
        return reverse_iterator(base_type::erase((++position).base()));
    }

    inline vector_map::reverse_iterator vector_map::erase(const_reverse_iterator first, const_reverse_iterator last)
    {
        return reverse_iterator(base_type::erase((++last).base(),(++first).base()));
    }


    /*==============================================
     * vector_map access functions
     ==============================================*/
    inline vector_map::iterator  vector_map::find(const key_type& k)
    {
        std::pair<iterator,iterator> itPair = equal_range(k);
        if(itPair.first != itPair.second)
            return itPair.first;
        return end();
    }

    inline vector_map::const_iterator vector_map::find(const key_type& k) const
    {
        std::pair<const_iterator,const_iterator> itPair = equal_range(k);
        if(itPair.first != itPair.second)
            return itPair.first;
        return end();
    }

    template <typename U, typename BinaryPredicate>
    vector_map::iterator vector_map::find_as(const U& u, BinaryPredicate predicate)
    {
        std::pair<iterator,iterator> itPair = equal_range<U,BinaryPredicate>(u,predicate);
        if(itPair.first != itPair.second)
            return itPair.first;
        return end();
    }

    template <typename U, typename BinaryPredicate>
    vector_map::const_iterator vector_map::find_as(const U& u, BinaryPredicate predicate) const
    {
        std::pair<const_iterator,const_iterator> itPair = equal_range<U,BinaryPredicate>(u,predicate);
        if(itPair.first != itPair.second)
            return itPair.first;
        return end();
    }

    vector_map::size_type vector_map::count(const key_type& k) const
    {
        std::pair<const_iterator,const_iterator> itPair = equal_range(k);
        if(itPair.first != itPair.second)
            return 1;
        return 0;
    }

    vector_map::iterator vector_map::lower_bound(const key_type& k)
    {
        return std::lower_bound(begin(), end(), k, mCompare);
    }

    vector_map::const_iterator vector_map::lower_bound(const key_type& k) const
    {
        return std::lower_bound(begin(), end(), k, mCompare);
    }

    vector_map::iterator  vector_map::upper_bound(const key_type& k)
    {
        return std::upper_bound(begin(), end(), k, mCompare);
    }

    vector_map::const_iterator vector_map::upper_bound(const key_type& k) const
    {
        return std::upper_bound(begin(), end(), k, mCompare);
    }

    std::pair<vector_map::iterator, vector_map::iterator>  vector_map::equal_range(const key_type& k)
    {
        iterator itLB = lower_bound(k);
        if((itLB == end()) || mCompare(k,*itLB))
            return std::pair<iterator,iterator>(itLB,itLB);

        iterator itUP(itLB);
        return std::pair<iterator,iterator>(itLB,++itUP);
    }

    std::pair<vector_map::const_iterator, vector_map::const_iterator> vector_map::equal_range(const key_type& k) const
    {
        const_iterator itLB = lower_bound(k);
        if((itLB == end()) || mCompare(k,*itLB))
            return std::pair<const_iterator,const_iterator>(itLB,itLB);

        const_iterator itUP(itLB);
        return std::pair<const_iterator,const_iterator>(itLB,++itUP);
    }

    template <typename U, typename BinaryPredicate>
    std::pair<vector_map::iterator, vector_map::iterator>  vector_map::equal_range(const U& u, BinaryPredicate predicate)
    {
        iterator itLB = std::lower_bound(begin(), end(), u, mCompare);
        if((itLB == end()) || mCompare(u,*itLB))
            return std::pair<iterator,iterator>(itLB,itLB);

        iterator itUP(itLB);
        return std::pair<iterator,iterator>(itLB,++itUP);
    }

    template <typename U, typename BinaryPredicate>
    std::pair<vector_map::const_iterator, vector_map::const_iterator> vector_map::equal_range(const U& u, BinaryPredicate) const
    {
        const_iterator itLB = std::lower_bound(begin(), end(), u, mCompare);
        if((itLB == end()) || mCompare(u,*itLB))
            return std::pair<const_iterator,const_iterator>(itLB,itLB);

        const_iterator itUP(itLB);
        return std::pair<const_iterator,const_iterator>(itLB,++itUP);
    }


    vector_map::mapped_type& vector_map::operator[](const key_type& k)
    {
        iterator itLB(lower_bound(k));
        if((itLB == end()) || (mCompare(k,*itLB)))
            insert(itLB, value_type(k,mapped_type()));
        return (*itLB).second;
    }

    vector_map::mapped_type& vector_map::operator[](key_type&& k)
    {
        iterator itLB(lower_bound(k));
        if((itLB == end()) || (mCompare(k,*itLB)))
            insert(itLB, value_type(std::move(k),mapped_type()));
        return (*itLB).second;
    }


}//ktstd

#endif // KTSTD_VECTOR_MAP_H

