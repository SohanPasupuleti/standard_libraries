#ifndef __ARRAY_LIST_INL__
#define __ARRAY_LIST_INL__

	#include <array_list.hpp>
	
	template<typename Type>
	Array_List<Type>::Array_List(const Type* initial_values, size_t length) : _buffer(initial_values, length, length) {}
	
	template<typename Type>
	Array_List<Type>::Array_List(const std::initializer_list<Type>& initial_values) : _buffer(initial_values) {}
	
	template<typename Type>
	Array_List<Type>::Array_List(const Array_List<Type>& array_list)
	{
		if (this == &array_list)
        {
            return;
        }
		_buffer = array_list._buffer;
	}
	
	template<typename Type>
	Array_List<Type>::Array_List(Array_List<Type>&& array_list)
	{
		if (this == &array_list)
        {
            return;
        }
		_buffer = static_cast<Dynamic_Buffer<Type>&&>(array_list._buffer);
	}
	
	template<typename Type>
	Array_List<Type>& Array_List<Type>::operator = (const Array_List<Type>& array_list)
	{
		if (this != &array_list)
		{
			_buffer = array_list._buffer;
		}
		return *this;
	}
	
	template<typename Type>
	Array_List<Type>& Array_List<Type>::operator = (Array_List<Type>&& array_list)
	{
		if (this != &array_list)
		{
			_buffer = static_cast<Dynamic_Buffer<Type>&&>(array_list._buffer);
		}
		return *this;
	}
	
	template<typename Type>
	Type Array_List<Type>::operator [] (size_t index) const
	{
		return _buffer[index];
	}
	
	template<typename Type>
	Type& Array_List<Type>::operator [] (size_t index)
	{
		return _buffer[index];
	}
	
	template<typename Type>
	const Type* Array_List<Type>::values() const
	{
		return _buffer.values();
	}
	
	template<typename Type>
    void Array_List<Type>::set_values(const Type* values, size_t length)
	{
		_buffer.set_values(values, length);
	}
	
	template<typename Type>
    Type* Array_List<Type>::data()
	{
		return _buffer.data();
	}

	template<typename Type>
	size_t Array_List<Type>::size() const
	{
		return _buffer.size();
	}
	
#endif