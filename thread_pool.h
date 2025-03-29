#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <vector>
#include <thread>
// #include <atomic>
#include <functional>
#include "safe_queue.h"

class thread_pool
{
    std::vector<std::thread> thrvec;
    safe_queue<std::function<void()>> task_queue;
    std::mutex queue_mutex;
    // bool stop_ = false;
    void work()
    {
        // while(!stop_)
        // {
            std::function<void()> task;
            try
            {
                task_queue.pop(task);
            }
            catch(...)
            {
                std::cout << "Thread waited too long\n";
            }
            task();
            // std::cout << "Loop work still running\n";
        // }
    }
public:
    thread_pool();
    ~thread_pool(){
        // {
        //     std::unique_lock<std::mutex> lock(queue_mutex);
        //     // stop_ = true;
        // }
        for(unsigned long i=0;i<thrvec.size();++i)
        {
            if(thrvec[i].joinable())
                thrvec[i].join();
        }
        std::cout << "Jobs done" << std::endl; //WARNING: MAY NEVER RUN IF MORE THREADS THAN JOBS, IDLE THREADS WILL WAIT FOR COND VAR TO NOTIFY THEM FOR EVER
    }
    template<typename Function>
    void submit(Function f)
    {
        task_queue.push(std::function<void()>(f));
    }
};

#endif // THREAD_POOL_H
