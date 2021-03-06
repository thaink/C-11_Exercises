#ifndef KTSTD_LIST_MAP_H
#define KTSTD_LIST_MAP_H

#include <cstddef>
#include <iterator>
#include <map>
#include <memory>
#include <cassert>

namespace ktstd {

    /**
     * What is a list map?
     * basically, it is a map but have a list
     * to specify the sequence of object.
     *
     * How to do this?
     * 1. Inherit the std::map
     * There is two problem when we inherit a class
     * from a library that we do not own.
     * - Since we mess with internal structure so
     * we have to catch and overload all its function.
     * it is easy to miss some. And it is not future
     * proof. when they add new function to the class,
     * our modification will be dump.
     * - if the function in the original class is not
     * virtual, user can cast to original type. Then
     * the original function will be called.
     *
     * 2. include a map in our structure
     * Better the previous approach. May lead to
     * overhead since we have to called function through
     * original layer.
     */


    // T = list_map::value_type = pair<const Key,T>
    template <typename T>
    struct list_map_base {
        using this_type     = list_map_base;
        using value_type    = T;

        //data
        value_type value; //pair of Key/Value
        this_type* Prev;
        this_type* Next;

        list_map_base()
            :value(), Prev(nullptr), Next(nullptr) {}

        list_map_base(const value_type val)
            :value(val), Prev(nullptr), Next(nullptr) {}
    };


    // T         = list_map::value_type
    // Pointer   = list_map::value_type*
    // Reference = list_map::value_type&
    template <typename T, typename Pointer, typename Reference>
    struct list_map_iterator
    {
        using this_type         = list_map_iterator<T,Pointer, Reference>;
        using iterator          = list_map_iterator<T, T*, T&>;
        using const_iterator    = list_map_iterator<T,const T*,const T&>;
        using size_type         = std::size_t;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using node_type         = list_map_base<T>;
        using pointer           = Pointer;
        using reference         = Reference;
        using iterator_category = std::bidirectional_iterator_tag;

    public:
        node_type* mpNode;

    public:
        list_map_iterator();
        list_map_iterator(const node_type* pNode);
        list_map_iterator(const iterator& x);

        reference operator*() const;
        pointer   operator->() const;

        this_type& operator++();
        this_type  operator++(int);

        this_type& operator--();
        this_type  operator--(int);

    };

    template<class Key, class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, list_map_base<std::pair<const Key,T>>>>>
    class list_map {

    public:
        //basic types
        using this_type                 = list_map<Key,T,Compare,Allocator>;
        using size_type                 = std::size_t;
        using key_type                  = Key;
        using mapped_type               = T;
        using value_type                = typename std::pair<const Key,T>; //value use will see
        using reference                 = value_type&;
        using const_reference           = const value_type&;
        using node_type                 = list_map_base<value_type>; //actual value in the map
        using map_type                  = typename std::map<Key,node_type,Compare,Allocator>;
        //iterator types
        using iterator                  = ktstd::list_map_iterator<value_type,value_type*,value_type&>;
        using const_iterator            = ktstd::list_map_iterator<value_type, const value_type*, const value_type&>;
        using reverse_iterator          = std::reverse_iterator<iterator>;
        using const_reverse_iterator    = std::reverse_iterator<const_iterator>;
        using allocator_type            = Allocator;
        using insert_return_type        = typename std::pair<iterator, bool>;


    protected:
        using internal_value_type       = node_type;

    protected:
        //internal data
        // nodes are order in sequences:
        // Front-----....-----Back------mNode
        // mNode.Next = Front
        // mNode.Prev = Back;
        node_type mNode;
        map_type  mMap;

    public:
        list_map(const Allocator& allocator = Allocator());
        list_map(const Compare& compare, const Allocator& allocator = Allocator());
        //copy is too expensive. since we have to rewrite every pointers
        //in the list before pushing it back to the map
        list_map(const list_map&) = delete;
        list_map& operator=(const list_map&) = delete;

    public:
        //iterator
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

    public:
        // List like methods
        reference       front();
        const_reference front() const;

        reference       back();
        const_reference back() const;

        // push_front and push_back which takes in a key/value pair
        bool            push_front(const value_type& value);
        bool            push_back(const value_type& value);

        // push_front and push_back which take key and value separately, for convenience
        bool            push_front(const key_type& key, const mapped_type& value);
        bool            push_back(const key_type& key, const mapped_type& value);

        void            pop_front();
        void            pop_back();

    public:
        // Map like methods
        iterator        find(const key_type& key);
        const_iterator  find(const key_type& key) const;

        template <typename U, typename Compare2>
        iterator       find_as(const U& u, Compare2 compare2);
        template <typename U, typename Compare2>
        const_iterator find_as(const U& u, Compare2 compare2) const;

