/*!
* \file 	ThreadTaskPool.h
* \brief	
*
*	�ִ�c++���߳������
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
		Idle = 0,       //����
		Normal = 5,     //��ͨ
		High = 10,       //��
		Realtime = 50,   //ʵʱ
	};
	//����Ԥ���
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
	E_Priority   priority_ = Normal;      // �������ȼ�
	TASKARG     arg_;                     // �������
	std::string taskName_;                // ��������

	//bool bAutoRelease_ = true;            // �Ƿ��Զ�ɾ��
};

struct PCmp
{
	bool operator () ( const std::shared_ptr<ITask> x
		               , const std::shared_ptr<ITask> y )
	{
		return x->GetPriority() < y->GetPriority();
	}
};

//��������
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

// �����߳�
class CThreadTask 
{
public:
	CThreadTask( ThreadTaskPool* pool );
	~CThreadTask( )
	{

	}


	/// \brief ֹͣ����
	void Stop() 
	{
		stop_.store(true);
	}

	/// \brief ��ͣ����
	bool Pause()
	{
		pause_.store(true);
		return true;
	}

	/// \brief ��ʼ����
	bool Start()
	{
		pause_.store(false);
		con_.notify_all();
		return true;
	}


	/// \brief ����������ִ��,�����ȴ�ִ�����
	void Join()
	{
		if (thread_.joinable())
			thread_.join();
	}

	void Run( );


private:
	ThreadTaskPool* threadpool_;                // �̳߳�ָ�����
	std::thread thread_;                        // �̶߳���
	std::atomic_bool stop_;                     // �Ƿ�ֹͣ�߳�

	std::atomic_bool pause_;                    // �Ƿ���ͣ�߳�
	std::mutex mutex_task_;                     // �߳���������������
	std::mutex mutex_pause_;                    // �߳���ͣ����������

	std::condition_variable con_;               // �߳�������������
	
	typedef std::chrono::duration<int> seconds_type;
	seconds_type seconds_wait;                  // �����������ȴ�  
};
//

// �̳߳�
class ThreadTaskPool 
{
public:
	ThreadTaskPool(int threadNum = 0
		, int wait_seconds = 1);
	~ThreadTaskPool();


	// ��ֹ�����͸���
	ThreadTaskPool(const ThreadTaskPool& other) = delete;
	const ThreadTaskPool& operator=(const ThreadTaskPool& other) = delete;
	//

	/// \brief ��ͣ�̳߳�
	/// \return �ɹ�true,ʧ��false
	bool Pause();

	/// \brief ��ʼ�̳߳�
	/// \return �ɹ�true,ʧ��false
	bool Start();

	/// \brief �������
	/// \param �������ָ��
	void addTask(std::shared_ptr<ITask> pTask);


	/// \brief ���������������һ������
	std::shared_ptr<ITask> getTask();

	/// \brief ��ȡ����������������
	/// \return ����������������
	size_t taskNum( ) /*const*/;

private:

	std::mutex  task_mutex_;                            // ��������� 
	std::condition_variable cond_;                      // �������� 
	TaskContainer tasks_;                               // �������

	std::vector<std::unique_ptr<CThreadTask>> threads_; // �̳߳���������̼߳���


	/// \brief �ͷ��̳߳��߳���Դ														
	void releaseThreads();
};


#endif _H_THREADTASKPOOL_H_
