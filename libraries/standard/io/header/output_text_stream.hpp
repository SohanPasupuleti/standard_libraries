/*
#ifndef OUTPUT_STREAM_HPP
#define OUTPUT_STREAM_HPP
	
	#include <static_buffer.hpp>

	#define __OUTPUT_STREAM_BUFFER_CAPACITY__ 128U

	struct Output_Stream
	{
		public:
			enum struct Mode : uint8_t;
			
			//static Output_Text_Stream main;
			
			Output_Stream();
			Output_Stream(const String&, Output_Stream::Write_Mode);
			Output_Stream(const Output_Stream&);
			Output_Stream(Output_Stream&&);
			~Output_Stream();
			
			Output_Stream& operator = (const Output_Stream&);
			Output_Stream& operator = (Output_Stream&&);
			Output_Stream& operator << (char);
			Output_Stream& operator << (bool);
			Output_Stream& operator << (int);
			Output_Stream& operator << (unsigned int);
			Output_Stream& operator << (float);
			Output_Stream& operator << (double);
			Output_Stream& operator << (const char* const);
			//Output_Stream& operator << (const String&);
			
			String file_name() const;
			Output_Stream::Write_Mode write_mode() const;

			void clear();
			void flush();

			friend bool operator == (const Output_Stream&, const Output_Stream&);
			friend bool operator != (const Output_Stream&, const Output_Stream&);
		
		private:
			#ifdef _WIN32
				HANDLE _handle;
				DWORD _characters_written;
			#else
				int _file_descriptor;
			#endif
			Static_Buffer<CHAR, __OUTPUT_STREAM_BUFFER_CAPACITY__> _buffer;
			Mode _mode;
	};

	enum struct Output_Stream::Write_Mode : uint8_t
	{
		Inactive = 0,
		Write = 1,
		Append = 2
		Console = 3
	};
	
	enum struct Output_Stream::Object_Mode
	{
		Undefined = 0,
		Binary = 1,
		Text = 2
	};

#endif
*/