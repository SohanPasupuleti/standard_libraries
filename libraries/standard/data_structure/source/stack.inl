#ifndef __STACK_INL__
#define __STACK_INL__

	#include <stack.hpp>

	template<typename Type>
	Stack<Type>::Stack(const Dynamic_Buffer<Type>& initial_buffer) : _buffer(initial_buffer) {}
	
	template<typename Type>
	Stack<Type>::Stack(Dynamic_Buffer<Type>&& initial_buffer) : _buffer(static_cast<Dynamic_Buffer<Type>&&>(initial_buffer)) {}
	
	template<typename Type>
	Stack<Type>::Stack(const std::initializer_list<Type>& initial_values) : _buffer(initial_values) {}
	
	template<typename Type>
	Stack<Type>::Stack(const Stack<Type>& stack)
	{
		if (this == &stack)
		{
			return;
		}
		_buffer = stack._buffer;
	}
	
	template<typename Type>
	Stack<Type>::Stack(Stack<Type>&& stack)
	{
		if (this == &stack)
		{
			return;
		}
		_buffer = static_cast<Dynamic_Buffer<Type>&&>(stack._buffer);
	}
	
	template<typename Type>
	Stack<Type>& Stack<Type>::operator = (const Stack<Type>& stack)
	{
		if (this != &stack)
		{
			_buffer = stack._buffer;
		}
		return *this;
	}
	
	template<typename Type>
	Stack<Type>& Stack<Type>::operator = (Stack<Type>&& stack)
	{
		if (this != &stack)
		{
			_buffer = static_cast<Dynamic_Buffer<Type>&&>(stack._buffer);
		}
		return *this;
	}
	
	template<typename Type>
    Type Stack<Type>::operator [] (size_t index) const
    {
        if (index < 0U || index >= _buffer.size())
        {
            return Type();
        }
        return _buffer[index];
    }
    
    template<typename Type>
    Type& Stack<Type>::operator [] (size_t index)
    {
        return _buffer[index];
    }
	
	template<typename Type>
	Type Stack<Type>::peek() const
	{
		return _buffer[_buffer.size() - 1];
	}
	
	template<typename Type>
	void Stack<Type>::push(const Type& value)
	{
		_buffer.insert(value, _buffer.size());
	}
	
	template<typename Type>
	void Stack<Type>::push(Type&& value)
	{
		_buffer.insert(static_cast<Type&&>(value), _buffer.size());
	}
	
	template<typename Type>
	void Stack<Type>::pop()
	{
		_buffer.remove(_buffer.size() - 1);
	}
	
	template<typename Type>
	size_t Stack<Type>::size() const
	{
		return _buffer.size();
	}
	
	
#endif