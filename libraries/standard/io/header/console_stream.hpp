#ifndef __CONSOLE_STREAM_HPP__
#define __CONSOLE_STREAM_HPP__

	#include <array.hpp>

	#define __CONSOLE_STREAM_BUFFER_SIZE__ 256U
	
	struct Console_Stream : Stream
	{
		public:
			static Console_Stream& input;
			static Console_Stream& output;
			static Console_Stream& error;
			
			ssize_t read();
		
		private:
			virtual Console_Stream() = default;
			virtual ~Console_Stream() = default;
			
			IO_Handler _handler;
			Static_Buffer<char, __CONSOLE_STREAM_BUFFER_SIZE__> _buffer;
	}

#endif