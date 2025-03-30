#include <iostream>
#include "thread_pool.h"

using namespace std;

void f1(){ std::cout << "F1!\n"; }
void f2(){ std::cout << "F2!\n"; }

int main()
{
    thread_pool thrp;

    // thrp.submit(f1);
    // thrp.submit(f2);

    for (int i = 0; i < 5; ++i) {
        thrp.submit(f1);
        thrp.submit(f2);
        this_thread::sleep_for(
                chrono::seconds(1));
    }

    return 0;
}
