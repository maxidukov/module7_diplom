#ifndef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

template<typename T>
class safe_queue
{
    std::queue<T> data;
    mutable std::mutex m;
    std::condition_variable data_cond;
public:
    safe_queue();
    safe_queue(const safe_queue& other){
        std::lock_guard<std::mutex> lock(other.m);
        data=other.data;
    }
    safe_queue& operator=(const safe_queue&) = delete;
    void push(const T& new_value){
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
        data_cond.notify_one();
    }
    void push(T&& new_value){
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
        data_cond.notify_one();
    }
    std::shared_ptr<T> pop(){
       std::unique_lock<std::mutex> lk(m);
        data_cond.wait(lk,[this]{return !data.empty();});
        std::shared_ptr<T> const res(std::make_shared<T>(data.front()));
        data.pop();
        return res;
    }
    void pop(T& value){
        std::unique_lock<std::mutex> lk(m);
        data_cond.wait(lk,[this]{return !data.empty();});
        value=data.front();
        data.pop();
    }
    bool empty() const{
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

#endif // SAFE_QUEUE_H
