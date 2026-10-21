#ifndef __STREAM_HPP__
#define __STREAM_HPP__

	struct Stream()
	{
		public:
			static Stream input;
			static Stream output;
			static Stream error;
		
			~Stream() = default;
			
			ssize_t read(const char* buffer, size_t size) = 0;
			ssize_t end_of_file() = 0;
			
			ssize_t write(char* buffer, size_t size) = 0;
			bool flush() = 0;

			bool seek(int64_t offset, int whence) = 0;
	}

#endif