#ifndef __IO_HANDLER_HPP__
#define __IO_HANDLER_HPP__

	struct IO_Hander()
	{
		public:
		#ifdef _WIN32
			void* HANDLE;
		#else
			int file_descriptor;
		#endif
	}

#endif