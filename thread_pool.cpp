#include "thread_pool.h"

thread_pool::thread_pool()
{
    unsigned const thread_count=std::thread::hardware_concurrency();
    // std::cout << thread_count << std::endl;
    try
    {
        for(unsigned i=0;i<thread_count;++i)
        {
            thrvec.push_back(
                std::thread(&thread_pool::work,this));
        }
    }
    catch(...)
    {
        throw;
    }

}

thread_pool::~thread_pool(){
    stop_ = true;
    for(unsigned long i=0;i<thrvec.size();++i)
    {
        if(thrvec[i].joinable())
            thrvec[i].join();
    }
    //std::cout << "All jobs done" << std::endl; //WARNING: MAY NEVER RUN IF MORE THREADS THAN JOBS AND NO NEW JOBD ARE COMING, IDLE THREADS WILL WAIT FOR COND VAR TO NOTIFY THEM FOR EVER
}

void thread_pool::work()
{
    while(!stop_)
    {
    std::function<void()> task;
    try
    {
        task_queue.pop(task);

    }
    catch(...)
    {
        //stop_ = true;
        std::this_thread::yield();
    }
    task();
    }
}
