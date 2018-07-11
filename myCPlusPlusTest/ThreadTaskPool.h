/*!
* \file 	ThreadTaskPool.h
* \brief	
*
*	现代c++，线程任务池
*
* \author	lwm email:business122@163.com
* \version  1.0.0
* \date		2018/07/10
*/
#ifndef _H_THREADTASKPOOL_H_
#define _H_THREADTASKPOOL_H_

#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>

typedef void* TASKARG;

class ITask
{
public:
	enum E_Priority
	{
		Idle = 0,       //空闲
		Normal = 5,     //普通
		High = 10,       //高
		Realtime = 50,   //实时
	};
	//重载预算符
	friend bool operator<(ITask  &lv, ITask &rv)
	{
		return lv.priority_ < rv.priority_;
	}

	ITask()
	   :arg_(NULL){

	}

	virtual ~ITask()
	{

	}

	void setArg(TASKARG arg) 
	{
		arg_ = arg;
	}

	void setName(const std::string& strName) 
	{
		taskName_ = strName;
	}

	virtual int run() = 0;

	void SetPriority(E_Priority ePriority) 
	{
		priority_ = ePriority;
	}

	E_Priority GetPriority() const
	{
		return priority_;
	}

	//void SetAutoRelease(bool bAutoRelease) 
	//{
	//	bAutoRelease_ = bAutoRelease;
	//}


	//bool IsAutoRelease() const 
	//{
	//	return bAutoRelease_;
	//}

	//virtual void release() { delete this; }

protected:
	E_Priority   priority_ = Normal;      // 任务优先级
	TASKARG     arg_;                     // 任务参数
	std::string taskName_;                // 任务名称

	//bool bAutoRelease_ = true;            // 是否自动删除
};

struct PCmp
{
	bool operator () ( const std::shared_ptr<ITask> x
		               , const std::shared_ptr<ITask> y )
	{
		return x->GetPriority() < y->GetPriority();
	}
};

//任务容器
class TaskContainer
{
public:
	TaskContainer() {};
	~TaskContainer() {};
	void push(std::shared_ptr<ITask> t) 
	{
		task_container_.push(t);
	}

	std::shared_ptr<ITask> top() 
	{
		if (!task_container_.empty())
			return task_container_.top();
		else
			return NULL;
		
	}

	void pop( ) 
	{
		if ( !task_container_.empty() )
			task_container_.pop();
		
		
	}

	bool empty() 
	{
		return task_container_.empty();
	}

	std::priority_queue< std::shared_ptr<ITask>, std::vector<std::shared_ptr<ITask>>, PCmp >::size_type size() const 
	{
		return task_container_.size();
	}

private:
	std::priority_queue<std::shared_ptr<ITask>, std::vector<std::shared_ptr<ITask>>, PCmp > task_container_;
};


class ThreadTaskPool;

// 任务线程
class CThreadTask 
{
public:
	CThreadTask( ThreadTaskPool* pool );
	~CThreadTask( )
	{

	}


	/// \brief 停止任务
	void Stop() 
	{
		stop_.store(true);
	}

	/// \brief 暂停任务
	bool Pause()
	{
		pause_.store(true);
		return true;
	}

	/// \brief 开始任务
	bool Start()
	{
		pause_.store(false);
		con_.notify_all();
		return true;
	}


	/// \brief 若任务仍在执行,阻塞等待执行完毕
	void Join()
	{
		if (thread_.joinable())
			thread_.join();
	}

	void Run( );


private:
	ThreadTaskPool* threadpool_;                // 线程池指针对象
	std::thread thread_;                        // 线程对象
	std::atomic_bool stop_;                     // 是否停止线程

	std::atomic_bool pause_;                    // 是否暂停线程
	std::mutex mutex_task_;                     // 线程任务阻塞互斥量
	std::mutex mutex_pause_;                    // 线程暂停阻塞互斥量

	std::condition_variable con_;               // 线程阻塞条件变量
	
	typedef std::chrono::duration<int> seconds_type;
	seconds_type seconds_wait;                  // 互斥锁阻塞等待  
};
//

// 线程池
class ThreadTaskPool 
{
public:
	ThreadTaskPool(int threadNum = 0
		, int wait_seconds = 1);
	~ThreadTaskPool();


	// 禁止拷贝和复制
	ThreadTaskPool(const ThreadTaskPool& other) = delete;
	const ThreadTaskPool& operator=(const ThreadTaskPool& other) = delete;
	//

	/// \brief 暂停线程池
	/// \return 成功true,失败false
	bool Pause();

	/// \brief 开始线程池
	/// \return 成功true,失败false
	bool Start();

	/// \brief 添加任务
	/// \param 任务对象指针
	void addTask(std::shared_ptr<ITask> pTask);


	/// \brief 从任务队列中申请一个任务
	std::shared_ptr<ITask> getTask();

	/// \brief 获取任务队列里的任务数
	/// \return 任务队列里的任务数
	size_t taskNum( ) /*const*/;

private:

	std::mutex  task_mutex_;                            // 任务队列锁 
	std::condition_variable cond_;                      // 条件阻塞 
	TaskContainer tasks_;                               // 任务队列

	std::vector<std::unique_ptr<CThreadTask>> threads_; // 线程池所管理的线程集合


	/// \brief 释放线程池线程资源														
	void releaseThreads();
};


#endif _H_THREADTASKPOOL_H_
