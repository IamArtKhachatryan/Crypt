#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::atomic<int> globlint(0);
std::mutex mtx;
bool quitnow = false;

void MyAsyncSimpleThread() {
    while (!quitnow) {
        std::lock_guard<std::mutex> lock(mtx);  
        globlint++;
        if (globlint > 100) {
            quitnow = true;
        }
        std::cout << "\nMyAsyncSimpleThread: " << globlint << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  
    }
}

int main() {
    std::thread t(MyAsyncSimpleThread);

    while (!quitnow) {
        {
            std::lock_guard<std::mutex> lock(mtx);  
            globlint++;
            if (globlint > 5000) {
                quitnow = true;
            }
            std::cout << "\nMain loop: " << globlint << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));  
    }

    t.join();

    return 0;
}
