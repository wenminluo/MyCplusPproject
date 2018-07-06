/*!
* \file 	STLTest.h
* \brief	
*
*	stl测试代码
*
* \author	lwm email:luowm@greytech.org
* \version  1.0.0
* \date		2018/05/07
*/
#ifndef _H_STLTEST_H_
#define _H_STLTEST_H_
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

namespace STLTEST
{
	void RQTest();

	/// \brief stl算法测试
	void AlgorithmTest();

	/// \brief STL迭代器测试
	void IteratorTest();

	/// \brief 打印值
	void PrintNValue(int nval);
	void PrintStrValue(const string& strVal);

	/// \brief 仿函数测试
	template <int theValue>
	void add(int& elem)
	{
		elem += theValue;
	}
	void f1();

	/// \brief 将所有指定值元素移除
	void RemoveTest();

	/// \brief 文件迭代器写测试 
	void FileWriteIteratorTest();

	/// \brief 流迭代器初始化容器测试
	void IteartorInitVTest();

	/// \brief 容器操作函数测试
	void STLContainerTest();
	
	
	/// \brief 容器list测试
	void STLListTest();


    /// \brief 容器set测试
	void STLSetTest();
    

	template< class T >
	class RuntimeCmp
	{
	public:
		enum cmp_mode { normal, reverse };

		RuntimeCmp( cmp_mode m = normal )
			:mode(m)
		{

		}

		// comparision of elements
		bool operator()(const T& t1, const T& t2)
		{
			return mode == normal ? t1 < t2 : t2 < t1;
		}

		// comparision of sorting criteria
		bool operator==(const RuntimeCmp& rc)
		{
			return mode == rc.mode;
		}

	private:
		cmp_mode mode;

	};

}







#endif // _H_STLTEST_H_

