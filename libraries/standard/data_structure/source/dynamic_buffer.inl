#ifndef __DYNAMIC_BUFFER_INL__
#define __DYNAMIC_BUFFER_INL__

    #include <dynamic_buffer.hpp>
    
	#define __DEFAULT_DYNAMIC_BUFFER_CAPACITY_MODE__ Capacity_Mode::MULTIPLY
    #define __DEFAULT_DYNAMIC_BUFFER_INITIAL_CAPACITY__ 5U
    #define __DYNAMIC_BUFFER_LINEAR_CONSTANT__ 5U
    #define __DYNAMIC_BUFFER_MULTIPLY_CONSTANT__ 2U
    #define __DYNAMIC_BUFFER_THRESHHOLD_VALUE__ 25U
    
    template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer()
    {
        _capacity_mode = __DEFAULT_DYNAMIC_BUFFER_CAPACITY_MODE__;
        _capacity = __DEFAULT_DYNAMIC_BUFFER_INITIAL_CAPACITY__;
        _size = 0U;
        _values = new Type[_capacity];
    }
    
	template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(size_t initial_capacity, size_t initial_size)
    {
        _capacity_mode = __DEFAULT_DYNAMIC_BUFFER_CAPACITY_MODE__;
        _capacity = initial_capacity;
        _size = initial_size;
        _values = new Type[_capacity];
    }
	
    template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(size_t initial_capacity, size_t initial_size, Capacity_Mode initial_capacity_mode)
    {
        _capacity_mode = initial_capacity_mode;
        _capacity = initial_capacity;
        _size = initial_size;
        _values = new Type[_capacity];
    }
	
	template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(const Type* initial_values, size_t initial_capacity, size_t initial_size)
    {
        _capacity_mode = __DEFAULT_DYNAMIC_BUFFER_CAPACITY_MODE__;
        _capacity = initial_capacity;
        _size = initial_size;
        _values = new Type[_capacity];
        for (size_t index = 0U; index < _size; ++index)
        {
            _values[index] = initial_values[index];
        }
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(const Type* initial_values, size_t initial_capacity, size_t initial_size, Capacity_Mode initial_capacity_mode)
    {
        _capacity_mode = initial_capacity_mode;
        _capacity = initial_capacity;
        _size = initial_size;
        _values = new Type[_capacity];
        for (size_t index = 0U; index < _size; ++index)
        {
            _values[index] = initial_values[index];
        }
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(const std::initializer_list<Type>& initial_values, Capacity_Mode initial_capacity_mode)
    {
        _capacity_mode = initial_capacity_mode;
        _capacity = initial_values.size();
        _size = _capacity;
        _values = new Type[_capacity];
        size_t index = 0U;
        for (const Type& element : initial_values)
        {
            _values[index] = element;
            ++index;
        }
    }
	
	template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(const std::initializer_list<Type>& initial_values)
    {
        _capacity_mode = Capacity_Mode::MULTIPLY;
        _capacity = initial_values.size();
        _size = _capacity;
        _values = new Type[_capacity];
        size_t index = 0U;
        for (const Type& element : initial_values)
        {
            _values[index] = element;
            ++index;
        }
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(const Dynamic_Buffer<Type>& Dynamic_Buffer)
    {
        if (this == &Dynamic_Buffer)
        {
            return;
        }
        _capacity_mode = Dynamic_Buffer._capacity_mode;
        _capacity = Dynamic_Buffer._capacity;
        _size = Dynamic_Buffer._size;
        _values = new Type[_capacity];
        for (size_t index = 0U; index < _size; ++index)
        {
            _values[index] = Dynamic_Buffer._values[index];
        }
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>::Dynamic_Buffer(Dynamic_Buffer<Type>&& dynamic_buffer)
    {
        if (this == &dynamic_buffer)
        {
            return;
        }
        _capacity_mode = dynamic_buffer._capacity_mode;
        _capacity = dynamic_buffer._capacity;
        _size = dynamic_buffer._size;
        _values = dynamic_buffer._values;
        dynamic_buffer._values = nullptr;
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>::~Dynamic_Buffer()
    {
        delete [] _values;
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>& Dynamic_Buffer<Type>::operator = (const Dynamic_Buffer<Type>& new_Dynamic_Buffer)
    {
        if (this == &new_Dynamic_Buffer)
        {
            return *this;
        }
        _capacity_mode = new_Dynamic_Buffer._capacity_mode;
        _capacity = new_Dynamic_Buffer._capacity;
        _size = new_Dynamic_Buffer._size;
        _values = new Type[_capacity];
        for (size_t index = 0U; index < _size; ++index)
        {
            _values[index] = new_Dynamic_Buffer._values[index];
        }
        return *this;
    }
    
    template<typename Type>
    Dynamic_Buffer<Type>& Dynamic_Buffer<Type>::operator = (Dynamic_Buffer<Type>&& new_Dynamic_Buffer)
    {
        if (this == &new_Dynamic_Buffer)
        {
            return *this;
        }
        _capacity_mode = new_Dynamic_Buffer._capacity_mode;
        _capacity = new_Dynamic_Buffer._capacity;
        _size = new_Dynamic_Buffer._size;
        _values = new_Dynamic_Buffer._values;
        new_Dynamic_Buffer._values = nullptr;
        return *this;
    }
    
    template<typename Type>
    Type Dynamic_Buffer<Type>::operator [] (size_t index) const
    {
        return _values[index];
    }
    
    template<typename Type>
    Type& Dynamic_Buffer<Type>::operator [] (size_t index)
    {
        return _values[index];
    }

    template<typename Type>
    Dynamic_Buffer<Type> Dynamic_Buffer<Type>::operator () (size_t start_index, size_t end_index) const
    {
        if (start_index > _size || end_index > _size)
        {
            return Dynamic_Buffer<Type>();
        }
        size_t sub_list_size = end_index - start_index + 1U;
        Dynamic_Buffer<Type> sub_list(sub_list_size, sub_list_size, _capacity_mode);
        for (size_t index = start_index; index <= end_index; ++index)
        {
            sub_list[index - start_index] = _values[index];
        }
        return sub_list;
    }
    
    template<typename Type>
    const Type* const Dynamic_Buffer<Type>::values() const
    {
        return _values;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::set_values(const Type* new_values, size_t new_size)
    {
        for (size_t index = 0U; index < _capacity && index < new_size; ++index)
        {
            _values[index] = new_values[index];
        }
    }
	
	template<typename Type>
    Type* Dynamic_Buffer<Type>::data()
    {
        return _values;
    }
    
    template<typename Type>
    size_t Dynamic_Buffer<Type>::capacity() const
    {
        return _capacity;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::set_capacity(size_t new_capacity)
    {
        if (_capacity == new_capacity)
        {
            return;
        }
        if (new_capacity == 0U)
        {
            _capacity = 0U;
            _size = 0U;
            delete _values;
            _values = nullptr;
        }
        _capacity = new_capacity;
        if (_size > _capacity)
        {
            _size = _capacity;
        }
        Type* previous_values = _values;
        _values = new Type[_capacity];
        for (size_t index = 0U; index < _size; ++index)
        {
            _values[index] = previous_values[index];
        }
        delete previous_values;
    }
    
    template<typename Type>
    size_t Dynamic_Buffer<Type>::size() const
    {
        return _size;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::set_size(size_t new_size)
    {
        if (new_size < _capacity)
        {
            _size = new_size;
        }
    }
    
    template<typename Type>
    Capacity_Mode Dynamic_Buffer<Type>::capacity_mode() const
    {
        return _capacity_mode;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::set_capacity_mode(Capacity_Mode new_capacity_mode)
    {
        _capacity_mode = new_capacity_mode;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::increase_capacity()
    {
        switch (_capacity_mode)
        {
            case Capacity_Mode::STATIC:
                break;
                
            case Capacity_Mode::LINEAR:
                this->set_capacity(_capacity + __DYNAMIC_BUFFER_LINEAR_CONSTANT__);
                break;
                
            case Capacity_Mode::MULTIPLY:
                this->set_capacity(_capacity * __DYNAMIC_BUFFER_MULTIPLY_CONSTANT__);
                break;
                
            case Capacity_Mode::QUADRATIC:
                this->set_capacity(_capacity + _capacity);
                break;
        }
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::insert(const Type& element, size_t index)
    {
        if (index > _size)
        {
            return;
        }
        while (_size + 1U > _capacity)
        {
            this->increase_capacity();
        }
        shift_right(index, _size, 1U);
        _values[index] = element;
        ++_size;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::insert(Type&& element, size_t index)
    {
        if (index > _size)
        {
            return;
        }
        while (_size + 1U > _capacity)
        {
            this->increase_capacity();
        }
        shift_right(index, _size, 1U);
        _values[index] = static_cast<Type&&>(element);
        ++_size;
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::remove(size_t index)
    {
        if (index >= _size)
        {
            return;
        }
        --_size;
        shift_left(index + 1U, _size, 1U);
        if (_capacity - _size >= __DYNAMIC_BUFFER_THRESHHOLD_VALUE__)
        {
            this->set_capacity(_size);
        }
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::shift_right(size_t offset)
    {
        this->shift_right(0U, _size - 1U, offset);
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::shift_right(size_t offset, size_t start_index, size_t end_index)
    {
        if (start_index > end_index)
        {
            return;
        }
        for (int index = (int)end_index; index >= (int)start_index; --index)
        {
            if (index + offset < _capacity)
            {
                _values[index + offset] = _values[index];
            }
        }
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::shift_left(size_t offset)
    {
        this->shift_left(0U, _size - 1U, offset);
    }
    
    template<typename Type>
    void Dynamic_Buffer<Type>::shift_left(size_t offset, size_t start_index, size_t end_index)
    {
        if (start_index > end_index)
        {
            return;
        }
        for (int index = (int)start_index; index <= (int)end_index; ++index)
        {
            if ((index - offset >= 0) && (index - offset < _capacity))
            {
                _values[index - offset] = _values[index];
            }
        }
    }
    
#endif