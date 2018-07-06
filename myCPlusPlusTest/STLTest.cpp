#include "STLTest.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

// 标准模板库
#include <vector>
// 双向队列
#include <deque>
// 链表
#include <list>
//set
#include <set>
//string
#include <string>
#include <iterator>
#include <functional>
#include <string>
#include <map>
using std::list;
using std::deque;
using std::vector;
using std::set;
using std::string;
using std::istream_iterator;
using std::ostream_iterator;
using std::cin;
using std::negate;
using std::multiplies;
using std::bind2nd;
using std::ifstream;
using std::ofstream;
using std::string;
using std::deque;
using std::greater;
using std::less;
using std::pair;
using std::multiset;
//

// 容器配接器
// 堆栈(先进后出)
#include <stack>
// 队列(先进先出,适合做缓冲区)
#include <queue>
// 优先级队列
// PriorityQueue
//
using std::stack;
using std::queue;

// algorithm
#include <algorithm>

// iterator
#include <iterator>



struct MyStruct
{
	MyStruct(int i)
		: j(i) {

	}

	int j;

};

namespace STLTEST
{
	void RQTest()
	{
		// vector
		vector<float> vectorTest;
		//vectorTest.push_back(1.0);
		vectorTest.emplace_back(2.0);

		vector<MyStruct> v1;
		MyStruct m1(1);
		//v1.push_back(1);
		v1.emplace_back(1);


		// 双向队列
		deque<float> dQueTest;
		dQueTest.push_front(2.0);
		dQueTest.push_front(1.0);
		dQueTest.emplace_back(3.0);

		// 链表
		list<float> listTest;
		//listTest.back();
		//listTest.pop_back();

		// 堆栈
		stack<double> stackTest;
		stackTest.emplace(2.0);
		double d = stackTest.top();


		// 队列
		queue<double> queueTest;

		//set
		//set<double, greater<double>> zz;

	}

	/// \brief 迭代器配接器测试
	void IteratorAdapters()
	{
		list<int> coll1;

		// insert
		for (int i = 1; i < 9; ++i)
		{
			coll1.emplace_back(i);
		}

		// copy the elements of coll1 into coll2 by appending them
		vector<int> coll2;
		copy(coll1.begin()
			, coll1.end()
			, back_inserter(coll2));


	}


	void AlgorithmTest()
	{
		vector<int> coll;
		vector<int>::iterator pos;

		// insert datas
		coll.emplace_back(2);
		coll.emplace_back(5);
		coll.emplace_back(4);
		coll.emplace_back(1);
		coll.emplace_back(6);
		coll.emplace_back(3);
		//

		//find and print minium and maxium elements
		pos = min_element(coll.begin(), coll.end());
		cout << "min: " << *pos << endl;

		pos = max_element(coll.begin(), coll.end());
		cout << "max: " << *pos << endl;

		//sort all elements
		sort(coll.begin(), coll.end());

		//find the first element with value 3
		pos = find(coll.begin(), coll.end(), 3);

		// reverse
		reverse(pos, coll.end());

		//print all elements
		for (pos = coll.begin(); pos != coll.end(); ++pos)
		{
			cout << *pos << ' ';
		}
		cout << endl;


		// 双向队列测试 
		deque<double> d1;
		d1.emplace_front(1);
		d1.emplace_front(7);
		d1.emplace_back(3);
		d1.emplace_back(5);
		d1.emplace_back(9);
		d1.emplace_back(8);

		list<double> d2(d1.size());
		/*d2.reserve(6);*/
		/*d2.resize(6);*/
		//d2.emplace_back(1);
		//d2.emplace_back(7);
		//d2.emplace_back(3);
		//d2.emplace_back(5);
		//d2.emplace_back(9);
		//d2.emplace_back(8);

		for (auto cIt = d2.cbegin()
			; d2.cend() != cIt
			; ++cIt)
		{
			cout << *cIt << endl;
		}

		if (equal(d1.cbegin(), d1.cend(), d2.cbegin()))
		{
			int j = 0;
		}

		copy(d1.begin(), d1.end(), d2.begin());

		for (auto cIt = d2.cbegin()
			; d2.cend() != cIt
			; ++cIt)
		{
			cout << *cIt << endl;
		}

		int j = 0;


	}

