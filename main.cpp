#include <iostream>
#include "thread_pool.h"

using namespace std;

void f1(){ std::cout << "F1!\n"; }
void f2(){ std::cout << "F2!\n"; }

int main()
{
    thread_pool thrp;
    // void f1(){ std::cout << "F1!\n"; }
    // void f2(){ std::cout << "F2!\n"; }
    // thrp.submit(f1);

    return 0;
}
