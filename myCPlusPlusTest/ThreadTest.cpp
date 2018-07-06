#include "ThreadTest.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <atomic>

using std::make_unique;
using std::cout;
using std::endl;
using std::vector;
using std::ref;
using std::cref;
using std::atomic_int;

void counter(int id, int numIterations)
{

	for ( int i = 0; i< numIterations; ++i )
	{
		cout << "Counter" << id << " has value";
		cout << i << endl;
	}

	::Sleep(1000);

}


//2
class Counter
{
public:
	Counter( int id, int numIterations )
		: mID(id)
	    ,mNumIterations(numIterations) {
	}

	void operator()()const
	{
		for (int i = 0; i < mNumIterations; ++i)
		{
			cout << "Counter" << mID << " has value";
			cout << i << endl;
		}
	}

private:
	int mID;
	int mNumIterations;

};
//

//3
class Request
{
public:
	Request(int id) : mId(id) {}

	void process()
	{
		cout << "Processing request " << mId << endl;
	}

private:
	int mId;
};
//


//4
#include <stdexcept>
using std::runtime_error;
using std::exception_ptr;
using std::current_exception;

void doSomeWork()
{

	for ( int i = 0; i<5; ++i )
	{
		cout << i << endl;
	}

	cout << " Thread throwing a runtime_error exception..." << endl;
	throw runtime_error("Exception from thread");
}

void threadFunc( exception_ptr& err )
{
	try
	{
		doSomeWork();
	}
	catch (...)
	{
		cout << "Thread caught exception, returning exception..." << endl;
		err = current_exception();
	}
}

void doWorkInThread()
{
	exception_ptr error;

	// Launch background thread
	thread t( threadFunc, ref(error) );

	// Wait for thread to finish
	t.join();

	// See if thread has thrown any exception
	if ( error )
	{
		cout << "Main thread received exception, rethrowing it..." << endl;
		rethrow_exception(error);
	}
	else
	{
		cout << "Main thread did not receive any exception." << endl;
	}
}
//

// 原子类型示例
void func(atomic_int& counter)
{
	int nResult = 0;
	for ( int i = 0; i<100; ++i )
	{
		++nResult;
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	counter += nResult;

}

void AutoTest()
{
	atomic_int counter = 0;
	vector<thread> theads;
	for ( int i = 0; i<10; ++i )
	{
		theads.emplace_back(thread(func, ref(counter)));
	}

	for (auto& t : theads)
	{
		t.join();
	}
		
	cout << "Result = " << counter << endl;

}
//

// 互斥操作
#include <mutex>
using std::mutex;
//

// call_once测试
using std::once_flag;
using std::call_once;

once_flag gOnceFlag;
void initiallizeShareResources()
{
	// ... Initialize shared resources that will be used by multiple threads.
	cout << "Shared resources initialized." << endl;
}

void processingFunction()
{
	// Make sure the shared resources are initialized.
	call_once(gOnceFlag, initiallizeShareResources);

	// ... Do some work, including using the shared resources
	cout << "Processing" << endl;
}

void CallOnceTest()
{
	// Launch 3 threads.
	vector<thread> threads(3);
	for ( auto& t : threads )
	{
		t = thread{ processingFunction };
	}
	for ( auto& t: threads )
	{
		t.join();
	}

}
//

//std::future与std::async测试
#include <future>

bool is_prime(int x)
{
	for ( int i = 2; i<x; ++i )
	{
		if (x%i == 0)
			return false;
	}
	return true;

}

void futureTest()
{
	// call function asynchronously
	std::future< bool > fut = std::async(is_prime, 44444444443);


	try
	{
		// do something while waiting for function to set future:
		cout << "checking, please wait";
		std::chrono::microseconds span(100);

		while (fut.wait_for(span) == std::future_status::timeout)
		{
			cout << '.';
		}


		bool x = fut.get();

		cout << "\n44444444443 " << (x ? "is" : "is not") << " prime.\n";
	}
	catch (const std::exception& err )
	{
		cout << "Caught exception: " << err.what() << endl;
	}

	

	
}

//



void ThreadTest(unique_ptr<thread>& pT1, unique_ptr<thread>& pT2)
{
	futureTest();
	return;

	//CallOnceTest();
	//return;

// 	AutoTest();
// 	return;

	//////////////////////////////////////////////////////////////////////////
	//try
	//{
	//	doWorkInThread();
	//}
	//catch (const std::exception& e)
	//{
	//	cout << "Main function caught:" << e.what() << "'" << endl;
	//}
	//return;

	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//Request req(100);
	//thread t(&Request::process, &req);
	//t.join();


	//// Using uniform initialization syntax
	thread t1{ Counter{1,20} };
	//// Using named variable
	//Counter c(2, 12);
	//thread t2(c);
	//
	//// Using temporary
	//thread t3(Counter(3, 10));

	t1.join();
	//t2.join();
	//t3.join();


	int id = 1;
	int numIterations = 5;

	thread t4([ id, numIterations ]() { 
		for (int i = 0; i < numIterations; ++i)
		{
			cout << "Counter" << id << " has value";
			cout << i << endl;
		}
	});
	t4.join();


	return;
	//////////////////////////////////////////////////////////////////////////

	unique_ptr<thread> pt1 = make_unique<thread>(counter, 1, 60);
	unique_ptr<thread> pt2 = make_unique<thread>(counter, 2, 40);
	//
	////t1->detach();
	////t2->detach();
	//
	pT1 = std::move(pt1);
	pT2 = std::move(pt2);
	

}