	void IteratorTest()
	{
		vector<string> coll;


		////
		//copy(istream_iterator<string>(cin)
		//	, istream_iterator<string>()
		//	, back_inserter(coll));

		// sort elements
		sort(coll.begin(), coll.end());

		//// print
		//unique_copy(coll.begin()
		//	, coll.end()
		//	, ostream_iterator<string>(cout, "\n"));

		////////////////////////////////////////////////////////////////////////////

		// Used in conjunction with copy algorithm
		// to put elements into a vector read from cin
		vector<int> vec(4);
		vector <int>::iterator Iter;

		cout << "Enter 4 integers separated by spaces & then\n"
			<< " a character ( try example: '2 4 6 8 a' ): ";
		istream_iterator<int> intvecRead(cin);

		// Default constructor will test equal to end of stream
		// for delimiting source range of vecor
		copy(intvecRead, istream_iterator<int>(), vec.begin());
		cin.clear();

		cout << "vec = ";
		for (Iter = vec.begin(); Iter != vec.end(); Iter++)
			cout << *Iter << " "; cout << endl;
		////////////////////////////////////////////////////////////////////////////



	}

	void f1()
	{
		vector<int> coll(10);
		for (int i = 0; i < 10; ++i)
		{
			coll[i] = i;
		}

		// 打印值
		//copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, "\n"));
		for_each(coll.cbegin(), coll.cend(), /*STLTEST::PrintNValue*/[](int n) {cout << n << endl; });

		// 增加值

		for_each(coll.begin(), coll.end(), add<10>);

		// 打印值
		//copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, "\n"));
		for_each(coll.cbegin(), coll.cend(), /*STLTEST::PrintNValue*/[](int n) {cout << n << endl; });

		// 设为相反值
		transform(coll.begin(), coll.end(), coll.begin(), negate<int>());

		// 打印值
		//copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, "\n"));
		for_each(coll.cbegin(), coll.cend(), /*STLTEST::PrintNValue*/[](int n) {cout << n << endl; });


		// 每个值2次方
		list<int> coll1;
		transform(coll.begin(), coll.end(), /*coll.begin()*/front_inserter(coll1), bind2nd(multiplies<int>(), 10));

		// 打印值
		//copy(coll1.cbegin(), coll1.cend(), ostream_iterator<int>(cout, "\n"));
		for_each(coll1.cbegin(), coll1.cend(), /*STLTEST::PrintNValue*/[](int n) {cout << n << endl; });

		int j = 0;

	}

	void PrintNValue(int nval)
	{
		cout << nval << endl;
	}

	void PrintStrValue(const string& strVal)
	{
		cout << strVal << endl;
	}


	void RemoveTest()
	{
		
		vector<int> vStr(6, 5);

		vStr.emplace_back(6);
		vStr.emplace_back(7);
		vStr.emplace_back(8);
		vStr.emplace_back(9);
		vStr.emplace_back(10);
		vStr.emplace_back(11);
		vStr.emplace_back(12);



		//for_each(vStr.cbegin(), vStr.cend(), STLTEST::PrintNValue);
		//copy(vStr.cbegin(), vStr.cend(), ostream_iterator<int>(cout, "\n"));
		cout << endl;

		remove(vStr.begin(), vStr.end(), 5);

		size_t n = vStr.size();
		//vStr.erase(remove(vStr.begin(), vStr.end(), "zz"), vStr.end());

		//for_each(vStr.cbegin(), vStr.cend(), STLTEST::PrintNValue);

		////////////////////////////////////////////////////////////////////////// 
		// 流迭代器写文件
		// 文件写入流

		//ofstream infile("f:\\test.txt"); //运行前，请让f:\\test.txt里面只有一个整数  
		//if (!infile)
		//{
		//	cout << "Can not open file!" << endl;
		//}
		//else
		//{
		//	copy(vStr.cbegin(), vStr.cend(), ostream_iterator<int>(infile, "\n"));
		//}
		//infile.close();



		// 流迭代器读文件
		// 文件读入流
		ifstream readFile("f:\\test.txt");
		if (readFile
			&& !readFile.bad())
		{
			// 读取
			vector<string> vs1;
			vector<string>(istream_iterator<string>(readFile), istream_iterator<string>()).swap(vs1);


			// 写到test1文件
			if ( !vs1.empty() )
			{
				//<1> 查看元素
				copy(vs1.cbegin(), vs1.cend(), ostream_iterator<string>(cout, "\n"));
				//

				ofstream ofFile("f:\\test_write.txt");
				if (ofFile
					&& !ofFile.bad())
				{
					copy(vs1.cbegin()
						, vs1.cend()
						, ostream_iterator<string>(ofFile, "\t"));
				}
				ofFile.close();

			}

		}
		readFile.close();



		int j = 0;


	}


