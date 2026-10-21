#ifndef __VECTOR_3D_HPP__
#define __VECTOR_3D_HPP__

    template<typename Type>
    struct Vector_3D
    {
        public:
            Type x;
            Type y;
            Type z;
            
            Vector_3D() = default;
            Vector_3D(Type, Type, Type);
            Vector_3D(const Vector_3D<Type>&) = default;
            
            Vector_3D<Type>& operator = (const Vector_3D<Type>&) = default;
            Vector_3D<Type>& operator += (const Vector_3D<Type>&);
            Vector_3D<Type>& operator += (Type);
            Vector_3D<Type>& operator -= (const Vector_3D<Type>&);
            Vector_3D<Type>& operator -= (Type);
            Vector_3D<Type>& operator *= (Type);
            Vector_3D<Type>& operator /= (Type);
            
            Type magnitude() const;
            Type dot(const Vector_3D<Type>&) const;
            Vector_3D<Type> cross(const Vector_3D<Type>&) const;
            
            template<typename _Type>
            friend Vector_3D<_Type> operator + (const Vector_3D<_Type>&, const Vector_3D<_Type>&);
            template<typename _Type>
            friend Vector_3D<_Type> operator + (_Type, const Vector_3D<_Type>&);
            template<typename _Type>
            friend Vector_3D<_Type> operator + (const Vector_3D<_Type>&, _Type);
            template<typename _Type>
            friend Vector_3D<_Type> operator - (const Vector_3D<_Type>&, const Vector_3D<_Type>&);
            template<typename _Type>
            friend Vector_3D<_Type> operator - (const Vector_3D<_Type>&, _Type);
            template<typename _Type>
            friend Vector_3D<_Type> operator - (const Vector_3D<_Type>&);
            template<typename _Type>
            friend Vector_3D<_Type> operator * (_Type, const Vector_3D<_Type>&);
            template<typename _Type>
            friend Vector_3D<_Type> operator * (const Vector_3D<_Type>&, _Type);
            template<typename _Type>
            friend Vector_3D<_Type> operator / (const Vector_3D<_Type>&, _Type);
            
    };
    
    #include "../source/vector_3D.inl"
    
#endif