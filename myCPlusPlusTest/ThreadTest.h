#ifndef _H_THREADTEST_H_
#define _H_THREADTEST_H_
#include <memory.h>
#include <thread>

using std::thread;
using std::shared_ptr;
using std::unique_ptr;



void ThreadTest( unique_ptr<thread>& pT1, unique_ptr<thread>& pT2);


#endif // _H_THREADTEST_H_
