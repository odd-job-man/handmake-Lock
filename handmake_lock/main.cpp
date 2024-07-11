#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include "handmadeLock.h"

constexpr int THREAD_NUM = 20;
constexpr unsigned long long ADD_PER_THREAD = 100000;
unsigned long long g_counter = 0;

unsigned _stdcall ThreadFunc(void* pParam)
{
    printf("start ThreadId : %d\n", GetCurrentThreadId());
    for (int i = 0; i < ADD_PER_THREAD; ++i)
    {
        GetSpin();
        ++g_counter;
        ReleaseSpin();
    }
    printf("end ThreadId : %d\n", GetCurrentThreadId());
    return 0;
}


int main() {
    HANDLE hThreadArr[THREAD_NUM];
    int i;
    for (i = 0; i < THREAD_NUM; ++i)
    {
        hThreadArr[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, nullptr, CREATE_SUSPENDED, nullptr);
        if (!hThreadArr[i])
        {
            printf("_beginthreadex func error code : %d\n", errno);
            __debugbreak();
            goto lb_end;
        }
    }

    for (int i = 0; i < THREAD_NUM; ++i)
    {
        ResumeThread(hThreadArr[i]);
    }


    WaitForMultipleObjects(THREAD_NUM, hThreadArr, true, INFINITE);

    printf("g_counter : %llu\n", g_counter);

lb_end:
    for (int j = 0; j < i; ++j)
    {
        CloseHandle(hThreadArr[j]);
    }
    return 0;
}