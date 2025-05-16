#include "Thread.h"
#include <stdio.h>

DWORD __stdcall Global_Thread_Function(void *_ptr)
{
	Thread* _this = (Thread*)_ptr;
	ThreadFunction func = _this->__Internal_Get_Func();
	VOID_PTR param = _this->__Internal_Get_Param();
	func(param);
	return 0;
}

//Thread::Thread()
//{
//	dwThread_Id = 0;
//	pHandle = INVALID_HANDLE_VALUE;
//}

Thread::Thread(ThreadFunction _func)
{
	dwThread_Id = 0;
	pHandle = INVALID_HANDLE_VALUE;
	pFunction = _func;
	param = nullptr;
}

Thread::~Thread()
{
	if (pHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(pHandle);
		pHandle = INVALID_HANDLE_VALUE;
	}
	dwThread_Id = 0;
	pFunction = nullptr;
	param = nullptr;
}

//void Thread::CreateThread(LPTHREAD_START_ROUTINE funcion)
//{
//	//pHandle = ::CreateThread(NULL, 0, funcion, NULL, CREATE_SUSPENDED, &dwThread_Id);
//	//if (pHandle == INVALID_HANDLE_VALUE)
//	//{
//	//	//ERROR
//	//	printf("Esto peta");
//	//}
//}

//void Thread::Start()
//{
//	::ResumeThread(pHandle);
//}

void Thread::Start(VOID_PTR _param)
{
	param = _param;
	pHandle = ::CreateThread(NULL, 0, Global_Thread_Function, this, 0, (DWORD*)&dwThread_Id);
	if (pHandle == INVALID_HANDLE_VALUE)
	{
		//ERROR
		printf("Esto peta");
	}

}



void Thread::Join()
{
	DWORD dwResult = WaitForSingleObject(pHandle, INFINITE);
	if (dwResult != WAIT_OBJECT_0)
	{
		//Fatal ERROR
	}
}

bool Thread::Join(UINT_Ptr _ms)
{
	DWORD dwResult = WaitForSingleObject(pHandle, _ms);
	if (dwResult == WAIT_OBJECT_0)
	{
		return true;
	}
	else if (dwResult == WAIT_TIMEOUT)
	{
		return false;
	}
	else
	{
		//Fatal ERROR
		return false;
	}
}

ThreadFunction Thread::__Internal_Get_Func()
{
	return pFunction;
}

VOID_PTR Thread::__Internal_Get_Param()
{
	return param;
}

void Thread::PauseThread()
{
	SuspendThread(pHandle);
}

void Thread::ResumeThread()
{
	::ResumeThread(pHandle);
}
