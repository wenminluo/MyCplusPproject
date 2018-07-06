#include "TBBTest.h"
#include <iostream>
#include "tbb\tbb.h"
using namespace std;


// tbb任务
class first_task : public tbb::task
{
public:
	virtual ~first_task();


	/// \brief 任务执行
	/// \return 返回程序将要运行的下一个任务，若为空，调度程序自由选择下一个任务
	virtual tbb::task* execute() /*override*/;


};
first_task::~first_task()
{

}

tbb::task* first_task::execute()
{
	cout << "Hello World!\n";
	return NULL;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Fibonacci Numbers
long SerialFib(long n)
{
	if (n < 2)
		return n;
	else
	{
		return SerialFib(n - 1) + SerialFib(n - 2);
	}
}


//The real work is inside struct FibTask. Its definition is shown below.
class FibTask : public tbb::task 
{
private:
	const long n;
	long* const sum;

public:
	FibTask(long n_, long* sum_) 
	    :n(n_),sum(sum_){

	}

	tbb::task* execute()
	{
		if ( n < 10 )
		{
			*sum = SerialFib(n);
		}
		else
		{
			long x, y;
			FibTask& a = *new(allocate_child()) FibTask(n - 1, &x);
			FibTask& b = *new(allocate_child()) FibTask(n - 2, &y);

			// Set ref_count to two children plus one for the wait.
			set_ref_count(3);
			spawn(b);

			// Start a running and wait for all children ( a and b ).
			spawn_and_wait_for_all(a);

			// Do the sum
			*sum = x + y;
		}

		return NULL;
	}

};



//The top-level code for the parallel task-based version is:
long ParallelFib(long n)
{
	long sum;
	FibTask& a = *new(tbb::task::allocate_root()) FibTask(n, &sum);
	tbb::task::spawn_root_and_wait(a);

	return sum;
}

//////////////////////////////////////////////////////////////////////////


void TBBTest()
{
	//// 1
	//tbb::parallel_for(0, 10000, [](int num) {cout << num << ":hello tbb " << endl; });

	//// 2
	//tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);

 //   first_task& f1 = *new(tbb::task::allocate_root()) first_task();

	//tbb::task::spawn_root_and_wait(f1);

	//3
	tbb::tick_count start = tbb::tick_count::now();
	long l = ParallelFib(10);
	tbb::tick_count end = tbb::tick_count::now();
	printf("tick count = %f\n", (end - start).seconds());
	int j = 0;

}