        size_type count(const key_type& key) const;
        size_type erase(const key_type& key);

    public:
        // Shared methods which are common to list and map
        iterator erase(const_iterator position);
        reverse_iterator erase(const_reverse_iterator position);

        void clear();
        void reset_lose_memory();

        bool validate() const;
        int validate_iterator(const_iterator i) const;

    }; //list_map


    /**===============================================================
     * list_map_iterator
     =================================================================*/
    template <typename T, typename Pointer, typename Reference>
    list_map_iterator<T,Pointer,Reference>::list_map_iterator()
        :mpNode{nullptr}
    {

    }

    template <typename T, typename Pointer, typename Reference>
    list_map_iterator<T,Pointer,Reference>::list_map_iterator(const node_type* pNode)
        :mpNode{const_cast<node_type*>(pNode)}
    {

    }

    template <typename T, typename Pointer, typename Reference>
    list_map_iterator<T,Pointer,Reference>::list_map_iterator(const iterator& x)
    {
        mpNode=const_cast<node_type*>(x.mpNode);
    }

    template <typename T, typename Pointer, typename Reference>
    inline typename list_map_iterator<T,Pointer,Reference>::reference
    list_map_iterator<T,Pointer,Reference>::operator*() const
    {
        return static_cast<reference>(mpNode->value);
    }

    template <typename T, typename Pointer, typename Reference>
    inline typename list_map_iterator<T,Pointer,Reference>::pointer
    list_map_iterator<T,Pointer,Reference>::operator->() const
    {
        return static_cast<pointer>(&(mpNode->value));
    }

    template <typename T, typename Pointer, typename Reference>
    inline typename list_map_iterator<T,Pointer,Reference>::this_type&
    list_map_iterator<T,Pointer,Reference>::operator++()
    {
        mpNode = mpNode->Next;
        return *this;
    }

    template <typename T, typename Pointer, typename Reference>
    inline typename list_map_iterator<T,Pointer,Reference>::this_type
    list_map_iterator<T,Pointer,Reference>::operator++(int)
    {
        this_type temp{mpNode};
        mpNode = mpNode->Next;
        return temp;
    }

    template <typename T, typename Pointer, typename Reference>
    inline typename list_map_iterator<T,Pointer,Reference>::this_type&
    list_map_iterator<T,Pointer,Reference>::operator--()
    {
        mpNode = mpNode->Prev;
        return *this;
    }

    template <typename T, typename Pointer, typename Reference>
    inline typename list_map_iterator<T,Pointer,Reference>::this_type
    list_map_iterator<T,Pointer,Reference>::operator--(int)
    {
        this_type temp{mpNode};
        mpNode = mpNode->Prev;
        return temp;
    }

    //We provide comparision for iterator
    template <typename T, typename Pointer1, typename Reference1, typename Pointer2, typename Reference2>
    inline bool operator==(const list_map_iterator<T,Pointer1,Reference1>& a, const list_map_iterator<T,Pointer2,Reference2>& b)
    {
        return a.mpNode == b.mpNode;
    }

    template <typename T, typename Pointer1, typename Reference1, typename Pointer2, typename Reference2>
    inline bool operator!=(const list_map_iterator<T,Pointer1,Reference1>& a, const list_map_iterator<T,Pointer2,Reference2>& b)
    {
        return a.mpNode != b.mpNode;
    }



    /*===============================================================
     *list_map
     ===============================================================*/
    //For iterators
    template<class Key, class T, class Compare, class Allocator>
    list_map<Key, T, Compare, Allocator>::list_map(const Allocator& allocator)
    //list_map::list_map(const Allocator& allocator)
        :mNode(),mMap(allocator)
    {
        mNode.Next = &mNode;
        mNode.Prev = &mNode;
    }


