#include <windows.h>
unsigned long long g_flag = 0;

#pragma optimize("",off)
void GetSpin()
{
    while (InterlockedExchange(&g_flag, 1) == 1)
    {
        // interlock 한번당 몇번의 YieldProcessor()가 필요한지는 모르겟음?
        YieldProcessor();
    }
}
void ReleaseSpin()
{
    InterlockedExchange(&g_flag, 0);
}
#pragma optimize("",on)