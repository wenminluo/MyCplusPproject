#include "TemplateTest.h"
#include "UtilitiesTest.h"
#include <string>
#include <memory>
#include "STLTest.h"
#include <map>
#include <list>
#include <bitset>
#include "pythonTransferTest.h"
#include "ThreadTest.h"
#include <thread>
#include "TBBTest.h"


using namespace std;

////////////////////////////////////////////////////////////////////////////
#include "third_lib/json/include/json.h"
#include "PolygonalLX.h"
////////////////////////////////////////////////////////////////////////////
//#define _CRT_SECURE_NO_WARNINGS




/// \brief 模板测试
void TemplateTest()
{
	MyClass a;
	int i = 11;
	double dj = 12.0;

	int n = a.max(1,6,i);
	double d = a.max(1.0, 3.2,dj);

	string str1 = "   da,s,das   ";
	wstring wstr1 = L"   e;e,e;ee;e;12 ";

	vector<string> v1;
	a.split(str1,",",v1,true);

	vector<wstring> v2;
	a.split(wstr1, L",", v2, true);
	
	

	int j = 0;

}

class myError1
{

};


void f() throw (myError1,std::bad_exception)
{
	if (1)
	{
		if (1)
		{
			myError err("异常了!");
			/*MyProblem err("异常了");*/
	
			throw err/*out_of_range("异常了!")*/;
			//throw std::out_of_range("111");
		}
	
	}

	int jj = 0;

}

void explictTest()
{
	/*Stack k = 9;*/
	int i = 0;
}

void CastTest(  )
{
	Car* p = new Limousine;

	Cabriolet* p1 = static_cast<Cabriolet*>(p);
	if (p1)
	{
		int j = 0;
	}


	Cabriolet* p2 = dynamic_cast<Cabriolet*>(p);
	if ( p2 )
	{
		int k = 0;
	}

	int j = 0;

}






//void Function()
//{
//	shared_ptr<Parent> pA(new Parent);
//	shared_ptr<Child> pB(new Child);
//	//pA->child = pB;
//	//pB->parent = pA;
//
//	int n = pA.use_count();
//	int j = pB.use_count();
//	int k = 0;
//
//}
class Child;
class Parent
{
public:
	~Parent()
	{
		int j = 0;

	}

	unique_ptr<const Child>& childAt(int nIndex)
	{
		if ( m_childTables.size()>nIndex )
		{
			return unique_ptr<const Child>(m_childTables.at(nIndex).get());
		}
		/*return NULL;*/
	}

	/*shared_ptr<Child> child;*/
	weak_ptr<Child> child;

	vector<unique_ptr<Child>> m_childTables;    // 子表
};


class Child
{
public:
	~Child()
	{
		int j = 0;
	}


	/*shared_ptr<Parent> parent;*/

	weak_ptr<Parent> parent;

	unique_ptr<Parent> uParent;
};

void auto_ptrTest( Parent* )
{
	auto_ptr< Stack > ptr(new Stack(1));

	auto_ptr< Stack > ptr1(new Stack(2));
	ptr1 = ptr;


	auto_ptr<Stack> ptr0;

	unique_ptr<Stack> ptr11;



	if (ptr.get())
	{
		int j = 0;
	}

	int j = 0;
}

void Function()
{
	//////////////////////////////////////////////////////////////////////////
	FILE* pStm = NULL;
	if (0==fopen_s(&pStm, "E:\\pecmd.ini", "r"))
	{
		shared_ptr<FILE> fileRes(pStm, &fclose);

	}
	
	//////////////////////////////////////////////////////////////////////////


	shared_ptr<Parent> pA(new Parent, &auto_ptrTest);
	shared_ptr<Child> pB(new Child);
	pA->child = pB;
	pB->parent = pA;

	int i = pA.use_count();
	int j = pB.use_count();

	int k = 0;

}


void Func1(shared_ptr<Parent> a)
{
	cout << "Enter Func1" << endl;
	cout << "Ref count: " << a.use_count() << endl;
	cout << "Leave Func1" << endl;
}

shared_ptr<Parent> Func2(shared_ptr<Parent>& a)
{
	cout << "Enter Func2" << endl;
	cout << "Ref count: " << a.use_count() << endl;
	cout << "Leave Func2" << endl;
	return a;
}