    template<class Key, class T, class Compare, class Allocator>
    list_map<Key, T, Compare, Allocator>::list_map(const Compare& compare, const Allocator& allocator)
    //list_map::list_map(const Compare& compare, const Allocator& allocator)
        :mNode(),mMap(compare, allocator)
    {
        mNode.Next = &mNode;
        mNode.Prev = &mNode;
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::iterator
    list_map<Key, T, Compare, Allocator>::begin() noexcept
    //typename list_map::iterator list_map::begin() noexcept
    {
        return iterator(mNode.Next);
    }

    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_iterator
    list_map<Key, T, Compare, Allocator>::begin() const noexcept
    //typename list_map::const_iterator list_map::begin() const noexcept
    {
        return const_iterator(mNode.Next);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_iterator
    list_map<Key, T, Compare, Allocator>::cbegin() const noexcept
    //typename list_map::const_iterator list_map::cbegin() const noexcept
    {
        return const_iterator(mNode.Next);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::iterator
    list_map<Key, T, Compare, Allocator>::end() noexcept
    //typename list_map::iterator list_map::end() noexcept
    {
        return iterator(&mNode);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_iterator
    list_map<Key, T, Compare, Allocator>::end() const noexcept
    //typename list_map::const_iterator list_map::end() const noexcept
    {
        return const_iterator(&mNode);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_iterator
    list_map<Key, T, Compare, Allocator>::cend() const noexcept
    //typename list_map::const_iterator list_map::cend() const noexcept
    {
        return const_iterator(&mNode);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::reverse_iterator
    list_map<Key, T, Compare, Allocator>::rbegin() noexcept
    //typename list_map::reverse_iterator list_map::rbegin() noexcept
    {
        return reverse_iterator(&mNode);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_reverse_iterator
    list_map<Key, T, Compare, Allocator>::rbegin() const noexcept
    //typename list_map::const_reverse_iterator list_map::rbegin() const noexcept
    {
        return const_reverse_iterator(&mNode);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_reverse_iterator
    list_map<Key, T, Compare, Allocator>::crbegin() const noexcept
    //typename list_map::const_reverse_iterator list_map::crbegin() const noexcept
    {
        return const_reverse_iterator(&mNode);
    }

    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::reverse_iterator
    list_map<Key, T, Compare, Allocator>::rend() noexcept
    //typename list_map::reverse_iterator list_map::rend() noexcept
    {
        return reverse_iterator(mNode.Next);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_reverse_iterator
    list_map<Key, T, Compare, Allocator>::rend() const noexcept
    //typename list_map::const_reverse_iterator list_map::rend() const noexcept
    {
        return const_reverse_iterator(mNode.Next);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_reverse_iterator
    list_map<Key, T, Compare, Allocator>::crend() const noexcept
    //typename list_map::const_reverse_iterator list_map::crend() const noexcept
    {
        return const_reverse_iterator(mNode.Next);
    }


    //For List
    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::reference
    list_map<Key, T, Compare, Allocator>::front()
    {
        return static_cast<node_type*>(mNode.Next)->value;
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_reference
    list_map<Key, T, Compare, Allocator>::front() const
    {
        return static_cast<node_type*> (mNode.Next)->value;
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::reference
    list_map<Key, T, Compare, Allocator>::back()
    {
        return static_cast<node_type*> (mNode.Prev)->value;
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_reference
    list_map<Key, T, Compare, Allocator>::back() const
    {
        return static_cast<node_type*> (mNode.Prev)->value;
    }


    template<class Key, class T, class Compare, class Allocator>
    bool list_map<Key, T, Compare, Allocator>::push_front(const value_type& value)
    {
        node_type temp(value);
        auto res = mMap.emplace(value.first, temp);
        if (res.second) {
            node_type* pnode = static_cast<node_type*> (&((*res.first).second));

            pnode->Next = mNode.Next;
            pnode->Prev = &mNode;

            mNode.Next->Prev = pnode;
            mNode.Next  = pnode;//careful with the order
            return true;
        }
        return false;
    }


    template<class Key, class T, class Compare, class Allocator>
    bool list_map<Key, T, Compare, Allocator>::push_back(const value_type& value)
    {
        node_type temp(value);
        auto res = mMap.emplace(value.first, temp);
        if (res.second) {
            node_type* pnode = static_cast<node_type*> (&((*res.first).second));

            pnode->Next = &mNode;
            pnode->Prev = mNode.Prev;

            mNode.Prev->Next = pnode;
            mNode.Prev  = pnode;
            return true;
        }
        return false;
    }


    template<class Key, class T, class Compare, class Allocator>
    bool list_map<Key, T, Compare, Allocator>::push_front(const key_type& key, const mapped_type& value)
    {
        return push_front(std::make_pair(key, value));
    }


    template<class Key, class T, class Compare, class Allocator>
    bool list_map<Key, T, Compare, Allocator>::push_back(const key_type& key, const mapped_type& value)
    {
        return push_back(std::make_pair(key, value));
    }


    template<class Key, class T, class Compare, class Allocator>
    void list_map<Key, T, Compare, Allocator>::pop_front()
    {
        if(&mNode == mNode.Next) return;

        node_type* pnode = mNode.Next;
        mNode.Next = pnode->Next;
        pnode->Next->Prev = &mNode;
        auto res = mMap.erase(pnode->value.first);
        assert(res > 0);//TO_REMOVE

    }


    template<class Key, class T, class Compare, class Allocator>
    void list_map<Key, T, Compare, Allocator>::pop_back()
    {
        if(&mNode == mNode.Prev) return;

        node_type* pnode = mNode.Prev;
        mNode.Prev = pnode->Prev;
        pnode->Prev->Next = &mNode;
        auto res = mMap.erase(pnode->value.first);
        assert(res > 0);//TO_REMOVE
    }

    //For Map
    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::iterator
    list_map<Key, T, Compare, Allocator>::find(const key_type& key)
    {
        auto fval = mMap.find(key);
        if(fval != mMap.end())//remember mMap.end() != end()
        {
            return iterator(&((*fval).second));
        }
        return iterator(&mNode);
    }


    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::const_iterator
    list_map<Key, T, Compare, Allocator>::find(const key_type& key) const
    {
        auto fval = mMap.find(key);
        if(fval != mMap.end())
        {
            return const_iterator(&((*fval).second));
        }
        return const_iterator(&mNode);
    }


    template <typename Key, typename T, typename Compare, typename Allocator>
    template <typename U, typename Compare2>
    typename list_map<Key, T, Compare, Allocator>::iterator
    list_map<Key, T, Compare, Allocator>::find_as(const U& u, Compare2 compare2)
    {
        for(auto idx = begin(); idx != end(); ++idx)
            if(compare2((*idx).first, u))
                    return idx;
        return end();
    }

    template <typename Key, typename T, typename Compare, typename Allocator>
    template <typename U, typename Compare2>
    typename list_map<Key, T, Compare, Allocator>::const_iterator
    list_map<Key, T, Compare, Allocator>::find_as(const U& u, Compare2 compare2) const
    {
        for(auto idx = begin(); idx != end(); ++idx)
            if(compare2((*idx).first, u))
                    return const_iterator(idx);
        return const_iterator(end());
    }

    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::size_type
    list_map<Key, T, Compare, Allocator>::count(const key_type& key) const
    {
        return mMap.count(key);
    }

    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::size_type
    list_map<Key, T, Compare, Allocator>::erase(const key_type& key)
    {
        auto fval = mMap.find(key);
        if(fval != mMap.end())
        {
            auto idx = &(*fval).second;
            auto inext = idx->Next;
            auto iprev = idx->Prev;
            inext->Prev= iprev;
            iprev->Next= inext;
            mMap.erase(fval);
            return 1;//element is unique
        }
        return 0;
    }

    //comon of list and map
    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::iterator
    list_map<Key, T, Compare, Allocator>::erase(const_iterator position)
    {
        auto fval = mMap.find((*position).first);
        if(fval != mMap.end())
        {
            auto idx = &(*fval).second;
            auto inext = idx->Next;
            auto iprev = idx->Prev;
            inext->Prev= iprev;
            iprev->Next= inext;
            mMap.erase(fval);
            return inext;//element is unique
        }
        return end();
    }

    template<class Key, class T, class Compare, class Allocator>
    typename list_map<Key, T, Compare, Allocator>::reverse_iterator
    list_map<Key, T, Compare, Allocator>::erase(const_reverse_iterator position)
    {
        return reverse_iterator(erase((++position).base()));
    }

    template<class Key, class T, class Compare, class Allocator>
    void list_map<Key, T, Compare, Allocator>::clear()
    {
        mMap.clear();
        mNode.Next = &mNode;
        mNode.Prev = &mNode;
    }

    template<class Key, class T, class Compare, class Allocator>
    void list_map<Key, T, Compare, Allocator>::reset_lose_memory()
    {
        mMap.clear();
        mNode.Next = &mNode;
        mNode.Prev = &mNode;
    }

    template<class Key, class T, class Compare, class Allocator>
    bool list_map<Key, T, Compare, Allocator>::validate() const
    {
        unsigned int count{0};
        for (auto idx=begin(); idx != end(); ++idx)
            ++count;
        if(mMap.size()!=count) return false;

        auto ibegin = (*mMap.begin()).second.Prev;
        auto iend   = (*mMap.rbegin()).second.Next;
        if((ibegin != &mNode) || (iend != &mNode)) return false;

        for (auto idx=begin(); idx != end(); ++idx)
            if((idx.mpNode->Next->Prev != idx.mpNode)
                    || (idx.mpNode->Prev->Next != idx.mpNode)) return false;
        return true;
    }

    template<class Key, class T, class Compare, class Allocator>
    int list_map<Key, T, Compare, Allocator>::validate_iterator(const_iterator i) const
    {
        for(auto idx = begin(); idx != end(); ++idx)
            if(i==idx)
                return 2;
        if(i==end()) return 1;
        return 0;
    }
}

#endif // KTSTD_LIST_MAP_H

