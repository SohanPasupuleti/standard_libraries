#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

	#include "static_buffer.hpp"

    template<typename Type, size_t Capacity>
    struct Array
    {
        public:
			Array() = default;
            Array(const Type* initial_values, size_t length);
            Array(const std::initializer_list<Type>& initial_values);
            Array(const Array<Type, Capacity>& array);
            Array(Array<Type, Capacity>&& array);
			~Array() = default;
			
			Array<Type, Capacity>& operator = (const Array<Type, Capacity>& array);
            Array<Type, Capacity>& operator = (Array<Type, Capacity>&& array);
			Type operator [] (size_t index) const;
            Type& operator [] (size_t index);
			
			const Type* values() const;
            void set_values(const Type* values, size_t length);
			Type* data();
			size_t size() const;
			
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
			Static_Buffer<Type, Capacity> _buffer;
	};
	
	#include "../source/array.inl"
	
#endif