#ifndef GRAPH_HPP
#define GRAPH_HPP

	#include <stddef.h>
	#include "dynamic_buffer.hpp"
	
	template <typename Type>
	struct Graph
	{
		public:
			Graph();
			
		private:
			Dynamic_Buffer<Dynamic_Buffer<size_t>> _adjacency_list;
			Dynamic_Buffer<Type> _values;
	};

#endif