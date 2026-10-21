#ifndef __PAIR_INL__
#define __PAIR_INL__

    #include <pair.hpp>

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>::Pair()
    {
        value_A = Type_A();
        value_B = Type_B();
    }

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>::Pair(const Type_A& initial_value_A, const Type_B& initial_value_B)
    {
        value_A = initial_value_A;
        value_B = initial_value_B;
    }

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>::Pair(Type_A&& initial_value_A, Type_B&& initial_value_B)
    {
        value_A = static_cast<Type_A&&>(initial_value_A);
        value_B = static_cast<Type_B&&>(initial_value_B);
    }

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>::Pair(const Pair<Type_A, Type_B>& initial_pair)
    {
        value_A = initial_pair.value_A;
        value_B = initial_pair.value_B;
    }

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>::Pair(Pair<Type_A, Type_B>&& initial_pair)
    {
        value_A = static_cast<Type_A&&>(initial_pair.value_A);
        value_B = static_cast<Type_B&&>(initial_pair.value_B);
    }

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>& Pair<Type_A, Type_B>::operator = (const Pair<Type_A, Type_B>& pair)
    {
        if (this == &pair)
        {
            return *this;
        }
        value_A = pair.value_A;
        value_B = pair.value_B;
        return *this;
    }

    template<typename Type_A, typename Type_B>
    Pair<Type_A, Type_B>& Pair<Type_A, Type_B>::operator = (Pair<Type_A, Type_B>&& pair)
    {
        if (this == &pair)
        {
            return *this;
        }
        value_A = static_cast<Type_A&&>(pair.value_A);
        value_B = static_cast<Type_A&&>(pair.value_B);
        return *this;
    }

#endif