#ifndef __NODE_INL__
#define __NODE_INL__

	#include <node.hpp>
	
	template<typename Type>
	Node<Type>::Node() : _next(nullptr), _value() {}
	
	template<typename Type>
	Node<Type>::Node(Node<Type>* next, Type value) : _next(next), _value(value) {}
	
	template<typename Type>
	Node<Type>::Node(Type value) : _next(nullptr), _value(value) {}
	
	template<typename Type>
	Node<Type>& Node<Type>::operator = (const Node<Type>& node) 
	{
		if (this != &node) 
		{
			_value = node._value;
			_next = node._next;
		}
		return *this;
	}

	template<typename Type>
	Node<Type>& Node<Type>::operator = (Node<Type>&& node) 
	{
		if (this != &node) 
		{
			_value = static_cast<Type&&>(node._value);
			_next = node._next;
			node._next = nullptr;
		}
		return *this;
	}

#endif