#ifndef __DYNAMIC_BUFFER_HPP__
#define __DYNAMIC_BUFFER_HPP__

    #include <stddef.h>
    #include <initializer_list>
	#include <capacity_mode.hpp>
    
    template<typename Type>
    struct Dynamic_Buffer
    {
        public:
            Dynamic_Buffer();
			Dynamic_Buffer(size_t, size_t);
            Dynamic_Buffer(size_t, size_t, Capacity_Mode);
			Dynamic_Buffer(const Type*, size_t, size_t);
            Dynamic_Buffer(const Type*, size_t, size_t, Capacity_Mode);
            Dynamic_Buffer(const std::initializer_list<Type>&, Capacity_Mode);
			Dynamic_Buffer(const std::initializer_list<Type>&);
            Dynamic_Buffer(const Dynamic_Buffer<Type>&);
            Dynamic_Buffer(Dynamic_Buffer<Type>&&);
            ~Dynamic_Buffer();
            
            Dynamic_Buffer<Type>& operator = (const Dynamic_Buffer<Type>&);
            Dynamic_Buffer<Type>& operator = (Dynamic_Buffer<Type>&&);
            Type operator [] (size_t) const;
            Type& operator [] (size_t);
            Dynamic_Buffer<Type> operator () (size_t, size_t) const;
            
            const Type* const values() const;
            void set_values(const Type*, size_t);
			Type* data();
            size_t capacity() const;
            void set_capacity(size_t);
            size_t size() const;
            void set_size(size_t);
            Capacity_Mode capacity_mode() const;
            void set_capacity_mode(Capacity_Mode);
            
            void increase_capacity();
            void insert(const Type&, size_t);
            void insert(Type&&, size_t);
            void remove(size_t);
            void shift_right(size_t);
            void shift_right(size_t, size_t, size_t);
            void shift_left(size_t);
            void shift_left(size_t, size_t, size_t);
            void reverse();
            void reverse(size_t, size_t);
            void sort();
            void sort(size_t, size_t);
            void clear();
            void clear(size_t, size_t);
            size_t find(const Type&) const;
            size_t count(const Type&) const;
            bool empty() const;
            
        private:
            Type* _values;
            size_t _capacity;
            size_t _size;
            Capacity_Mode _capacity_mode;
    };
    
    #include "../source/dynamic_buffer.inl"

#endif