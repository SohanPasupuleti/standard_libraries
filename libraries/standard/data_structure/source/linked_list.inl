#ifndef __LINKED_LIST_INL__
#define __LINKED_LIST_INL__

	#include <linked_list.hpp>

	template<typename Type>
	Linked_List<Type>::Linked_List() : _head(nullptr), _size(0U) {}
	
	template<typename Type>
	Linked_List<Type>::Linked_List(const std::initializer_list<Type>& initial_values) : _head(nullptr), _size(0U) 
	{
		if (initial_values.size() == 0U)
		{
			return;
		}
		const Type* iterator = initial_values.begin();
		_size = initial_values.size();
		Node<Type>* tail = nullptr;
		for (size_t index = 0U; index < _size; ++index)
		{
			Node<Type>* new_node = new Node<Type>(iterator[index]);
			if (_head == nullptr)
			{
				_head = new_node;
			}
			else
			{
				tail->_next = new_node;
			}
			tail = new_node;
		}
	}
	
	template<typename Type>
	Linked_List<Type>::Linked_List(const Linked_List<Type>& linked_list) : _head(nullptr), _size(0U) 
	{
		if (linked_list.size() == 0U)
		{
			return;
		}
		_size = linked_list._size;
		Node<Type>* tail = nullptr;
		Node<Type>* current_source = linked_list._head;
		while (current_source != nullptr)
		{
			Node<Type>* new_node = new Node<Type>(current_source->_value);
			if (_head == nullptr)
			{
				_head = new_node;
			}
			else
			{
				tail->_next = new_node;
			}
			tail = new_node;
			current_source = current_source->_next;
		}
	}
	
	template<typename Type>
	Linked_List<Type>::~Linked_List() 
	{
		Node<Type>* current = _head;
		while (current != nullptr)
		{
			Node<Type>* next_node = current->_next;
			delete current;
			current = next_node;
		}
	}
	
	template<typename Type>
	Type Linked_List<Type>::operator [] (size_t index) const
	{
		Node<Type>* current = _head;
		for (size_t current_position = 0U; current_position < index; ++current_position)
		{
			current = current->_next;
		}
		return current->_value;
	}
	
	template<typename Type>
	Type& Linked_List<Type>::operator [] (size_t index) 
	{
		Node<Type>* current = _head;
		for (size_t current_position = 0U; current_position < index; ++current_position)
		{
			current = current->_next;
		}
		return current->_value;
	}
	
	template<typename Type>
	size_t Linked_List<Type>::size() const
	{
		return _size;
	}

#endif