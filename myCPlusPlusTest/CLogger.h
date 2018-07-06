/*!
* \file 	CLogger.h
* \brief	
*
*	c++11线程安全日志类
*
* \author	lwm email:luowm@greytech.org
* \version  1.0.0
* \date		2018/07/02
*/
#ifndef _H_CLOGGER_H_
#define _H_CLOGGER_H_
#include <string>
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>

using std::wstring;


class Logger
{

public:
	/// \brief Starts a background thread writing long entries to a file.
	Logger();

	// Gracefully shut down background thread.
	virtual ~Logger();

	/// \brief Prevent copy construction and assignment.
	Logger(const Logger& src) = delete;
	Logger& operator=(const Logger& rhs) = delete;

	/// \brief Add log entry to the queue.
	void log(const wstring& entry);
	
private:
	/// \brief The function running in the background thread.
	void processEntries();

	/// Mutex and condition variable to protect access to the queue.
	std::mutex mMutex;
	std::condition_variable mCondVar;
	std::queue<wstring> mQueue;

	// The background thread.
	std::thread mThread;
	// Boolean telling the background thread to terminate.
	std::atomic<bool> mExit;


};

#endif // _H_CLOGGER_H_

