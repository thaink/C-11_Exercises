/*
 * Vector Implementation
 * author: thaink@capp.snu.ac.kr
 */


#ifndef ESTD_VECTOR_H
#define ESTD_VECTOR_H

#include <memory>

namespace Estd {

    /*
     * Vector implementation. this a simplified version
     */
    //template <class T, class A = std::allocator<T>>
    class vector {
    public:
        using T = int;
        using A = std::allocator<int>;
        using size_type = unsigned int;//type for vector size
        using value_type = T;
        using iterator = T *;
        using const_iterator = const T *;

        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;

        explicit vector(size_type n, const T& val = value_type(), const A& = A());

        vector(const vector& a);
        vector& operator=(const vector& a);
        vector(vector&& a);
        vector& operator=(vector&& a);

        ~vector();

        size_type size() const {return vb.space-vb.elem;}
        size_type capability() {return vb.last-vb.elem;}
        void reserve(size_type n); //reserve spaces for n elements

        void resize(size_type n, const value_type& = {}); // increase size to n
        void push_back(const value_type&); // add element at the end

        iterator begin() {return vb.elem;}
        iterator end(){return vb.space;}
        const_iterator begin() const {return vb.elem;}
        const_iterator end() const {return vb.space;}


    private:
        /*
         * This class are meant to manage the memory of vector
         */
        //template <class T, class A = std::allocator<T>>
        struct vector_base{
            using T = int;
            using A = std::allocator<int>;
            using value_type = T;
            using size_type = unsigned int;
            A alloc;          //allocator
            value_type* elem; //start of allocation
            value_type* space;//end of element sequence, start of space allocated for posible expansion
            value_type* last; //end of allocated space

            vector_base(const A& a, size_type n)
                :alloc{a}, elem{alloc.allocate(n)}, space{elem}, last{elem+n} {}
            ~vector_base(){alloc.deallocate(elem, last-elem);}

            vector_base(const vector_base&) = delete;
            vector_base& operator=(const vector_base&) = delete;
            vector_base(vector_base&&);
            vector_base& operator=(vector_base&&);
        };//vector_base
        vector_base vb;

        void destroy_elements();
    };//vector

}//Estd

#endif // ESTD_VECTOR_H

