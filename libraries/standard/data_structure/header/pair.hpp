#ifndef __PAIR_HPP__
#define __PAIR_HPP__

    template<typename Type_A, typename Type_B>
    struct Pair
    {
        public:
            Type_A value_A;
            Type_B value_B;

            Pair();
            Pair(const Type_A&, const Type_B&);
            Pair(Type_A&&, Type_B&&);
            Pair(const Pair<Type_A, Type_B>&);
            Pair(Pair<Type_A, Type_B>&&);

            Pair<Type_A, Type_B>& operator = (const Pair<Type_A, Type_B>&);
            Pair<Type_A, Type_B>& operator = (Pair<Type_A, Type_B>&&);
    };

    #include "../source/pair.inl"

#endif