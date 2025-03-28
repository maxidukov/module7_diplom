#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include "safe_queue.h"

class thread_pool
{
    std::vector<std::thread> thrvec;
    safe_queue<std::function<void()>> task_queue;
    void work()
    {
            std::function<void()> task;
            try
            {
                task_queue.pop(task);
            }
            catch(...)
            {
                std::this_thread::yield();
            }
            task();
    }
public:
    thread_pool();
    ~thread_pool(){}
    template<typename Function>
    void submit(Function f)
    {
        task_queue.push(std::function<void()>(f));
    }
};

#endif // THREAD_POOL_H
