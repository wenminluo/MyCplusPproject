#include "pythonTransferTest.h"
#include <iostream>
using namespace std;

extern "C"
{
#include "Python.h"
}

//�������"Hello Python"����
void Hello()
{
	Py_Initialize();//����Py_Initialize()���г�ʼ��
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("test001");//���õ�Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "Hello");//���õĺ�����
	PyEval_CallObject(pFunc, NULL);//���ú���,NULL��ʾ����Ϊ��
	Py_Finalize();//����Py_Finalize,��Py_Initialize���Ӧ��.
}

void Add()
{
	Py_Initialize();
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("test001");//Test001:Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "Add");//Add:Python�ļ��еĺ�����
												   //��������:
	PyObject *pArgs = PyTuple_New(2);//�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 6));//0--���,i��ʾ����int�ͱ���
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 8));//1--���
													 //����ֵ
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);//���ú���
											  //������ֵת��Ϊint����
	int result;
	PyArg_Parse(pReturn, "i", &result);//i��ʾת����int�ͱ���
	cout << "6 + 8 = " << result << endl;
	Py_Finalize();
}

void CvImageTest()
{
	Py_Initialize();//����Py_Initialize()���г�ʼ��
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	pModule = PyImport_ImportModule("TraverseTest");//���õ�Python�ļ���
	pFunc = PyObject_GetAttrString(pModule, "CvImage");//���õĺ�����
	PyEval_CallObject(pFunc, NULL);//���ú���,NULL��ʾ����Ϊ��
	Py_Finalize();//����Py_Finalize,��Py_Initialize���Ӧ��.
}


void PyMain()
{
	cout << "CvImageTest" << endl;
	CvImageTest();

	cout << "����Test001.py�е�Hello����..." << endl;
	Hello();
	cout << "\n����Test001.py�е�Add����..." << endl;
	Add();
	getchar();

	

	return;
}