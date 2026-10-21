#ifndef __MAP_HPP__
#define __MAP_HPP__

    #include <stddef.h>
    #include <initializer_list>
    #include "../header/dynamic_buffer.hpp"

    template<typename Type_A, typename Type_B>
    struct Map
    {
        public:
            Map();
            Map(const Dynamic_Buffer<Pair<Type_A, Type_B>>&);
            Map(Dynamic_Buffer<Pair<Type_A, Type_B>>&&);
            Map(const std::initializer_list<Pair<Type_A, Type_B>>&);
            Map(const Map<Type_A, Type_B>&);
            Map(Map<Type_A, Type_B>&&);
            ~Map();

			Map<Type_A, Type_B>& operator = (const Dynamic_Buffer<Pair<Type_A, Type_B>>&);
			
            Type_B operator [] (const Type_A&) const;
            Type_B& operator [] (const Type_A&);
			
			void insert(const Pair<Type_A, Type_B>&);
			void insert(Pair<Type_A, Type_B>&&);
			void remove(const Type_A&);

        private:
            Dynamic_Buffer<Pair<Type_A, Type_B>> _key_value_pairs;
    };
	
	#include "../header/map.cpp"

#endif

