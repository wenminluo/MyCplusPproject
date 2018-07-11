#include "ThreadTaskPool.h"


// �߳�
CThreadTask::CThreadTask(ThreadTaskPool* pool)
                : threadpool_(pool)
	            , stop_(false)
	            , pause_(true)
	            , seconds_wait(1)
{
	//[1] �����߳�
	thread_ = std::thread(&CThreadTask::Run, this);
	thread_.detach();
		
}

void CThreadTask::Run()
{
	while (true
		   &&threadpool_)
	{
		
		//<1> �Ƿ�ֹͣ�߳� 
		if ( stop_.load() )
		{
			break;
		}

		//<2> �Ƿ���ͣ�߳�
		if (pause_.load())
		{
			std::unique_lock<std::mutex> ulk(mutex_pause_);
			con_.wait(ulk, [this] { return !(pause_.load()); });
		}

		//<3> ���̳߳�����һ������ 
		std::shared_ptr<ITask> pTask = NULL;
		{
			std::unique_lock<std::mutex> ulk(mutex_task_);
			con_.wait_for(ulk, seconds_wait, [this, &pTask] { pTask = threadpool_->getTask(); return pTask != NULL; });
		}
		

		//<4> �Ƿ�ֹͣ�߳�
		if (stop_.load())
		{
			break;
		}

		//<5> �Ƿ���ͣ�߳�
		if (pause_.load())
		{
			std::unique_lock<std::mutex> ulk(mutex_pause_);
			con_.wait(ulk, [this] { return !(pause_.load()); });
		}

		//<6> ִ������ 
		if( pTask )
			pTask->run();

	}

}


//

// �̳߳�
ThreadTaskPool::ThreadTaskPool( int threadNum /*= 0*/
	                           , int wait_seconds /*= 1*/ )
{
	//[1] Ĭ�Ͽ������߳����� 
	if (threadNum <= 0)
	{
		threadNum = std::thread::hardware_concurrency();
		threadNum = (threadNum == 0 ? 2 : threadNum);
	}

	//[2] �����߳�
	for ( size_t i = 0; i <threadNum; ++i )
	{
		threads_.emplace_back(std::make_unique<CThreadTask>( this ));
	}

	////[3] �����߳�
	//Start();
}


ThreadTaskPool::~ThreadTaskPool( )
{
	//[1] �ͷ��̳߳��߳���Դ
	releaseThreads();

}


bool ThreadTaskPool::Pause( )
{
	//[1] ����ֵ
	bool bRet(true);

	//[2] ��ͣ�����߳�
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
	//[1] ����ֵ
	bool bRet(true);

	//[2] ��ʼ�����߳�
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
	//[1] ���е��߳���������,�����е��̵߳ȴ������������
	//<1> ��ֹͣ��������
	for_each(threads_.begin(), threads_.end(), [](std::unique_ptr<CThreadTask>& pThread)
	{
		if ( pThread )
			pThread->Stop();
		
	});

	//<2> ��һ�ȴ������߳�ִ�����
	for_each(threads_.begin(), threads_.end(), [](std::unique_ptr<CThreadTask>& pThread)
	{
		if (pThread)
		{
			pThread->Join();
		}
		
	});

	//<3> �ͷ��̳߳��߳�
	threads_.clear();
	threads_.shrink_to_fit();

}

//