void fun12Test()
{
	//构造一个指向int类型对象的指针aObj1,引用计数+1
	shared_ptr<Parent> aObj1(new Parent);
	cout << "Ref count: " << aObj1.use_count() << endl;
	int n = aObj1.use_count();
	{
		//同aObj1,不过由于生存周期在括号内,所以aObj2会被销毁
		shared_ptr<Parent> aObj2 = aObj1;
		cout << "Ref count: " << aObj2.use_count() << endl;//引用计数-1
		n = aObj1.use_count();
		int j = 0;
	}
	n = aObj1.use_count();

	//在调用函数时,参数为shared_ptr类型,参数为传值类型,智能指针引用计数+1
	Func1(aObj1);
	n = aObj1.use_count();

	//在调用函数时,参数为shared_ptr类型,参数为传引用类型,智能指针引用计数不变
	Func2(aObj1);
	n = aObj1.use_count();

	shared_ptr<Parent> aObj3 = Func2(aObj1);//引用计数+1
	

	n = aObj1.use_count();
	cout << "Ref count:" << aObj3.use_count() << endl;
}


unique_ptr<Parent> Unique_ptrTest()
{
	unique_ptr< Parent > pParent(new Parent);

	return pParent;
}



void numeric_limitsTest()
{
	// print maximum of integral typea
	cout << "max(short):" << numeric_limits<short>::max() << endl;

	// print char is signed
	cout << "is_signed(char):" << numeric_limits<char>::is_signed << endl;

	// print whether numeric limits for type string exist
	cout << "is_specialized(string):" << numeric_limits<string>::is_specialized << endl;


	int j = 0;
}


void jsonTest()
{
	//Json::Value rootVal;

	//Json::CharReaderBuilder jsonReadObj;
	//if (jsonReadObj.parse("E:\\myCplusPlusTest\\myCPlusPlusTest\\test_data\\red.json", rootVal))
	//{

		//[1]获取红色点数据
		//.....
		//
		vector<LXPoint> vRedPts;
		vRedPts.emplace_back(LXPoint(2678.2619, 9459.1982));
		vRedPts.emplace_back(LXPoint(2727.5129, 9453.8691));
		vRedPts.emplace_back(LXPoint(2737.0625, 9452.8330));
		vRedPts.emplace_back(LXPoint(2737.3430, 9452.8027));
		vRedPts.emplace_back(LXPoint(2744.7739, 9475.1464));
		vRedPts.emplace_back(LXPoint(2684.3061, 9484.8994));
		vRedPts.emplace_back(LXPoint(2673.9511, 9479.5634));
		vRedPts.emplace_back(LXPoint(2672.2502, 9467.1826));

		//[2]  初始化查询接口
		CPolygonalLX polyLxObj(vRedPts);

		//[3] 获取黑色数据点
		//...
		//

		//[4] 逐点判断方位
		LXPoint pt1(3678.287,9659.573);
		LXPtPosType ePosType1 = polyLxObj(pt1);

		LXPoint pt2(2678.796, 9462.119);
		LXPtPosType ePosType2 = polyLxObj(pt2);

		int j = 0;

		
	//}

}

int fun(int x[], int n)
{
	static int sum = 0, i;
	for ( i = 0;i<n;i++ )
	{
		sum += x[i];
	}

	return sum;

}

void test()
{
	/*int a[] = { 1,2,3,4,5 }, b[] = { 6,7,8,9 }, s = 0;
	s = fun(a, 5 + fun(b, 4));
	
	int j = 0;*/

	char str[][20] = { "One*World","One*Dream!" }, *p = str[1];
	printf("%d", strlen(p));
	printf("%s\n",p);

}


shared_ptr<double> SharedTest()
{

	shared_ptr< double > pd = NULL;


	pd = shared_ptr<double>(new double(2.2));

	return pd;
}



void sharedTestMain()
{
	map<int, shared_ptr<double>> mapTest;

   for ( int i = 0 ; i<3; ++i  )
   {
	   mapTest[i] = NULL;
   }

   for ( int j = 0; j< 3; ++j   )
   {
	   mapTest[j] = SharedTest();
   }

   for ( auto itM = mapTest.cbegin()
	    ; mapTest.cend()!= itM
	    ; ++itM )
   {
	   if ( itM->second )
	   {

		   double dd = *(itM->second);
        
		   cout << itM->first <<" "<<dd<<endl;
	   }
   }

}

