#include <iostream>
#include <atomic>

// Preprocessor directives for cross-platform handling
#ifdef _COMPILE_WINDOWS
#include <Windows.h>  // For Sleep and thread management on Windows
typedef HANDLE THREADVAR;
typedef DWORD THREADFUNCVAR;  // Change to DWORD
typedef LPVOID THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef CRITICAL_SECTION THREAD_LOCK;
#endif

#ifdef _COMPILE_LINUX
#include <pthread.h>  // For thread management on Linux
#include <unistd.h>   // For usleep on Linux
typedef pthread_t THREADVAR;
typedef void* THREADFUNCVAR;
typedef void* THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef pthread_mutex_t THREAD_LOCK;
#endif

// Globals
std::atomic<int> globlint(0);
bool quitnow = false;

// Cross-platform thread function declaration
THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam);

// Cross-platform thread management functions
THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg);
void StopThread(THREADVAR t);
void InitThreadLock(THREAD_LOCK& t);
void LockThread(THREAD_LOCK& t);
void UnlockThread(THREAD_LOCK& t);
void sleep(int ms);

// The thread function
THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam) {
    THREAD_LOCK& ref_lock = *((THREAD_LOCK*)lpParam);  // Get the thread lock passed as parameter

    while (!quitnow) {
        LockThread(ref_lock);  // Lock the mutex
        globlint++;
        if (globlint > 100) {
            quitnow = true;
        }
        std::cout << "\nMyAsyncSimpleThread: " << globlint << std::endl;
        UnlockThread(ref_lock);  // Unlock the mutex
        sleep(1000);  // Sleep for 1 second
    }
    return 0;  // Return 0 (not NULL)
}

int main() {
    THREAD_LOCK lock;
    InitThreadLock(lock);

    // Prepare the thread with a parameter
    THREADVAR threadHandle = PrepareThread(MyAsyncSimpleThread, (THREADFUNCARGS)&lock);

    // Main loop with synchronization
    while (!quitnow) {
        LockThread(lock);  // Lock the mutex
        globlint++;
        if (globlint > 5000) {
            quitnow = true;
        }
        std::cout << "\nMain loop: " << globlint << std::endl;
        UnlockThread(lock);  // Unlock the mutex
        sleep(5);  // Sleep for 5 milliseconds
    }

    StopThread(threadHandle);  // Stop the thread
    return 0;
}

// Cross-platform thread handling functions
THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg) {
#ifdef _COMPILE_LINUX
    pthread_t out;
    pthread_create(&out, NULL, f, arg);
    return out;
#endif

#ifdef _COMPILE_WINDOWS
    DWORD thrId;
    THREADVAR out = CreateThread(
        NULL,                // default security attributes
        0,                   // use default stack size  
        (LPTHREAD_START_ROUTINE)f,  // thread function
        arg,                 // argument to thread function
        0,                   // use default creation flags 
        &thrId               // returns the thread identifier
    );
    return out;
#endif
}

void StopThread(THREADVAR t) {
#ifdef _COMPILE_LINUX
    pthread_exit((void*)t);
#endif

#ifdef _COMPILE_WINDOWS
    TerminateThread(t, 0);
    CloseHandle(t);
#endif
}

void InitThreadLock(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
    pthread_mutex_init(&t, NULL);
#endif

#ifdef _COMPILE_WINDOWS
    InitializeCriticalSection(&t);
#endif
}

void LockThread(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
    pthread_mutex_lock(&t);
#endif

#ifdef _COMPILE_WINDOWS
    EnterCriticalSection(&t);
#endif
}

void UnlockThread(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
    pthread_mutex_unlock(&t);
#endif

#ifdef _COMPILE_WINDOWS
    LeaveCriticalSection(&t);
#endif
}

void sleep(int ms) {
#ifdef _COMPILE_LINUX
    usleep(ms * 1000);  // usleep takes time in microseconds
#endif

#ifdef _COMPILE_WINDOWS
    Sleep(ms);  // Sleep takes time in milliseconds
#endif
}
