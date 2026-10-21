#ifndef __MATRIX_CPP__
#define __MATRIX_CPP__

    #include "../header/matrix.hpp"
	
	#include <type_traits>
	
	extern "C" 
	{
		void fortran_matmul_double(const double* A, size_t ra, size_t ca, const double* B, size_t cb, double* C);
		void fortran_matmul_float(const float* A, size_t ra, size_t ca, const float* B, size_t cb, float* C);
	}
    
    template<typename Type>
    Matrix<Type>::Matrix()
    {
        _values = nullptr;
        _rows = 0;
        _columns = 0;
    }
    
    template<typename Type>
    Matrix<Type>::Matrix(size_t height, size_t width)
    {
        _rows = height;
        _columns = width;
        _values = new Type[_rows * _columns];
		memset(_values, 0, _rows * _columns * sizeof(Type));
    }
	
	template<typename Type>
    Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type>> initial_values) 
    {
		_rows = initial_values.size();
        _columns = initial_values.begin()->size();
        _values = new Type[_rows * _columns];
		size_t row = 0U;
		size_t column = 0U;
        for (std::initializer_list<Type> matrix_row : initial_values)
        {
            for (Type matrix_value : matrix_row)
            {
                _values[row * _columns + column] = matrix_value;
				column = (column + 1) % _columns;
            }
			++row;
        }
    }
    
    template<typename Type>
    Matrix<Type>::Matrix(std::initializer_list<Type> initial_values, size_t height, size_t width)
    {
        _rows = height;
        _columns = width;
        _values = new Type[_rows * _columns];
        Type* initial_values_pointer = (Type*)initial_values.begin();
        for (size_t row = 0U; row < _rows; ++row)
        {
            for (size_t column = 0U; column < _columns; ++column)
            {
                _values[row * _columns + column] = *initial_values_pointer;
                ++initial_values_pointer;
            }
        }
    }
    
    template<typename Type>
    Matrix<Type>::Matrix(const Matrix<Type>& initial_matrix)
    {
        if (this != &initial_matrix)
        {
            _rows = initial_matrix._rows;
            _columns = initial_matrix._columns;
            _values = new Type[_rows * _columns];
            for (size_t row = 0U; row < _rows; ++row)
            {
                for (size_t column = 0U; column < _columns; ++column)
                {
                    _values[row * _columns + column] = initial_matrix._values[row * _columns + column];
                }
            }
        }
    }
    
    template<typename Type>
    Matrix<Type>::Matrix(Matrix<Type>&& initial_values)
    {
        if (this != &initial_values)
        {
            _values = initial_values._values;
            _rows = initial_values._rows;
            _columns = initial_values._columns;
            initial_values._values = nullptr;
        }
    }
    
    template<typename Type>
    Matrix<Type>::~Matrix()
    {
        delete [] _values;
    }
    
    template<typename Type>
    Matrix<Type>& Matrix<Type>::operator = (const Matrix<Type>& initial_matrix)
    {
        if (this != &initial_matrix)
        {
            _rows = initial_matrix._rows;
            _columns = initial_matrix._columns;
            delete [] _values;
            _values = new Type[_rows * _columns];
            for (size_t row = 0U; row < _rows; ++row)
            {
                for (size_t column = 0U; column < _columns; ++column)
                {
                    _values[row * _columns + column] = initial_matrix._values[row * _columns + column];
                }
            }
        }
        return *this;
    }
    
    template<typename Type>
    Matrix<Type>& Matrix<Type>::operator = (Matrix<Type>&& initial_values)
    {
        if (this != &initial_values)
        {
            _values = initial_values._values;
            _rows = initial_values._rows;
            _columns = initial_values._columns;
            initial_values._values = nullptr;
        }
        return *this;
    }
    
    template<typename Type>
    Type Matrix<Type>::operator () (size_t row, size_t column) const
    {
        return _values[row * _columns + column];
    }
    
    template<typename Type>
    Type& Matrix<Type>::operator () (size_t row, size_t column)
    {
        return _values[row * _columns + column];
    }
    
    template<typename Type>
    size_t Matrix<Type>::rows() const
    {
        return _rows;
    }
    
    template<typename Type>
    size_t Matrix<Type>::columns() const
    {
        return _columns;
    }
    
    template<typename Type>
    Type Matrix<Type>::determinant() const
    {
        if (_rows != _columns)
        {
            return Type();
        }
        if (_rows == 1U)
        {
            return _values[0];
        }
        if (_rows == 2U)
        {
            return _values[0] * _values[3] - _values[1] * _values[2];
        }
        Type determinant_value = Type();
        int sign = 1;
        for (size_t column = 0; column < _columns; ++column)
        {
            determinant_value += sign * _values[column] * submatrix(0, column).determinant();
            sign *= -1;
        }
        return determinant_value;
    }
    
    template<typename Type>
    Matrix<Type> Matrix<Type>::submatrix(size_t deleted_row, size_t deleted_column) const
    {
        if (_rows <= 1U || _columns <= 1U)
        {
            return *this;
        }
        Matrix<Type> sub_matrix(_rows - 1U, _columns - 1U);
        for (size_t row = 0U; row < deleted_row; ++row)
        {
            for (size_t column = 0U; column < deleted_column; ++column)
            {
                sub_matrix._values[row * sub_matrix._columns + column] = _values[row * _columns + column];
            }
        }
        for (size_t row = deleted_row + 1U; row < _rows; ++row)
        {
            for (size_t column = 0U; column < deleted_column; ++column)
            {
                sub_matrix._values[(row - 1U) * sub_matrix._columns + column] = _values[row * _columns + column];
            }
        }
        for (size_t row = deleted_row + 1U; row < _rows; ++row)
        {
            for (size_t column = deleted_column + 1U; column < _columns; ++column)
            {
                sub_matrix._values[(row - 1U) * sub_matrix._columns + (column - 1U)] = _values[row * _columns + column];
            }
        }
        for (size_t row = 0U; row < deleted_row; ++row)
        {
            for (size_t column = deleted_column + 1U; column < _columns; ++column)
            {
                sub_matrix._values[row * sub_matrix._columns + (column - 1U)] = _values[row * _columns + column];
            }
        }
        return sub_matrix;
    }
    
    template<typename Type>
    Matrix<Type> Matrix<Type>::cofactor() const
    {
        if (_rows != _columns)
        {
            return *this;
        }
        Matrix<Type> cofactor_matrix(_rows, _columns);
        int sign = 1;
        for (size_t row = 0U; row < _rows; ++row)
        {
            for (size_t column = 0U; column < _columns; ++column)
            {
                cofactor_matrix._values[row * cofactor_matrix._columns + column] = sign * submatrix(row, column).determinant();
                sign *= -1;
            }
        }
        return cofactor_matrix;
    }
    
    template<typename Type>
    Matrix<Type> Matrix<Type>::transpose() const
    {
        if (_rows == 0U || _columns == 0U)
        {
            return *this;
        }
        Matrix<Type> transpose_matrix(_columns, _rows);
        for (size_t row = 0; row < transpose_matrix._rows; ++row)
        {
            for (size_t column = 0U; column < transpose_matrix._columns; ++ column)
            {
                transpose_matrix._values[row * transpose_matrix._columns + column] = _values[column * _columns + row];
            }
        }
        return transpose_matrix;
    }
    
    template<typename Type>
    Matrix<Type> Matrix<Type>::inverse() const
    {
		Type det = determinant();
        if (_rows != _columns || det == 0)
        {
            return *this;
        }
        return ((cofactor()).transpose()) / det;
    }
    
    template<typename _Type>
    Matrix<_Type> operator + (const Matrix<_Type>& matrix_A, const Matrix<_Type>& matrix_B)
    {
        if (!matrix_A._rows || !matrix_A._columns || !matrix_B._rows || !matrix_B._columns)
        {
            return Matrix<_Type>();
        }
        if (matrix_A._rows != matrix_B._rows || matrix_A._columns != matrix_B._columns)
        {
            return Matrix<_Type>();
        }
        Matrix<_Type> sum_matrix(matrix_A._rows, matrix_A._columns);
        for (size_t row = 0U; row < sum_matrix._rows; ++row)
        {
            for (size_t column = 0U; column < sum_matrix._columns; ++column)
            {
                sum_matrix._values[row * sum_matrix._columns + column] = 
                matrix_A._values[row * matrix_A._columns + column] + 
                matrix_B._values[row * matrix_B._columns + column];
            }
        }
        return sum_matrix;
    }
    
    template<typename _Type>
    Matrix<_Type> operator - (const Matrix<_Type>& matrix_A, const Matrix<_Type>& matrix_B)
    {
        if (!matrix_A._rows || !matrix_A._columns || !matrix_B._rows || !matrix_B._columns)
        {
            return Matrix<_Type>();
        }
        if (matrix_A._rows != matrix_B._rows || matrix_A._columns != matrix_B._columns)
        {
            return Matrix<_Type>();
        }
        Matrix<_Type> difference_matrix(matrix_A._rows, matrix_A._columns);
        for (size_t row = 0U; row < difference_matrix._rows; ++row)
        {
            for (size_t column = 0U; column < difference_matrix._columns; ++column)
            {
                difference_matrix._values[row * difference_matrix._columns + column] = 
                matrix_A._values[row * matrix_A._columns + column] - 
                matrix_B._values[row * matrix_B._columns + column];
            }
        }
        return difference_matrix;
    }

	template<typename _Type>
    Matrix<_Type> operator * (const Matrix<_Type>& matrix_A, const Matrix<_Type>& matrix_B)
    {
        if (!matrix_A._rows || !matrix_A._columns || !matrix_B._rows || !matrix_B._columns)
        {
            return Matrix<_Type>();
        }
        if (matrix_A._columns != matrix_B._rows)
        {
            return Matrix<_Type>();
        }
        Matrix<_Type> product_matrix(matrix_A._rows, matrix_B._columns);
		if constexpr (std::is_same_v<_Type, double>) 
		{
			fortran_matmul_double(matrix_A._values, matrix_A._rows, matrix_A._columns, 
								  matrix_B._values, matrix_B._columns, product_matrix._values);
		} 
		else if constexpr (std::is_same_v<_Type, float>) 
		{
			fortran_matmul_float(matrix_A._values, matrix_A._rows, matrix_A._columns, 
								 matrix_B._values, matrix_B._columns, product_matrix._values);
		}
		else 
		{
			_Type temp;
			for (size_t row = 0U; row < matrix_A._rows; ++row) 
			{
				for (size_t index = 0U; index < matrix_A._columns; ++index) 
				{
					temp = matrix_A._values[row * matrix_A._columns + index];
					for (size_t column = 0U; column < matrix_B._columns; ++column) 
					{
						product_matrix._values[row * product_matrix._columns + column] += temp * matrix_B._values[index * matrix_B._columns + column];
					}
				}
			}
		}
        return product_matrix;
    }
    
    template<typename _Type>
    Matrix<_Type> operator / (const Matrix<_Type>& matrix, _Type value)
    {
        if (!matrix._rows || !matrix._columns)
        {
            return Matrix<_Type>();
        }
        Matrix<_Type> quotient_matrix(matrix);
        for (size_t row = 0U; row < quotient_matrix._rows; ++row)
        {
            for (size_t column = 0U; column < quotient_matrix._columns; ++column)
            {
                quotient_matrix._values[row * quotient_matrix._columns + column] /= value;
            }
        }
        return quotient_matrix;
    }
    
    template<typename _Type>
    Matrix<_Type> operator ^ (const Matrix<_Type>& matrix, size_t exponent)
    {
        if (matrix._rows != matrix._columns)
        {
            return Matrix<_Type>();
        }
		if (exponent == 0U)
        {
            return matrix_identity<_Type>(matrix._rows);
        }
        if (exponent == 1U)
        {
            return matrix;
        }
        Matrix<_Type> exponentiated_matrix = matrix_identity<_Type>(matrix._rows);
		Matrix<_Type> base_matrix = matrix;
		while (exponent > 0U)
        {
			if (exponent % 2U == 1U)
			{
				exponentiated_matrix = exponentiated_matrix * base_matrix;
			}
			if (exponent > 1U) 
			{
				base_matrix = base_matrix * base_matrix;
			}
			exponent >>= 1U;
        }
        return exponentiated_matrix;
    }
    
    template<typename _Type>
    Matrix<_Type> matrix_identity(size_t size)
    {
        if (!size)
        {
            return Matrix<_Type>();
        }
        Matrix<_Type> identity_matrix(size, size);
        for (size_t index = 0U; index < identity_matrix._rows; ++index)
        {
			identity_matrix._values[index * identity_matrix._columns + index] = (_Type)(1);
        }
        return identity_matrix;
    }
    
#endif