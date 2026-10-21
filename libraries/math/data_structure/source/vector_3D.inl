#ifndef VECTOR_3D_CPP
#define VECTOR_3D_CPP

    #include <vector_3D.hpp">
    
    template<typename Type>
    Vector_3D<Type>::Vector_3D(Type x_value, Type y_value, Type z_value)
    {
        x = x_value;
        y = y_value;
        z = z_value;
    }
    
    template<typename Type>
    Vector_3D<Type>& Vector_3D<Type>::operator += (const Vector_3D<Type>& vector_3D)
    {
        *this = *this + vector_3D;
        return *this;
    }
    
    template<typename Type>
    Vector_3D<Type>& Vector_3D<Type>::operator += (Type value)
    {
        *this = *this + value;
        return *this;
    }
    
    template<typename Type>
    Vector_3D<Type>& Vector_3D<Type>::operator -= (const Vector_3D<Type>& vector_3D)
    {
        *this = *this - vector_3D;
        return *this;
    }
    
    template<typename Type>
    Vector_3D<Type>& Vector_3D<Type>::operator -= (Type value)
    {
        *this = *this - value;
        return *this;
    }
    
    template<typename Type>
    Vector_3D<Type>& Vector_3D<Type>::operator *= (Type value)
    {
        *this = *this * value;
        return *this;
    }
    
    template<typename Type>
    Vector_3D<Type>& Vector_3D<Type>::operator /= (Type value)
    {
        *this = *this / value;
        return *this;
    }
    
    template<typename Type>
    Type Vector_3D<Type>::magnitude() const
    {
        return (Type)(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
    }
    
    template<typename Type>
    Type Vector_3D<Type>::dot(const Vector_3D<Type>& vector_3D) const
    {
        return (Type)(x * vector_3D.x + y * vector_3D.y + z * vector_3D.z);
    }
    
    template<typename Type>
    Vector_3D<Type> Vector_3D<Type>::cross(const Vector_3D<Type>& vector_3D) const
    {
        return Vector_3D<Type>
        (
            y * vector_3D.z - z * vector_3D.y, 
            -x * vector_3D.z + z * vector_3D.x,
            x * vector_3D.y - y * vector_3D.x
        );
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator + (const Vector_3D<_Type>& vector_3D_A, const Vector_3D<_Type>& vector_3D_B)
    {
        return Vector_3D<_Type>(vector_3D_A.x + vector_3D_B.x, vector_3D_A.y + vector_3D_B.y, vector_3D_A.z + vector_3D_B.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator + (_Type value, const Vector_3D<_Type>& vector_3D)
    {
        return Vector_3D<_Type>(value + vector_3D.x, value + vector_3D.y, value + vector_3D.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator + (const Vector_3D<_Type>& vector_3D, _Type value)
    {
        return Vector_3D<_Type>(value + vector_3D.x, value + vector_3D.y, value + vector_3D.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator - (const Vector_3D<_Type>& vector_3D_A, const Vector_3D<_Type>& vector_3D_B)
    {
        return Vector_3D<_Type>(vector_3D_A.x - vector_3D_B.x, vector_3D_A.y - vector_3D_B.y, vector_3D_A.z - vector_3D_B.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator - (const Vector_3D<_Type>& vector_3D, _Type value)
    {
        return Vector_3D<_Type>(vector_3D.x - value, vector_3D.y - value, vector_3D.z - value);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator - (const Vector_3D<_Type>& vector_3D)
    {
        return Vector_3D<_Type>(-vector_3D.x, -vector_3D.y, -vector_3D.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator * (_Type value, const Vector_3D<_Type>& vector_3D)
    {
        return Vector_3D<_Type>(value * vector_3D.x, value * vector_3D.y, value * vector_3D.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator * (const Vector_3D<_Type>& vector_3D, _Type value)
    {
        return Vector_3D<_Type>(value * vector_3D.x, value * vector_3D.y, value * vector_3D.z);
    }
    
    template<typename _Type>
    Vector_3D<_Type> operator / (const Vector_3D<_Type>& vector_3D, _Type value)
    {
        return Vector_3D<_Type>(vector_3D.x / value, vector_3D.y / value, vector_3D.z / value);
    }

#endif