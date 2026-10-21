#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

    #include <stddef.h>
    #include <initializer_list>
    #include "dynamic_buffer.hpp"

    template<typename Type>
    struct Queue
    {
        public:
            Queue() = default;
            Queue(const Dynamic_Buffer<Type>&);
            Queue(Dynamic_Buffer<Type>&&);
            Queue(const std::initializer_list<Type>&);
            Queue(const Queue<Type>&);
            Queue(Queue<Type>&&);
            ~Queue() = default;

			Queue<Type>& operator = (const Queue<Type>&);
			Queue<Type>& operator = (Queue<Type>&&);
			Type operator [] (size_t) const;
			Type& operator [] (size_t);
			
			Type peek_front() const;
			Type peek_back() const;
			void enqueue(const Type&);
			void enqueue(Type&&);
			void dequeue();
			size_t size() const;

        private:
            Dynamic_Buffer<Type> _buffer;
    };
	
	#include "../source/queue.inl"

#endif

