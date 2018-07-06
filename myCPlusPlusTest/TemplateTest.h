/*!
* \file 	TemplateTest.h
* \brief	
*
*	ģ����Գ���
*
* \author	lwm email:luowm@greytech.org
* \version  1.0.0
* \date		2018/04/27
*/
#ifndef _H_TEMPLATETEST_H_
#define _H_TEMPLATETEST_H_
#include <iostream>
#include <vector>
//#include "UtilitiesTest.h"
//#include <memory>
using namespace std;

class myError
{
public:
	explicit myError(const string&  strErr)
	              :m_str(strErr) {

	}

private:
	string m_str;
};

/*template <class T>*/
class MyClass 
{
public:


	/// \brief �Ƚ��������е����ֵ
	/// \param a [in]��a
	/// \param b [in]��b
	/// \return �������ֵ
	template <class T>
	const T& max(const T& a,const T& b, T&c) throw (myError)
	{
		c = T();

		return a > b ? a : b;
	}

	/// \brief /*���ָ�������ַ���*/
	/// \param 
	/// \param 
	/// \param 
	/// \param 
	template <class T, class U>
	void split(const T& src
		       , const U& separator
		       , vector<T>& dest
		      , bool bNoEmptyStr = false )
	{
		T str = src;
		T substring;
		T::size_type start = 0, index;

		do
		{
			index = str.find_first_of(separator, start);
			if (index != T::npos)
			{
				substring = str.substr(start, index - start);
				if (substring.empty())
				{
					if (!bNoEmptyStr)
					{
						dest.push_back(substring);
					}
				}
				else
				{
					dest.push_back(substring);
				}

				start = str.find_first_not_of(separator, index);
				if (start == T::npos) return;
			}
		} while (index != T::npos);

		//the last token
		substring = str.substr(start);

		if (substring.empty())
		{
			if (!bNoEmptyStr)
			{
				dest.push_back(substring);
			}
		}
		else
		{
			dest.push_back(substring);
		}
	}

};

class Stack
{
public:
	explicit Stack(int j)
       	  :m_i(j){

	}

	~Stack()
	{
		int i = 0;
	}

private:
	int m_i;

};

class Car
{
public:
    Car()
	{

	}


	virtual ~Car()
	{

	}
};

class Cabriolet : public Car
{

};


class Limousine : public Car
{

};

//
class MyConstClass
{
public:
	static const int nNum = 100;
	int elems[nNum];

};

const int MyConstClass::nNum;
//

// �쳣
class MyProblem : public std::exception
{
public:
	MyProblem(const char* strError)
	            : m_strError(strError)
	{

	}
	~MyProblem()
	{

	}

	virtual char const* what() const override
	{
		return m_strError.data();
	}

private:
	string m_strError;    // �쳣��Ϣ
};



//
////����ģ��
//template<class T>
//bool IsEqual1(T t1, T t2) {
//	std::cout << "in template<class T>..." << std::endl;
//	return t1 == t2;
//}
//
//template<> //����ģ���ػ�
//bool IsEqual1<char *>(char *t1, char *t2); /*{
//	std::cout << "in special template< >..." << std::endl;
//	return strcmp(t1, t2) == 0;
//}*/

//// ģ�嶨��Ӧ�÷���ͷ�ļ��У�
//template<typename T>
//int g(T, T x = 42)
//{
//	return x;
//}
//
//// �ػ�������ֹģ�����ʵ��������Ϊ�˱�������ظ����壬�Ͳ��ܰѶ����������
//template<>
//int g<int>(int, int y);


// general version
template<class T>
class Compare
{
public:
	static bool IsEqual(const T& lh, const T& rh)
	{
		std::cout << "in the general class..." << std::endl;
		return lh == rh;
	}
};



// specialize for float
template<>
class Compare<float>
{
public:
	static bool IsEqual(const float& lh, const float& rh)
	{
		std::cout << "in the float special class..." << std::endl;

		return std::abs(lh - rh) < 10e-3;
	}
};

// specialize for double
template<>
class Compare<double>
{
public:
	static bool IsEqual(const double& lh, const double& rh)
	{
		std::cout << "in the double special class..." << std::endl;

		return std::abs(lh - rh) < 10e-6;
	}
};


// stl TEST
template <class T>
inline void PRINT_ELEMENTS(const T& coll, const char* optcstr = "")
{
	/*typename*/ T::const_iterator pos;

	std::cout << optcstr;

	for ( pos = coll.cbegin()
		; coll.cend()!=pos
		 ; ++pos )
	{
		std::cout << *pos << ' ';

	}

	std::cout << std::endl;
}
//


// �����
#include <queue>
#include <memory>

template< typename T >
class CObjectPool
{
public:
	CObjectPool(size_t nChunkSize = kDefaultChunkSize)
	{
		//[1] ��������Ч��
		if ( 0== nChunkSize )
		{
			throw invalid_argument("Chunk size must be postive");
		}
		else
		{
			mChunkSize = nChunkSize;
		}

		//[2] ��������ڴ��
		allocateChunk();


	}


	using Object = std::shared_ptr<T>;
	/// \brief �̳߳ط��ض����ȡ
	/// \return �̳߳ط��ض���
	Object acquireObject()
	{
		//[1] �������Ϊ�գ����ӷ���
		if ( mFreeList.empty() )
		{
			allocateChunk();
		}
		
		//[2] ȡ������ض���ǰ�������
		//<1> ȡ��
		std::unique_ptr pObj = std::move(mFreeList.front());
		mFreeList.pop();

		//<2> ת��Ϊ���ü���ָ��,�Զ�����������������ʱ����ջض���
		Object pSmartObj = (pObj.release(), [this](T* t)
		{
			mFreeList.push(std::unique_ptr<T>(t));
		});

		return pSmartObj;

	}

private:
	std::queue<std::unique_ptr<T>> mFreeList;   // ����ؿ��ж������
	size_t mChunkSize;                          // ����ؿ��С 
	static const size_t kDefaultChunkSize = 10; // Ĭ��ÿ�����·������εĿ��С

	/// \brief �����
	void allocateChunk( )
	{
		for ( size_t i = 0; i<mChunkSize; ++i )
		{
			mFreeList.emplace(std::make_unique<T>());
		}
	}
};

//

#endif // _H_TEMPLATETEST_H_