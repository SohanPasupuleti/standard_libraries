#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

	#include <stddef.h>
    #include <initializer_list>
	#include <node.hpp>
	
	template<typename Type>
	struct Linked_List
	{
		public:
			Linked_List();
			Linked_List(const std::initializer_list<Type>&);
			Linked_List(const Linked_List<Type>&);
			Linked_List(Linked_List<Type>&&);
			~Linked_List();
			
			Linked_List<Type>& operator = (const Linked_List<Type>&);
			Linked_List<Type>& operator = (Linked_List<Type>&&);
			Type operator [] (size_t) const;
			Type& operator [] (size_t);
			
			size_t size() const;
			
			void insert(const Type&, size_t);
			void append(const Type&);
			void remove(size_t);
			void find(const Type&);
			void count(const Type&);
			
			
		private:
			Node<Type>* _head;
			size_t _size;
	};
	
	#include "../source/linked_list.inl"

#endif