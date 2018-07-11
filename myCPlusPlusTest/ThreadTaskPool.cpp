#include "ThreadTaskPool.h"


// 线程
CThreadTask::CThreadTask(ThreadTaskPool* pool)
                : threadpool_(pool)
	            , stop_(false)
	            , pause_(true)
	            , seconds_wait(1)
{
	//[1] 启动线程
	thread_ = std::thread(&CThreadTask::Run, this);
	thread_.detach();
		
}

void CThreadTask::Run()
{
	while (true
		   &&threadpool_)
	{
		
		//<1> 是否停止线程 
		if ( stop_.load() )
		{
			break;
		}

		//<2> 是否暂停线程
		if (pause_.load())
		{
			std::unique_lock<std::mutex> ulk(mutex_pause_);
			con_.wait(ulk, [this] { return !(pause_.load()); });
		}

		//<3> 从线程池申请一个任务 
		std::shared_ptr<ITask> pTask = NULL;
		{
			std::unique_lock<std::mutex> ulk(mutex_task_);
			con_.wait_for(ulk, seconds_wait, [this, &pTask] { pTask = threadpool_->getTask(); return pTask != NULL; });
		}
		

		//<4> 是否停止线程
		if (stop_.load())
		{
			break;
		}

		//<5> 是否暂停线程
		if (pause_.load())
		{
			std::unique_lock<std::mutex> ulk(mutex_pause_);
			con_.wait(ulk, [this] { return !(pause_.load()); });
		}

		//<6> 执行任务 
		if( pTask )
			pTask->run();

	}

}


//

// 线程池
ThreadTaskPool::ThreadTaskPool( int threadNum /*= 0*/
	                           , int wait_seconds /*= 1*/ )
{
	//[1] 默认开启的线程数量 
	if (threadNum <= 0)
	{
		threadNum = std::thread::hardware_concurrency();
		threadNum = (threadNum == 0 ? 2 : threadNum);
	}

	//[2] 创建线程
	for ( size_t i = 0; i <threadNum; ++i )
	{
		threads_.emplace_back(std::make_unique<CThreadTask>( this ));
	}

	////[3] 开启线程
	//Start();
}


ThreadTaskPool::~ThreadTaskPool( )
{
	//[1] 释放线程池线程资源
	releaseThreads();

}


bool ThreadTaskPool::Pause( )
{
	//[1] 返回值
	bool bRet(true);

	//[2] 暂停所有线程
	for_each(threads_.begin(), threads_.end(), [&](std::unique_ptr<CThreadTask>& pThread)
	{
		if (pThread)
		{
			bool b = pThread->Pause();
			bRet = bRet&&b;
		}
			
	});

	return bRet;
}


bool ThreadTaskPool::Start( )
{
	//[1] 返回值
	bool bRet(true);

	//[2] 开始所有线程
	for_each(threads_.begin(), threads_.end(), [&](std::unique_ptr<CThreadTask>& pThread)
	{
		if (pThread)
		{
			bool b = pThread->Start();
			bRet = bRet&&b;
		}

	});

	return bRet;
}

void ThreadTaskPool::addTask(std::shared_ptr<ITask> pTask)
{
	if ( pTask )
	{
		std::lock_guard<std::mutex> glk(task_mutex_);
		tasks_.push(pTask);
	}
}

std::shared_ptr<ITask> ThreadTaskPool::getTask()
{
	std::shared_ptr<ITask> pTask = NULL;

	if ( !tasks_.empty() )
	{
		std::lock_guard<std::mutex> glk(task_mutex_);
		pTask = tasks_.top();
		tasks_.pop();
	}
	
	return pTask;
}

size_t ThreadTaskPool::taskNum() /*const*/
{
	std::lock_guard<std::mutex> glk(task_mutex_);
	return tasks_.size();
}


// private
void ThreadTaskPool::releaseThreads()
{
	//[1] 空闲的线程立即销毁,运行中的线程等待其完成再销毁
	//<1> 先停止所有任务
	for_each(threads_.begin(), threads_.end(), [](std::unique_ptr<CThreadTask>& pThread)
	{
		if ( pThread )
			pThread->Stop();
		
	});

	//<2> 逐一等待所有线程执行完毕
	for_each(threads_.begin(), threads_.end(), [](std::unique_ptr<CThreadTask>& pThread)
	{
		if (pThread)
		{
			pThread->Join();
		}
		
	});

	//<3> 释放线程池线程
	threads_.clear();
	threads_.shrink_to_fit();

}

//



