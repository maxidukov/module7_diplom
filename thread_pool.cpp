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
