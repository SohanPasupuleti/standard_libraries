#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

    #include <stddef.h>
	#include <string.h>
    #include <initializer_list>
    
    template<typename Type>
    struct Matrix
    {
        public:
            Matrix();
            Matrix(size_t, size_t);
			Matrix(std::initializer_list<std::initializer_list<Type>>);
            Matrix(std::initializer_list<Type>, size_t, size_t);
            Matrix(const Matrix<Type>&);
            Matrix(Matrix<Type>&&);
            ~Matrix();
            
            Matrix& operator = (const Matrix<Type>&);
            Matrix& operator = (Matrix<Type>&&);
            Matrix& operator += (const Matrix<Type>&);
            Matrix& operator += (Type);
            Matrix& operator -= (const Matrix<Type>&);
            Matrix& operator -= (Type);
            Matrix& operator *= (const Matrix<Type>&);
            Matrix& operator *= (Type);
            Matrix& operator /= (Type);
            Matrix& operator ^= (Type);
            Type operator () (size_t, size_t) const;
            Type& operator () (size_t, size_t);
            
            size_t rows() const;
            size_t columns() const;
            Type determinant() const;
            Matrix<Type> submatrix(size_t, size_t) const;
            Matrix<Type> cofactor() const;
            Matrix<Type> transpose() const;
            Matrix<Type> inverse() const;
            
            template<typename _Type>
            friend Matrix<_Type> operator + (const Matrix<_Type>&, const Matrix<_Type>&);
            template<typename _Type>
            friend Matrix<_Type> operator + (const Matrix<_Type>&, _Type);
            template<typename _Type>
            friend Matrix<_Type> operator + (_Type, const Matrix<_Type>&);
            template<typename _Type>
            friend Matrix<_Type> operator - (const Matrix<_Type>&, const Matrix<_Type>&);
            template<typename _Type>
            friend Matrix<_Type> operator - (const Matrix<_Type>&, _Type);
            template<typename _Type>
            friend Matrix<_Type> operator - (_Type, const Matrix<_Type>&);
            template<typename _Type>
            friend Matrix<_Type> operator * (const Matrix<_Type>&, const Matrix<_Type>&);
            template<typename _Type>
            friend Matrix<_Type> operator * (const Matrix<_Type>&, _Type);
            template<typename _Type>
            friend Matrix<_Type> operator * (_Type, const Matrix<_Type>&);
            template<typename _Type>
            friend Matrix<_Type> operator / (const Matrix<_Type>&, _Type);
            template<typename _Type>
            friend Matrix<_Type> operator ^ (const Matrix<_Type>&, size_t);
            
            template<typename _Type>
            friend Matrix<_Type> matrix_identity(size_t);
            
        private:
            Type* _values;
            size_t _rows;
            size_t _columns;
    };
	
	template<typename _Type>
	Matrix<_Type> matrix_identity(size_t size);

    #include "../source/matrix.inl"
    
#endif