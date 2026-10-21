#ifndef __STACK_HPP__
#define __STACK_HPP__

    #include <stddef.h>
    #include <initializer_list>
    #include "dynamic_buffer.hpp"

    template<typename Type>
    struct Stack
    {
        public:
            Stack() = default;
            Stack(const Dynamic_Buffer<Type>&);
            Stack(Dynamic_Buffer<Type>&&);
            Stack(const std::initializer_list<Type>&);
            Stack(const Stack<Type>&);
            Stack(Stack<Type>&&);
            ~Stack() = default;

			Stack<Type>& operator = (const Stack<Type>&);
			Stack<Type>& operator = (Stack<Type>&&);
			Type operator [] (size_t) const;
			Type& operator [] (size_t);
			
			Type peek() const;
			void push(const Type&);
			void push(Type&&);
			void pop();
			size_t size() const;

        private:
            Dynamic_Buffer<Type> _buffer;
    };
	
	#include "../source/stack.inl"

#endif

