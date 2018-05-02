#ifndef KTSTD_LIST_MAP_H
#define KTSTD_LIST_MAP_H

#include <cstddef>
#include <iterator>

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

    class list_map_node {

    };

    template <typename T, typename Pointer, typename Reference>
    struct list_map_iterator
    {
        typedef list_map_iterator<T, Pointer, Reference>    this_type;
        typedef list_map_iterator<T, T*, T&>                iterator;
        typedef list_map_iterator<T, const T*, const T&>    const_iterator;
        typedef std::size_t                                 size_type;     // See config.h for the definition of eastl_size_t, which defaults to uint32_t.
        typedef std::ptrdiff_t                              difference_type;
        typedef T                                           value_type;
        typedef list_map_node                               node_type;
        typedef Pointer                                     pointer;
        typedef Reference                                   reference;
        typedef std::bidirectional_iterator_tag             iterator_category;

    public:
        node_type* mpNode;

    public:
        list_map_iterator();
        list_map_iterator(const base_node_type* pNode);
        list_map_iterator(const iterator& x);

        reference operator*() const;
        pointer   operator->() const;

        this_type& operator++();
        this_type  operator++(int);

        this_type& operator--();
        this_type  operator--(int);

    };

//    template<class Key, class T,
//        class Compare = std::less<Key>,
//        class Allocator = std::allocator<std::pair<const Key, T>>>
    class list_map {
        using Key           =   std::string;
        using T             =   std::string;
        using Compare       =   std::less<Key>;
        using Allocator     =   std::allocator<std::pair<const Key, T>>;

    public:
        //basic types
        typedef list_map                            this_type;
        typedef unsigned int                        size_type;
        typedef Key                                 key_type;
        typedef T                                   mapped_type;
        typedef typename std::pair<const Key, T>    value_type;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef list_map_node                       node_type;
        //iterator types

    protected:
        //internal data
        list_map_node mNode;
        std::map<Key,T,Compare,Allocator> mMap;

    public:
        list_map(const Allocator& allocator = Allocator());
        list_map(const Compare& compare, const Allocator& allocator = Allocator());

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


}

#endif // KTSTD_LIST_MAP_H