#include <algorithm>
void STLReplaceTest()
{
	wstring ws1 = L"F:/2/3/4/DDD";

	wstring ws2(ws1);
	replace_copy(ws1.begin(), ws1.end(), ws2.begin(),L'/', L'\\');

	int j = 0;

}

//////////////////////////////////////////////////////////////////////////

class Test
{
public:
	typedef std::shared_ptr<Test> TestPtr;
	static TestPtr CreateInstance()
	{
		return TestPtr(new Test());
	}
private:
	Test()
	{
	}
};
//////////////////////////////////////////////////////////////////////////

void STLMaxSizeTest()
{
	vector<int> vInt;
	cout<< "vInt.max_size(): " <<vInt.max_size()<<endl;

	// 返回第一个元素
	vInt.front();

	// 返回最后一个元素
	vInt.back();

	list<int> lInt;
	cout << "lInt.max_size(): " << lInt.max_size() << endl;

	vector<string> vStr;
	cout << "vStr.max_size(): " << vStr.max_size() << endl;

	list<string> lStr;
	cout << "lStr.max_size(): " << lStr.max_size() << endl;

	
	int j = 0;
}

void BitSetTest()
{
	bitset<16> b8("01010011");
	b8 = 25;
	for ( int n =15; n>=0; --n )
	{
		cout << b8[n] << endl;
	}
	
	int j = 0;

}

typedef struct  user1
{
	string name;
};

void PtrTest()
{
	vector<shared_ptr<const user1>> vU;

	shared_ptr<user1> pU = make_shared<user1>();

	pU->name = "12";

	vU.emplace_back(pU);

	for_each(vU.cbegin(), vU.cend(), [](auto it) { cout << it->name << endl; });

	int j = 0;

}

// 线程安全日志
#include "CLogger.h"
#include <sstream>


/// \brief 获取当前系统时间
/// \return 当前系统时间
std::wstring getCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm ptm;
	localtime_s(&ptm, &tt);

	wchar_t date[60] = { 0 };
	swprintf_s(date, L"%d-%02d-%02d %02d:%02d:%02d",
		(int)ptm.tm_year + 1900, (int)ptm.tm_mon + 1, (int)ptm.tm_mday,
		(int)ptm.tm_hour, (int)ptm.tm_min, (int)ptm.tm_sec);

	return std::wstring(date);
}

void logSomeMessages(int id, Logger& logger)
{
	for ( int i = 0; i< 10; ++i )
	{
		 wstringstream ss;
		 ss << getCurrentSystemTime()<< L" :Log entry " << i << L" from thread " << id;
		 logger.log(ss.str());

	}

}

void ThreadSafeLogTest()
{
	Logger logger;
	vector<thread> threads;

	// Create a few threads all working with the same Logger instances.
	for ( int i = 0; i < 10; ++i )
	{
		threads.emplace_back(logSomeMessages, i, ref(logger));
	}

	// Wait for all threads to finish.
	for ( auto& t : threads )
	{
		t.join();
	}
}

//

// 移动语义测试 
class Echo {
public:
	Echo() { std::cout << "new" << std::endl; }
	Echo(const Echo&) { std::cout << "new" << std::endl; }
	Echo& operator=(const Echo&) { std::cout << "=" << std::endl; return *this; }
	Echo(Echo&&) noexcept { std::cout << "move" << std::endl; }
	Echo& operator=(Echo&&) noexcept {
		std::cout << "move" << std::endl; return *this;
	}
};

Echo Rtest()
{
	
	Echo j;

	return j;
	//return std::move(j);
}


void Rtest(Echo& g)
{
	int j = 0;
}

void MoveTest()
{

	std::vector<Echo> v1, v2;
	v2.resize(1);

	v1.resize(5);
	std::cout << v1.size() << " "
		<< v2.size() << std::endl;
	//v2 = v1;
	//v2 = std::move(v1);
	v2.swap(v1);

	std::cout << v1.size() << " "
		<< v2.size() << std::endl;

////////////////////////////////////////////////////////////////////////////
//	Echo i = Rtest();
//	//i=Rtest();
//	//Rtest(i);
//
//	int j = 0;
////////////////////////////////////////////////////////////////////////////

	

}
//

