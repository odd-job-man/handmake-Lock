#include <windows.h>
unsigned long long g_flag = 0;

#pragma optimize("",off)
void GetSpin()
{
    while (InterlockedExchange(&g_flag, 1) == 1)
    {
        // interlock �ѹ��� ����� YieldProcessor()�� �ʿ������� �𸣰���?
        YieldProcessor();
    }
}
void ReleaseSpin()
{
    InterlockedExchange(&g_flag, 0);
}
#pragma optimize("",on)