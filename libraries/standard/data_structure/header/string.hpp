#ifndef __STRING_HPP__
#define __STRING_HPP__

    #include <stddef.h>
	#include <stdint.h>
	#include <initializer_list>
	#include <dynamic_buffer.hpp>

    void copy_string(char* const, const char* const, size_t);
    size_t string_length(const char* const);
    void append_char(char* const, char);
    void append_string(char* const, const char* const);
    void insert_char(char* const, char, size_t);
    void insert_string(char* const, const char* const, size_t);
    void detach_char(char* const);
    void remove_char(char* const, size_t);
    void remove_substring(char* const, size_t, size_t);
    char* substring(const char* const, size_t, size_t);
    void resize_string(char* const, size_t);
    char* uppercase(char* const);
    char* lowercase(char* const);
    size_t index_of_string(const char* const, const char* const);
    size_t index_of_char(const char* const, char);
    void modify_string(char* const, char (*)(char));
    void clear_string(char* const);
        
    struct String
    {
        public:
            String();
            //String(size_t);
            String(char, size_t);
            String(const char*);
            String(const char*, size_t);
            String(std::initializer_list<char>);
			String(int);
			String(float);
            String(const String&);
            String(String&&);
            ~String() = default;
            
            String& operator = (const char*);
            String& operator = (const String&);
            String& operator = (String&&);
            String& operator += (char);
            String& operator += (const char*);
            String& operator += (const String&);
            char operator [] (size_t) const;
            char& operator [] (size_t);
            String operator () (size_t, size_t) const;
            
            const char* c_string() const;
            size_t length() const;
            
            void append(char);
            void append(const String&);
            void insert(char, size_t);
            void insert(const String&, size_t);
            void detach();
            void remove(size_t);
            void resize(size_t);
            String uppercase();
            String lowercase();
            size_t index_of(char) const;
            size_t index_of(const String&) const;
            void modify(char (*)(char));
            void clear();
            
            friend bool operator == (const String&, const String&);
            friend bool operator != (const String&, const String&);
            friend String operator + (const String&, const String&);
            friend String operator + (const String&, const char* const);
            friend String operator + (const char* const, const String&);
            friend String operator + (const String&, char);
            friend String operator + (char, const String&);
            
        private:
			Dynamic_Buffer<char> _buffer;
    };
    
#endif