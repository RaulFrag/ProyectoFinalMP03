#pragma once
#include <windows.h>
#include "Types.h"

typedef void(*ThreadFunction)(VOID_PTR);

class Thread
{
	VOID_PTR pHandle;
	UINT_32 dwThread_Id;
	ThreadFunction pFunction;
	VOID_PTR param;
	
public:
	//Thread();
	Thread(ThreadFunction _func);
	~Thread();

	//void CreateThread(LPTHREAD_START_ROUTINE funcion);

	//void Start();
	void Start(VOID_PTR _param);

	void Join();
	bool Join(UINT_Ptr _ms);

	ThreadFunction __Internal_Get_Func();
	VOID_PTR __Internal_Get_Param();

	void PauseThread();

	void ResumeThread();
};

