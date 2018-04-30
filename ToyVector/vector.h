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
    template <class T, class A = std::allocator<T>>
    class vector {
    public:
        //using T = int;
        //using A = std::allocator<int>;
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
        struct vector_base {
            A alloc;          //allocator
            value_type* elem; //start of allocation
            value_type* space;//end of element sequence, start of space allocated for posible expansion
            value_type* last; //end of allocated space

            vector_base(const A& a, size_type n)
            :alloc{a}, elem{alloc.allocate(n)}, space{elem}, last{elem+n}{ }
            ~vector_base(){alloc.deallocate(elem, last-elem);}

            vector_base(const vector_base&) = delete;
            vector_base& operator=(const vector_base&) = delete;
            vector_base(vector_base&&);
            vector_base& operator=(vector_base&&);
        };//vector_base


        /*
         * representation of the vector and private methods
         */
        vector_base vb;

        void destroy_elements();
    };//vector


    using std::allocator;
    using std::swap;
    /*
     * implementation of vector_base
     */
    template<class T, class A>
    vector<T,A>::vector_base::vector_base(vector_base&& a)
    //vector::vector_base::vector_base(vector_base&& a)
        : alloc(a.alloc),
          elem(a.elem),
          space(a.space),
          last(a.last)
    {
        a.elem = a.space = a.last = nullptr;
    }

    template<class T, class A>
    typename vector<T,A>::vector_base& vector<T,A>::vector_base::operator=(vector_base&& a)
    //vector::vector_base& vector::vector_base::operator=(vector_base&& a)
    {
        swap(alloc, a.alloc);
        swap(elem, a.elem);
        swap(space,a.space);
        swap(last, a.last);
        return *this;
    }


    /*
     * implementation of vector
     */
    template <class T, class A>
    vector<T,A>::vector(size_type n, const value_type& val, const A& talloc)
    //vector::vector(size_type n, const value_type& val, const A& talloc)
        :vb(talloc,n)
    {
        std::uninitialized_fill(vb.elem, vb.elem+n, val);
        vb.space = vb.space+n;
    }

    template <class T, class A>
    void vector<T,A>::destroy_elements()
    //void vector::destroy_elements()
    {
        for (T* p = vb.elem; p!=vb.space; ++p)
            p->~T();
        vb.space = vb.elem;
    }

    template <class T, class A>
    vector<T,A>::~vector()
    //vector::~vector()
    {
        destroy_elements();
    }

    template <class T, class A>
    vector<T,A>::vector(const vector<T,A>& a)
    //vector::vector(const vector& a)
        :vb{a.vb.alloc, a.size()}
    {
        std::uninitialized_copy(a.begin(), a.end(), vb.elem);
        vb.space = vb.space+a.size();
    }

    template <class T, class A>
    vector<T,A>& vector<T,A>::operator=(const vector<T,A>& a)
    //vector& vector::operator=(const vector& a)
    {
        if (capability() < a.size()) { //allocate new vector representation
            vector temp{a};
            std::swap(*this, temp);
            return *this;
        }

        if (this == &a) return *this;

        size_type sz=size();
        size_type asz=a.size();
        vb.alloc = a.vb.alloc;
        if(asz<=sz) {
            std::copy(a.begin(), a.end(), vb.elem);
            for (T* p=vb.elem+asz; p<vb.space;++p)
                p->~T();
        } else {
            std::copy(a.begin(), a.end(), vb.elem);
            std::uninitialized_copy(a.begin()+sz, a.end(), vb.space);
        }
        vb.space = vb.elem + asz;
        return *this;
    }

    template <class T, class A>
    vector<T,A>::vector(vector<T,A>&& a)
    //vector::vector(vector&& a)
        :vb{std::move(a.vb)}
    {
    }

    template <class T, class A>
    vector<T,A>& vector<T,A>::operator=(vector<T,A>&& a)
    //vector& vector::operator=(vector&& a)
    {
        //this->destroy_elements(); //redundance. assme rvalue being destroyed immediately
        std::swap(vb, a.vb); //swap work because we define move assignment for sub-class
        return *this;
    }


    template<typename It1, typename It2>
    static void uninitialized_move(It1 I, It1 E, It2 Dest) {
        std::uninitialized_copy(std::make_move_iterator(I),
                                std::make_move_iterator(E), Dest);
    }

    template <class T, class A>
    void vector<T,A>::reserve(size_type newalloc)
    //void vector::reserve(size_type newalloc)
    {
        if(newalloc <= capability()) return;
        vector_base b(vb.alloc, newalloc);
        uninitialized_move(vb.elem, vb.space, b.elem);
        b.space = b.elem + size();
        swap(vb,b);
    }// implicitly release old value


    template <class T, class A>
    void vector<T,A>::push_back(const value_type& val)
    //void vector::push_back(const value_type& val)
    {
        if(capability()==size())
            reserve(size()?2*size():8);
        vb.alloc.construct(vb.space, val);
        ++vb.space;
    }

}//Estd

#endif // ESTD_VECTOR_H