//
unique_ptr<int> UniquePtrTest()
{
	return make_unique<int>(2);
}
//

//
class zz
{
public:
	zz()
	 :mI(0){
		cout << "zz()" << endl;
		//throw invalid_argument("i invalid");
	}
	~zz()
	{
		cout << "~zz()" << endl;
	}

	void set(int t) 
	{
		mI = t;
	}

	int Val() const 
	{
		return mI;
	}

private:
	int mI;
};


//[1] 照片exif信息结构体
typedef struct PhotoExifInfo_
{
	PhotoExifInfo_()
		: m_strName(L"")
		, m_lSize(0)
		, m_strPath(L"")
		, m_strCameraManufacturer(L"")
		, m_strCameraModel(L"")
		, m_strCameraOwner(L"")
		, m_strGeneratingTheImageHost(L"")
		, m_strImageShootingTime(L"")
		, m_strImageModificationTime(L"")
		, m_strGPS(L"")
		, m_strShootingPosition(L"")
		, m_strPhotoPixelDimension(L"")
		, m_strPhotoSoftware(L"")
		, m_uFileObjId(0)
		, m_strRefFilePath(L"")
		, m_bDeleteFile(false) {
		memset(&m_tCreateTime, 0, sizeof(time_t));
		memset(&m_tModifyTime, 0, sizeof(time_t));
		memset(&m_tCreateTime, 0, sizeof(time_t));
	}


	wstring m_strName;                   // 名称
	long m_lSize;                        // 大小(字节)
	wstring m_strPath;                   // 路径

	wstring m_strCameraManufacturer;     // 相机厂商
	wstring m_strCameraModel;            // 相机型号
	wstring m_strCameraOwner;            // 相机拥有者

	wstring m_strGeneratingTheImageHost; // 生成图像主机
	wstring m_strImageShootingTime;      // 图像拍摄时间
	wstring m_strImageModificationTime;  // 图像修改时间

	wstring m_strGPS;                    // GPS
	wstring m_strShootingPosition;       // 拍摄位置
	wstring m_strPhotoPixelDimension;    // 宽度

	wstring m_strPhotoSoftware;          // 程序
	time_t m_tCreateTime;                // 创建时间
	time_t m_tModifyTime;                // 修改时间

	time_t m_tAcessTime;                 // 访问时间
	uint32_t m_uFileObjId;		         // 参考文件ID
	wstring	 m_strRefFilePath;           // 参考文件路径

	bool m_bDeleteFile;	                 // 是否为删除文件

}PhotoExifInfo;

class CFileAnalysis
{
public:


	/// \brief 分析
	/// \return 成功true,失败false
	bool Parse()
	{
		if ( PareseQInfo(mQueue) )
		{
		/*	for ( const unique_ptr< const zz > pZ : mQueue  )
			{
				cout << "zz:" << pZ->Val() << endl;
			}*/

			for_each(mQueue.cbegin(), mQueue.cend(), [](const unique_ptr< const PhotoExifInfo >& pZ)
			{
				wcout << L"PhotoExifInfo:" << pZ->m_strName.c_str() << endl;

				//pZ = std::move(unique_ptr< const PhotoExifInfo >());
			});
		
			return true;
		}

		return false;
	}

private:
	std::vector<unique_ptr< const PhotoExifInfo> > mQueue;    // 队列信息

	/// \brief 生成队列信息
	/// \param  qInfos  [in/out]  队列信息
	/// \return 生成成功true,失败false
	bool PareseQInfo(std::vector< unique_ptr<const PhotoExifInfo> >& qInfos)
	{
		//[1] 结果集清空
		std::vector<unique_ptr<const PhotoExifInfo>>().swap(qInfos);

		
		static std::wstringstream strConver;

		for ( size_t i =0; i< 10; ++i  )
		{
			unique_ptr<PhotoExifInfo> p = std::make_unique<PhotoExifInfo>();

			strConver.clear();
			strConver.str(L"");
			strConver <<L"PhotoInfo:";
			strConver << i << endl;
			p->m_strName = strConver.str();


			qInfos.emplace_back(std::move(p));
		}

		return (!qInfos.empty());
	}

