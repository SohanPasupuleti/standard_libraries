#ifndef __ARRAY_INL__
#define __ARRAY_INL__

	#include <array.hpp>
	
	template<typename Type, size_t Capacity>
	Array<Type, Capacity>::Array(const Type* initial_values, size_t length) : _buffer(initial_values, length) {}
	
	template<typename Type, size_t Capacity>
	Array<Type, Capacity>::Array(const std::initializer_list<Type>& initial_values) : _buffer(initial_values) {}
	
	template<typename Type, size_t Capacity>
	Array<Type, Capacity>::Array(const Array<Type, Capacity>& array)
	{
		if (this == &array)
        {
            return;
        }
		_buffer = array._buffer;
	}
	
	template<typename Type, size_t Capacity>
	Array<Type, Capacity>::Array(Array<Type, Capacity>&& array)
	{
		if (this == &array)
        {
            return;
        }
		_buffer = static_cast<Static_Buffer<Type, Capacity>&&>(array._buffer);
	}
	
	template<typename Type, size_t Capacity>
	Array<Type, Capacity>& Array<Type, Capacity>::operator = (const Array<Type, Capacity>& array)
	{
		if (this != &array)
		{
			_buffer = array._buffer;
		}
		return *this;
	}
	
	template<typename Type, size_t Capacity>
	Array<Type, Capacity>& Array<Type, Capacity>::operator = (Array<Type, Capacity>&& array)
	{
		if (this != &array)
		{
			_buffer = static_cast<Static_Buffer<Type, Capacity>&&>(array._buffer);
		}
		return *this;
	}
	
	template<typename Type, size_t Capacity>
	Type Array<Type, Capacity>::operator [] (size_t index) const
	{
		return _buffer[index];
	}
	
	template<typename Type, size_t Capacity>
	Type& Array<Type, Capacity>::operator [] (size_t index)
	{
		return _buffer[index];
	}
	
	template<typename Type, size_t Capacity>
	const Type* Array<Type, Capacity>::values() const
	{
		return _buffer.values();
	}
	
	template<typename Type, size_t Capacity>
    void Array<Type, Capacity>::set_values(const Type* values, size_t length)
	{
		_buffer.set_values(values, length);
	}
	
	template<typename Type, size_t Capacity>
    Type* Array<Type, Capacity>::data()
	{
		return _buffer.data();
	}
	
	template<typename Type, size_t Capacity>
	size_t Array<Type, Capacity>::size() const
	{
		return Capacity;
	}

#endif