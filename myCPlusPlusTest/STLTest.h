/*!
* \file 	STLTest.h
* \brief	
*
*	stl���Դ���
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

	/// \brief stl�㷨����
	void AlgorithmTest();

	/// \brief STL����������
	void IteratorTest();

	/// \brief ��ӡֵ
	void PrintNValue(int nval);
	void PrintStrValue(const string& strVal);

	/// \brief �º�������
	template <int theValue>
	void add(int& elem)
	{
		elem += theValue;
	}
	void f1();

	/// \brief ������ָ��ֵԪ���Ƴ�
	void RemoveTest();

	/// \brief �ļ�������д���� 
	void FileWriteIteratorTest();

	/// \brief ����������ʼ����������
	void IteartorInitVTest();

	/// \brief ����������������
	void STLContainerTest();
	
	
	/// \brief ����list����
	void STLListTest();


    /// \brief ����set����
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

