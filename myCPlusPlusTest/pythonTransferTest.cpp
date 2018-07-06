#include "pythonTransferTest.h"
#include <iostream>
using namespace std;

extern "C"
{
#include "Python.h"
}

//调用输出"Hello Python"函数
void Hello()
{
	Py_Initialize();//调用Py_Initialize()进行初始化
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("test001");//调用的Python文件名
	pFunc = PyObject_GetAttrString(pModule, "Hello");//调用的函数名
	PyEval_CallObject(pFunc, NULL);//调用函数,NULL表示参数为空
	Py_Finalize();//调用Py_Finalize,和Py_Initialize相对应的.
}

void Add()
{
	Py_Initialize();
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("test001");//Test001:Python文件名
	pFunc = PyObject_GetAttrString(pModule, "Add");//Add:Python文件中的函数名
												   //创建参数:
	PyObject *pArgs = PyTuple_New(2);//函数调用的参数传递均是以元组的形式打包的,2表示参数个数
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 6));//0--序号,i表示创建int型变量
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 8));//1--序号
													 //返回值
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);//调用函数
											  //将返回值转换为int类型
	int result;
	PyArg_Parse(pReturn, "i", &result);//i表示转换成int型变量
	cout << "6 + 8 = " << result << endl;
	Py_Finalize();
}

void CvImageTest()
{
	Py_Initialize();//调用Py_Initialize()进行初始化
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("TraverseTest");//调用的Python文件名
	pFunc = PyObject_GetAttrString(pModule, "CvImage");//调用的函数名
	PyEval_CallObject(pFunc, NULL);//调用函数,NULL表示参数为空
	Py_Finalize();//调用Py_Finalize,和Py_Initialize相对应的.
}


void PyMain()
{
	cout << "CvImageTest" << endl;
	CvImageTest();

	cout << "调用Test001.py中的Hello函数..." << endl;
	Hello();
	cout << "\n调用Test001.py中的Add函数..." << endl;
	Add();
	getchar();

	

	return;
}