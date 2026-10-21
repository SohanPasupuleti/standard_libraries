#ifndef __QUEUE_INL__
#define __QUEUE_INL__

	#include <queue.hpp>

	template<typename Type>
	Queue<Type>::Queue(const Dynamic_Buffer<Type>& initial_buffer) : _buffer(initial_buffer) {}
	
	template<typename Type>
	Queue<Type>::Queue(Dynamic_Buffer<Type>&& initial_buffer) : _buffer(static_cast<Dynamic_Buffer<Type>&&>(initial_buffer)) {}
	
	template<typename Type>
	Queue<Type>::Queue(const std::initializer_list<Type>& initial_values) : _buffer(initial_values) {}
	
	template<typename Type>
	Queue<Type>::Queue(const Queue<Type>& queue)
	{
		if (this == &queue)
		{
			return;
		}
		_buffer = queue._buffer;
	}
	
	template<typename Type>
	Queue<Type>::Queue(Queue<Type>&& queue)
	{
		if (this == &queue)
		{
			return;
		}
		_buffer = static_cast<Dynamic_Buffer<Type>&&>(queue._buffer);
	}
	
	template<typename Type>
	Queue<Type>& Queue<Type>::operator = (const Queue<Type>& queue)
	{
		if (this != &queue)
		{
			_buffer = queue._buffer;
		}
		return *this;
	}
	
	template<typename Type>
	Queue<Type>& Queue<Type>::operator = (Queue<Type>&& queue)
	{
		if (this != &queue)
		{
			_buffer = static_cast<Dynamic_Buffer<Type>&&>(queue._buffer);
		}
		return *this;
	}
	
	template<typename Type>
    Type Queue<Type>::operator [] (size_t index) const
    {
        if (index < 0U || index >= _buffer.size())
        {
            return Type();
        }
        return _buffer[index];
    }
    
    template<typename Type>
    Type& Queue<Type>::operator [] (size_t index)
    {
        return _buffer[index];
    }
	
	template<typename Type>
	Type Queue<Type>::peek_front() const
	{
		return _buffer[0];
	}
	
	template<typename Type>
	Type Queue<Type>::peek_back() const
	{
		return _buffer[_buffer.size() - 1];
	}
	
	template<typename Type>
	void Queue<Type>::enqueue(const Type& value)
	{
		_buffer.insert(value, 0);
	}
	
	template<typename Type>
	void Queue<Type>::enqueue(Type&& value)
	{
		_buffer.insert(static_cast<Type&&>(value), 0);
	}
	
	template<typename Type>
	void Queue<Type>::dequeue()
	{
		_buffer.remove(_buffer.size() - 1);
	}
	
	template<typename Type>
	size_t Queue<Type>::size() const
	{
		return _buffer.size();
	}
	
	
#endif