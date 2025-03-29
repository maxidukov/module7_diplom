#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include "safe_queue.h"

class thread_pool
{
    std::vector<std::thread> thrvec;
    safe_queue<std::function<void()>> task_queue;
    // std::mutex queue_mutex;
    // bool stop_ = false;
    void work();
public:
    thread_pool();
    ~thread_pool();
    template<typename Function>
    void submit(Function f)
    {
        task_queue.push(std::function<void()>(f));
    }
};

#endif // THREAD_POOL_H
