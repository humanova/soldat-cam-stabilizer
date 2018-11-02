#include <iostream>
#include <Windows.h>

#include "proc.h"
#include "utils.h"

using namespace std;

int main()
{
	// ========== GET GAMEHANDLE AND PID ============

	DWORD procId = GetProcId(L"Soldat.exe");
	HANDLE SolHandle = 0;
	if (!procId)
	{
		cout << "Couldn't get Soldat PID..." << endl;
		Sleep(1000); exit(-1);
	}
	else
	{
		SolHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
	}

	// ===============================================

	cout << "use left/right arrow to change spectated player" << endl;
	
	gameVal val;
	int specID = 1;
	bool stabilizer = TRUE;

	while (1)
	{
		val.playerPos = GetPlayerPos(SolHandle, specID);
		val.playerCount = GetPlayerCount(SolHandle);
		
		if (stabilizer)
		{
			GetKeyEvent(specID, val.playerCount);
			val.cameraPos = val.playerPos;
			SetCameraPos(SolHandle, val.cameraPos);
		}
		
		Sleep(1);
	}

	return 0;
}

