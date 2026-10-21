#ifndef __NODE_HPP__
#define __NODE_HPP__

	template<typename Type>
	struct Node
	{
		public:
			Node<Type>* _next;
			Type _value;
			
			Node();
			Node(Node<Type>*, Type);
			Node(Type);
			
			Node<Type>& operator = (const Node<Type>&);
			Node<Type>& operator = (Node<Type>&&);
	};
	
	#include "../source/node.inl"

#endif