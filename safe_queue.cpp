#include "safe_queue.h"

template<typename T>
safe_queue<T>::safe_queue() {}

template class safe_queue<std::function<void()>>;