	void test( )
	{
		wcout << L"test" << endl;
	}

};
//

//std::function 测试
void func(int num, const string& str)
{
	cout << "func(" << num << "," << str << ")" << endl;
}
//


#include <windows.h>

// 内存泄漏检测
#include "MemoryleakTest.h"
//

int main(int argc, char** argv)
{
	// 内存泄漏检测
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//


	CFileAnalysis cf;

	// 只能定义public函数
	bool (CFileAnalysis::*CParse) () = &CFileAnalysis::Parse;
/*	void (CFileAnalysis::*cTest) () = &CFileAnalysis::test;*/

	(cf.*CParse)();
	


	std::function<void(int, const string&)> f1 = func;

	f1(1, "test");

	////////////////////////////////////////////////////////////////////////////
	//CFileAnalysis cf;
	//cf.Parse();
	////////////////////////////////////////////////////////////////////////////

	try
	{
		zz z1;
	}
	catch (const std::exception& err)
	{
		cout << err.what() << endl;
	}
	
	unique_ptr<int> pl;
	pl = UniquePtrTest();

	MoveTest();
	return 0;

	TBBTest();
	return 0;

	//////////////////////////////////////////////////////////////////////////
	//ThreadSafeLogTest();
	//////////////////////////////////////////////////////////////////////////

	////
	//shared_ptr<int> p11;

	//p11 = make_shared<int>(2);

	//if (p11)
	//{
	//	int j = 0;
	//}

	//p11.reset();

	//if ( p11 )
	//{
	//	int j = 0;
	//}

	//unique_ptr<thread> p1, p2;

	//ThreadTest( p1,p2 );

	//PtrTest();

	//PyMain();

	//double d1 = 3.45e-6;

	//STLTEST::STLSetTest();

	//STLTEST::STLListTest();

	//STLTEST::STLContainerTest();
	//

	////STLTEST::IteartorInitVTest();

	//int j = 0;

	////BitSetTest();

	//STLTEST::RemoveTest();

	//STLMaxSizeTest();
	
	//STLTEST::f1();
	//int j = 0;
	//::Sleep(10000);

	//if (p1
	//	&&p1->joinable())
	//	p1->join();
	//	
	//if (p2
	//	&&p2->joinable())
	//	p2->join();

	return 0;


	vector<int> v(10, 1);

	PRINT_ELEMENTS(v);

	

	STLTEST::IteratorTest();

	

	Test::TestPtr p = Test::CreateInstance();
	

	STLReplaceTest();

	sharedTestMain();

	//jsonTest();

	STLTEST::AlgorithmTest();

	STLTEST::RQTest();

	numeric_limitsTest();

	//////////////////////////////////////////////////////////////////////////
	Compare<int> comp1;
	std::cout << comp1.IsEqual(3, 4) << std::endl;
	std::cout << comp1.IsEqual(3, 3) << std::endl;

	Compare<float> comp2;
	std::cout << comp2.IsEqual(3.14, 4.14) << std::endl;
	std::cout << comp2.IsEqual(3, 3) << std::endl;

	Compare<double> comp3;
	std::cout << comp3.IsEqual(3.14159, 4.14159) << std::endl;
	std::cout << comp3.IsEqual(3.14159, 3.14159) << std::endl;
	//////////////////////////////////////////////////////////////////////////

	//int i = 10, j = 15;

	//int n = g(10, 15);
	//int m = g(i, j);

	//fun12Test();

	//Function();

	unique_ptr<Parent> pp(new Parent);
	
	if ( !pp )
	{
		/*int j = 0;*/
		pp.reset();
	}

	pp.reset();

	if (!pp)
	{
		/*int j = 0;*/
		pp.reset();
	}

	//Shared_ptrTest();

	auto_ptrTest( NULL);

	PairTest();

  	//int j = MyConstClass::nNum;


	//CastTest();
	//explictTest();

	//
	try
	{
		f();
	}
	catch (const myError& err)
	{
		
		int j = 0;
	}

	//
	TemplateTest();



	return 0;
}

