#ifndef __STRING_CPP__
#define __STRING_CPP__

    #include <string.hpp>

	#define __INITIAL_STRING_CAPACITY__ 16U
	#define __INTEGER_32_MAX_DIGITS__ 20
	#define __FLOAT_THRESHOLD__ 1e-6F
	#define __SAFETY_THRESHOLD__ 30
	
	String::String() : _buffer(__INITIAL_STRING_CAPACITY__, 0U) {}
    
    String::String(char character, size_t length) : _buffer(length + 1, length)
    {
		for (size_t index = 0U; index < length; ++index)
		{
			_buffer[index] = character;
		}
		_buffer[length] = '\0';
    }
    
    String::String(const char* string)
    {
		if (string == nullptr || string[0] == '\0')
		{
			_buffer = Dynamic_Buffer<char>(1U, 0U);
		}
		size_t length = 0U;
        for (; string[length] != '\0'; ++length){}
        if (length == 0U)
        {
            _buffer = Dynamic_Buffer<char>(1U, 0U);
        }
		else
		{
			_buffer = Dynamic_Buffer<char>(length + 1U, length);
			for (size_t index = 0U; index < length; ++index)
			{
				_buffer[index] = string[index];
			}
		}
		_buffer[length] = '\0';
    }
    
    String::String(const char* string, size_t copy_length)
    {
		if (string == nullptr || string[0] == '\0')
		{
			_buffer = Dynamic_Buffer<char>(1U, 0U);
			_buffer[1] = '\0';
			return;
		}
		size_t actual_length = 0U;
        for (; string[actual_length] != '\0'; ++actual_length){}
		size_t length = (copy_length <= actual_length) ? copy_length : actual_length;
        if (length == 0U)
        {
            _buffer = Dynamic_Buffer<char>(1U, 0U);
			_buffer[1] = '\0';
			return;
        }
		_buffer = Dynamic_Buffer<char>(length + 1U, length);
		for (size_t index = 0U; index < length; ++index)
		{
			_buffer[index] = string[index];
		}
		_buffer[length] = '\0';
    }
    
    String::String(std::initializer_list<char> string)
    {
		if (string.size() == 0U)
		{
			_buffer = Dynamic_Buffer<char>(1U, 0U);
			_buffer[1] = '\0';
			return;
		}
		size_t length = string.size();
		_buffer = Dynamic_Buffer<char>(length + 1U, length);
		size_t index = 0U;
		for (char character : string)
		{
			_buffer[index] = character;
			++index;
		}
		_buffer[length] = '\0';
    }
	
	String::String(int value) 
	{
		if (value == 0) 
		{
			_buffer = Dynamic_Buffer<char>(2U, 1U);
			_buffer[0] = '0';
			_buffer[1] = '\0';
			return;
		}

		bool is_negative = (value < 0);
		unsigned int absolute = is_negative ? static_cast<unsigned int>(-value) : static_cast<unsigned int>(value);

		size_t digits = 0;
		unsigned int temp = absolute;
		while (temp > 0) 
		{
			temp /= 10;
			++digits;
		}

		size_t total_length = digits + (is_negative ? 1 : 0);

		_buffer = Dynamic_Buffer<char>(total_length + 1, total_length); // +1 for '\0'

		size_t index = total_length - 1;
		while (absolute > 0) 
		{
			_buffer[index--] = '0' + (absolute % 10);
			absolute /= 10;
		}

		if (is_negative) 
		{
			_buffer[0] = '-';
		}

		_buffer[total_length] = '\0';
	}


	
	String::String(float value)
	{
		bool is_negative = (value < 0.0F);
		if (is_negative) value = -value;

		int int_part = static_cast<int>(value);
		float fractional = value - static_cast<float>(int_part);

		// Buffer to store digits
		char int_buf[16];
		int int_len = 0;

		if (int_part == 0) 
		{
			int_buf[int_len++] = '0';
		} 
		else 
		{
			int temp = int_part;
			while (temp > 0) 
			{
				int_buf[int_len++] = '0' + (temp % 10);
				temp /= 10;
			}
		}

		// Final buffer to build the string
		char temp[64];
		size_t pos = 0;

		if (is_negative) 
		{
			temp[pos++] = '-';
		}

		// Copy integer part in correct order
		for (int i = int_len - 1; i >= 0; --i) 
		{
			temp[pos++] = int_buf[i];
		}

		// Handle fractional part (up to 6 digits)
		if (fractional > __FLOAT_THRESHOLD__) 
		{
			temp[pos++] = '.';

			int precision = 6;
			while (precision-- > 0 && fractional > __FLOAT_THRESHOLD__) 
			{
				fractional *= 10.0f;
				int digit = static_cast<int>(fractional);
				temp[pos++] = '0' + digit;
				fractional -= digit;
			}

			// Trim trailing zeros
			while (temp[pos - 1] == '0') 
			{
				--pos;
			}

			// Remove trailing decimal point
			if (temp[pos - 1] == '.') 
			{
				--pos;
			}
		}

		// Null-terminate
		temp[pos] = '\0';

		// Set to dynamic buffer
		_buffer = Dynamic_Buffer<char>(pos + 1, pos);
		for (size_t i = 0; i < pos; ++i) {
			_buffer[i] = temp[i];
		}
		_buffer[pos] = '\0';
	}


    
    String::String(const String& string)
    {
		_buffer = string._buffer;
    }
    
    String::String(String&& string)
    {
		if (this == &string)
        {
            return;
        }
		_buffer = static_cast<Dynamic_Buffer<char>&&>(string._buffer);
    }
    
    String& String::operator = (const char* string)
    {
		size_t length = 0U;
        for (length = 0U; string[length] != '\0'; ++length){}
		_buffer.set_capacity(length + 1U);
		_buffer.set_size(length);
        for (size_t index = 0U; index < length; ++index)
        {
            _buffer[index] = string[index];
        }
        _buffer[length] = '\0';
        return *this;
    }

    String& String::operator = (const String& string)
    {
        if (this != &string)
        {
            _buffer = string._buffer;
        }
        return *this;
    }

    String& String::operator = (String&& string)
    {
        if (this != &string)
        {
            _buffer = static_cast<Dynamic_Buffer<char>&&>(string._buffer);
        }
        return *this;
    }

    String& String::operator += (char character)
    {
		_buffer.insert(character, _buffer.size());
        return *this;
    }

    String& String::operator += (const char* string)
    {
		size_t string_length = 0U;
        for (; string[string_length] != '\0'; ++string_length){}
        while (this->length() + string_length > _buffer.capacity())
        {
            _buffer.increase_capacity();
        }
        for (size_t index = 0U; index < string_length; ++index)
		{
			_buffer[index + this->length()] = string[index];
		}
        _buffer.set_size(this->length() + string_length);
		_buffer[this->length()] = '\0';
        return *this;
    }

    String& String::operator += (const String& string)
    {
		while (this->length() + string.length() > _buffer.capacity())
        {
            _buffer.increase_capacity();
        }
        for (size_t index = 0U; index < string.length(); ++index)
		{
			_buffer[index + this->length()] = string[index];
		}
        _buffer.set_size(this->length() + string.length());
		_buffer[this->length()] = '\0';
        return *this;
    }

    char String::operator [] (size_t index) const
    {
        return _buffer[index];
    }

    char& String::operator [] (size_t index)
    {
        return _buffer[index];
    }

    String String::operator () (size_t start, size_t end) const
    {
		String substring;
		substring._buffer.set_capacity(end - start + 2U);
		substring._buffer.set_size(end - start + 1U);
        for (size_t index = 0; index < end - start + 1; ++index)
        {
            substring._buffer[index] = _buffer[index + start];
        }
		substring._buffer[substring.length()] = '\0';
        return substring;
    }

    const char* String::c_string() const
    {
        return _buffer.values();
    }

    size_t String::length() const
    {
        return _buffer.size();
    }
	
	String operator + (const String& string_A, const String& string_B)
	{
		String concatenated_string;
		concatenated_string._buffer.set_capacity(string_A.length() + string_B.length() + 1U);
		concatenated_string._buffer.set_size(string_A.length() + string_B.length());
        size_t index = 0;
        for (; index < string_A.length(); ++index)
        {
            concatenated_string._buffer[index] = string_A._buffer[index];
        }
        for (; index < string_A.length() + string_B.length(); ++index)
        {
            concatenated_string._buffer[index] = string_B._buffer[index - string_A.length()];
        }
        concatenated_string._buffer[concatenated_string.length()] = '\0'; 
		return concatenated_string;
	}

#endif