#include <iostream>
#include <Windows.h>

#include "utils.h"

using namespace std;

int main()
{   
// ========== GET GAMEHANDLE AND PID ============
    DWORD pid=0;         
    HANDLE SoldatHANDLE;       

    HWND SoldatWindow = FindWindow(0, (L"Soldat"));
    if (SoldatWindow == NULL)
    {
        cout<< "Couldn't find find Soldat window..."<<endl;
        exit(-1);
    }
    else
    {
        GetWindowThreadProcessId(SoldatWindow, &pid);
        if(!pid)
        {
            cout << "Couldn't get processID..."<<endl;
            exit(-1);
        }
        else
        {
            SoldatHANDLE = OpenProcess(PROCESS_ALL_ACCESS,0,pid);
        }
        
    }
    
// ===============================================

    PlayerPos playerPos;
    int specID = 1;
    int playerCount = GetPlayerCount(SoldatHANDLE);

    while(1)
    {
        playerCount = GetPlayerCount(SoldatHANDLE);
        GetKeyEvent(specID, playerCount);

        playerPos = GetPlayerPos(SoldatHANDLE, specID);
        SetCameraPos(SoldatHANDLE, playerPos.pl_x, playerPos.pl_y);

        Sleep(1);
    }


    return 0;
}

