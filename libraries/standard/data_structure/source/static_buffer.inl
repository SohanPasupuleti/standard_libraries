#ifndef __STATIC_BUFFER_INL__
#define __STATIC_BUFFER_INL__

    #include <static_buffer.hpp>
    
	template<typename Type, size_t Capacity>
    Static_Buffer<Type, Capacity>::Static_Buffer()
    {
        for (size_t index = 0U; index < Capacity; ++index)
        {
            _values[index] = Type();
        }
    }
	
    template<typename Type, size_t Capacity>
    Static_Buffer<Type, Capacity>::Static_Buffer(const Type* initial_values, size_t length)
    {
        for (size_t index = 0U; index < Capacity && index < length; ++index)
        {
            _values[index] = initial_values[index];
        }
    }
    
    template<typename Type, size_t Capacity>
    Static_Buffer<Type, Capacity>::Static_Buffer(const std::initializer_list<Type>& initial_values)
    {
        size_t index = 0U;
        for (const Type& element : initial_values)
        {
			if (index >= Capacity)
			{
				break;
			}
            _values[index] = element;
            ++index;
        }
    }
    
    template<typename Type, size_t Capacity>
    Static_Buffer<Type, Capacity>::Static_Buffer(const Static_Buffer<Type, Capacity>& buffer)
    {
        if (this == &buffer)
        {
            return;
        }
        for (size_t index = 0U; index < Capacity; ++index)
        {
            _values[index] = buffer._values[index];
        }
    }
    
    template<typename Type, size_t Capacity>
    Static_Buffer<Type, Capacity>::Static_Buffer(Static_Buffer<Type, Capacity>&& buffer)
    {
        if (this == &buffer)
        {
            return;
        }
        for (size_t index = 0U; index < Capacity; ++index)
        {
            _values[index] = static_cast<Type&&>(buffer._values[index]);
        }
    }

	template<typename Type, size_t Capacity>
	Static_Buffer<Type, Capacity>& Static_Buffer<Type, Capacity>::operator = (const Static_Buffer<Type, Capacity>& buffer)
	{
		if (this == &buffer)
        {
            return *this;
        }
        for (size_t index = 0U; index < Capacity; ++index)
        {
            _values[index] = buffer._values[index];
        }
		return *this;
	}
	
    template<typename Type, size_t Capacity>
	Static_Buffer<Type, Capacity>& Static_Buffer<Type, Capacity>::operator = (Static_Buffer<Type, Capacity>&& buffer)
	{
		if (this == &buffer)
        {
            return *this;
        }
        for (size_t index = 0U; index < Capacity; ++index)
        {
            _values[index] = static_cast<Type&&>(buffer._values[index]);
        }
		return *this;
	}
	
	template<typename Type, size_t Capacity>
	Type Static_Buffer<Type, Capacity>::operator [] (size_t index) const
	{
		return _values[index];
	}
	
	template<typename Type, size_t Capacity>
	Type& Static_Buffer<Type, Capacity>::operator [] (size_t index)
	{
		return _values[index];
	}
	
	template<typename Type, size_t Capacity>
	const Type* Static_Buffer<Type, Capacity>::values() const
	{
		return &_values[0];
	}
	
	template<typename Type, size_t Capacity>
	void Static_Buffer<Type, Capacity>::set_values(const Type* values, size_t length)
	{
		for (size_t index = 0U; index < Capacity && index < length; ++index)
		{
			_values[index] = values[index];
		}
	}
	
	template<typename Type, size_t Capacity>
	Type* Static_Buffer<Type, Capacity>::data()
	{
		return &_values[0];
	}
	
#endif
