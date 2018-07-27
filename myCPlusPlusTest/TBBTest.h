/*!
* \file 	TBBTest.h
* \brief	
*
*	Intel的Threading Building Blocks(Intel TBB) 线程池库测试
*
* \author	lwm email:luowm@greytech.org
* \version  1.0.0
* \date		2018/07/03
*/
#ifndef _H_TBBTEST_H_
#define _H_TBBTEST_H_




void TBBTest();


// 移动语义测试
class Spreadsheet
{
public:
	// Move constructor
	Spreadsheet(Spreadsheet&& src) noexcept
		: mWidth(src.mWidth)
	    , mHeight(src.mHeight)
	    , mCells(src.mCells) {
		// Shallow copy of data
		

		// Reset the source object, because ownership has been moved!
		src.mWidth = 0;
		src.mHeight = 0;
		src.mCells = 0;
	}

	// Move assignment
	Spreadsheet& operator=(Spreadsheet&& rhs) noexcept
	{
		// Check for self-assignment
		if ( this == &rhs )
		{
			return *this;
		}

		//// free the old memory
		//freeMemory()

		// Shallow copy of data
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;
		mCells = rhs.mCells;

		// Reset the source object, because ownership has been moved!
		rhs.mWidth = 0;
		rhs.mHeight = 0;
		rhs.mCells = 0;

		return *this;
	}


private:
	int mWidth;
	int mHeight;
	int mCells;

};
//

#endif // _H_TBBTEST_H_
