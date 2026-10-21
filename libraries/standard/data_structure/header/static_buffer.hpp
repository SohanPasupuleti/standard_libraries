#ifndef __STATIC_BUFFER_HPP__
#define __STATIC_BUFFER_HPP__

    #include <stddef.h>
    #include <initializer_list>
    
    template<typename Type, size_t Capacity>
    struct Static_Buffer
    {
        public:
            Static_Buffer();
            Static_Buffer(const Type*, size_t);
            Static_Buffer(const std::initializer_list<Type>&);
            Static_Buffer(const Static_Buffer<Type, Capacity>&);
            Static_Buffer(Static_Buffer<Type, Capacity>&&);
            
            Static_Buffer<Type, Capacity>& operator = (const Static_Buffer<Type, Capacity>&);
            Static_Buffer<Type, Capacity>& operator = (Static_Buffer<Type, Capacity>&&);
            Type operator [] (size_t) const;
            Type& operator [] (size_t);
            
            const Type* values() const;
            void set_values(const Type*, size_t);
			Type* data();
        
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
            Type _values[Capacity];
    };
    
    #include "../source/static_buffer.inl"

#endif