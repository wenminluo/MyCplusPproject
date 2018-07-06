/*!
* \file 	MemoryleakTest.h
* \brief
*
*	ÄÚ´æÐ¹Â©¼ì²â²âÊÔ
*
* \author	lwm email:luowm@greytech.org
* \version  1.0.0
* \date		2018/07/05
*/
#ifndef _H_MEMORYLEAKTEST_H_
#define _H_MEMORYLEAKTEST_H_

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
	#ifndef DBG_NEW    
        #define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
        #define new DBG_NEW 
	#endif // !DBG_NEW
#endif // _DEBUG



#endif // _H_MEMORYLEAKTEST_H_
