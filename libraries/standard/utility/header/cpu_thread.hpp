#ifndef CPU_THREAD_HPP
#define CPU_THREAD_HPP

    #if _WIN32
        #include <windows.h>
    #else
        #include <pthread.h>

        class CPU_Thread
        {
            public:
                CPU_Thread();
                CPU_Thread(void* (*)(void*), void*);
                CPU_Thread(const CPU_Thread&) = delete;
                CPU_Thread& operator = (const CPU_Thread&) = delete;
                CPU_Thread& operator = (CPU_Thread&&) = delete;
                void wait();
                static void sleep(unsigned int);
                
            private:
                pthread_t ID; 
        };

    #endif
#endif