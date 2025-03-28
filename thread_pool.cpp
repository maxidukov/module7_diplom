#include "thread_pool.h"

thread_pool::thread_pool()
{
    unsigned const thread_count=std::thread::hardware_concurrency();
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
    for(unsigned long i=0;i<thrvec.size();++i)
    {
        if(thrvec[i].joinable())
            thrvec[i].join();
    }
}
