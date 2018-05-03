#ifndef KTSTD_VECTOR_MAP_H
#define KTSTD_VECTOR_MAP_H

namespace ktstd {

    class vector_map {
        //basic types
        using this_type                 = vector_map;
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
    };

}//ktstd

#endif // KTSTD_VECTOR_MAP_H

