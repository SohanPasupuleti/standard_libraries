#ifndef __ARRAY_LIST_HPP__
#define __ARRAY_LIST_HPP__

	#include <dynamic_buffer.hpp>

	template<typename Type>
    struct Array_List
	{
		public:
			Array_List() = default;
            Array_List(const Type* initial_values, size_t length);
            Array_List(const std::initializer_list<Type>& initial_values);
            Array_List(const Array_List<Type>& array_list);
            Array_List(Array_List<Type>&& array_list);
			~Array_List() = default;
			
			Array_List<Type>& operator = (const Array_List<Type>& array_list);
            Array_List<Type>& operator = (Array_List<Type>&& array_list);
			Type operator [] (size_t index) const;
            Type& operator [] (size_t index);
			
			const Type* values() const;
            void set_values(const Type* values, size_t length);
			Type* data();
			size_t size() const;
			
			void increase_capacity();
            void insert(const Type& value, size_t length);
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
			Dynamic_Buffer<Type> _buffer;
	};

	#include "../source/array_list.inl"

#endif