	void FileWriteIteratorTest()
	{
		istream_iterator<int> eoff;
		ifstream infile("f:\\test.txt"); //运行前，请让f:\\test.txt里面只有一个整数  
		istream_iterator<int> input(infile);
		cout << "the first element:" << *input << endl;
		++input;
		cout << (input == eoff ? "EOF" : "others") << endl;

		cout << "*******************" << endl;
		cout << "请输入整数,按ctrl+z结束输入:" << endl;
		vector<int> ivec;
		copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(ivec));
		//下句为将ivec内容输出屏幕  
		copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, "\t"));
		system("pause");
	}

	void IteartorInitVTest()
	{
		vector<int> vTest;

		cout << "Input numbers with ';' end" << endl;
		// 输入流写入
		copy(istream_iterator<int>(cin), istream_iterator<int>(),back_inserter(vTest));

		// 打印输出
		ofstream filew("f:\\w1.txt");
		if ( filew
			&&!filew.bad() )
		{
			copy(vTest.cend(), vTest.cend(), ostream_iterator<int>(filew));
			filew.close();
		}
		

		int j = 0;

	}
	
	void STLContainerTest()
	{

		//deque
		vector<string> vA (10, "A");
		size_t nC = vA.capacity();

		vA.clear();

		size_t nC1 = vA.capacity();

		vA.shrink_to_fit();

		size_t nC2 = vA.capacity();

		deque<string> dA(10, "A");
	    
		//set
	    multiset<int, less<int>> vSGreater;
		std::function<void()> f = [&vSGreater]() { for (int i = 0; i < 10; ++i) { vSGreater.insert(i*2); }};
		f();

		// 若安插成功
		/*if (*/vSGreater.insert(3);/*.second*//*)*/
// 		{
// 
// 		}
		/*if (*/vSGreater.insert(3);/*.second*//*)*/
// 		{
// 
// 		}
		/*if (*/vSGreater.insert(3);/*.second*//*)*/
// 		{
// 
// 		}
		


		copy(vSGreater.cbegin(), vSGreater.cend(), ostream_iterator<int>(cout,"\n"));



		pair<set<int, greater<int>>::const_iterator, set<int, greater<int>>::const_iterator> pPOS = vSGreater.equal_range(3);

		cout << "pPOS.first:" <<*pPOS.first << "\npPOS.second:" << *pPOS.second<<endl;
		cout << "distance(pPOS.first, pPOS.second):" <<distance(pPOS.first, pPOS.second)<<endl;

		

		vSGreater.erase(3);
		cout << endl;
		copy(vSGreater.cbegin(), vSGreater.cend(), ostream_iterator<int>(cout, "\n"));

		int j = 0;
	}

	void STLListTest()
	{
		

		vector<int> vV;
		for ( int i = 0; i<10; ++i )
		{
			vV.emplace_back(i);
		}

		list<int> vL( vV.size() );

		//vL.splice( vL.begin(),vV);

		//// 释放vector
		//vector<int>().swap(vV);
		////

		std::function< void( int ) > f = [](int n) { cout << n << endl; };

		for_each(vL.cbegin(), vL.cend(), /*f*/[](int n) { cout << n << endl; });


		

		int j = 0;


	}

	void STLSetTest()
	{
		//////////////////////////////////////////////////////////////////////////
		set<string> coll((istream_iterator<string>(cin))
			, (istream_iterator<string>()));


		copy(coll.cbegin(),coll.cend(), ostream_iterator<string>(cout, "\n"));
		//////////////////////////////////////////////////////////////////////////


		typedef set<int, RuntimeCmp<int>> IntSet;

		IntSet coll1;
		std::function<void(IntSet&)> fill = []( IntSet& coll ) {
			coll.insert(4);
			coll.insert(7);
			coll.insert(5);
			coll.insert(1);
			coll.insert(6);
			coll.insert(2);
			coll.insert(5);
		};
		fill(coll1);

		// 打印出容器内要素值
		cout << "coll1:";
		copy(coll1.cbegin(), coll1.cend(), ostream_iterator<int>(cout, "\t"));
		cout << endl;

		// create sorting criterion with reverse element order
		RuntimeCmp<int> reverse_order( RuntimeCmp<int>::reverse );

		// create,fill,and print set with reverse element order
		IntSet coll2( reverse_order );
		fill(coll2);

		// 打印出容器内要素值
		cout << "coll2:";
		copy(coll2.cbegin(), coll2.cend(), ostream_iterator<int>(cout, "\t"));
		cout << endl;


		// assign elements AND sorting criterion
		coll1 = coll2;
		coll1.insert(3);
		// 打印出容器内要素值
		cout << "coll1:";
		copy(coll1.cbegin(), coll1.cend(), ostream_iterator<int>(cout, "\t"));
		cout << endl;

		// just to make sure...
		if ( coll1.value_comp() == coll2.value_comp() )
		{
			cout << "coll1 and coll2 have same sorting critertion" << endl;
		}
		else
		{
			cout << "coll1 and coll2 have different sorting criterion" << endl;
		}

	}
}

