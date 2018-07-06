
/*!
* \file 	UtilitiesTest.h
* \brief	
*
*	通用工具程序库测试
*
* \author	lwm email:luowm@greytech.org
* \version  1.0.0
* \date		2018/05/03
*/
#ifndef _H_UTILITIESTEST_H_
#define _H_UTILITIESTEST_H_
#include <utility>
#include <string>
//////////////////////////////////////////////////////////////////////////
#include <climits>
#include <limits>
#include <cfloat>
#include <float.h>
//////////////////////////////////////////////////////////////////////////



using namespace std;

typedef pair<int, string> Ret;

Ret PairTest();


void Shared_ptrTest();



//class Parent
//{
//public:
//	Parent()
//	{
//
//	}
//
//	~Parent()
//	{
//		int j = 0;
//	}
//
//	shared_ptr<Child> child;
//};


/// \brief 极值
namespace std1
{
	// 基础类
	template< class T >
	class numeric_limits
	{
	public:
		static const bool is_specialized = false;
	};

	// 整形模板特化
	template<> class numeric_limits<int>
	{
	public:
		static const bool is_specialized = true;

		static int min() throw()
		{
			return -2147483647;
		}

		static int max() throw()
		{
			return 2147483647;
		}

		static const int digits = 31;
	};

}
//




#endif // _H_UTILITIESTEST_H_