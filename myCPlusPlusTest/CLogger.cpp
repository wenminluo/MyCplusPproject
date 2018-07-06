#include "CLogger.h"
#include <fstream>
#include <iostream>

///// \brief 获取当前系统时间
///// \return 当前系统时间
//std::wstring getCurrentSystemTime()
//{
//	auto tt = std::chrono::system_clock::to_time_t
//	(std::chrono::system_clock::now());
//	struct tm ptm;
//	localtime_s(&ptm, &tt);
//
//	wchar_t date[60] = { 0 };
//	swprintf_s(date, L"%d-%02d-%02d %02d:%02d:%02d",
//		(int)ptm.tm_year + 1900, (int)ptm.tm_mon + 1, (int)ptm.tm_mday,
//		(int)ptm.tm_hour, (int)ptm.tm_min, (int)ptm.tm_sec);
//
//	return std::wstring(date);
//}

Logger::Logger()
         :mExit(false){
	mThread = std::thread{ &Logger::processEntries,this };
}

void Logger::log(const wstring& entry)
{
	// Lock mutex and add entry to the queue.
	std::lock_guard<std::mutex> lock(mMutex);
	mQueue.push(entry);

	// Notify condition variable to wake up thread.
	mCondVar.notify_all();
}


Logger::~Logger()
{
	{
		//std::unique_lock<std::mutex> lock(mMutex);

		// Gracefully shut down the thread by setting mExit
		// to true and notifying the thread.
		mExit = true;

		// Notify condition variable to wake up thread.
		mCondVar.notify_all();
	}
	
	// Wait until thread is shut down. This should be outside the above code
	// block because the lock on mMutex must be released before calling join()!
	mThread.join();


}

void Logger::processEntries()
{
	// Open log file.
	std::wofstream ofs(L"log.txt");
	if ( ofs.fail() )
	{
		std::wcerr << L"Failed to open logfile." << std::endl;
		return;
	}



	// Start processing loop.
	std::unique_lock<std::mutex> lock(mMutex);

	while (!mExit)
	{

		//// test
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
		// Wait for a notification.
		mCondVar.wait(lock, [this]() {return !mQueue.empty(); });
		

		
		// Condition variable is notified, so something might be in the queue.
		lock.unlock();
		while (true)
		{
			lock.lock();
			if ( mQueue.empty() )
			{
				break;
			}
			else
			{
				ofs /*<< getCurrentSystemTime()<<": "*/ << mQueue.front() << std::endl;
				mQueue.pop();
			}
			lock.unlock();
		}
		if ( mExit )
		{
			break;
		}

	}

}