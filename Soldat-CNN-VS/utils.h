#pragma once
#include <Windows.h>
#include <TlHelp32.h>

enum SoldatOffset
{
	cameraX = 0x8CBFE8,
	cameraY = 0x8CBFEC,
	playerX = 0x767914,
	playerY = 0x767918,
	playerCount = 0xCF270C
};

struct Pos
{
	float x;
	float y;
};

struct gameVal
{
	Pos playerPos;
	Pos cameraPos;
	int playerCount;
};

int GetPlayerCount(HANDLE game_handle)
{
	int pl_count;
	ReadProcessMemory(game_handle, (BYTE*)SoldatOffset::playerCount, (BYTE*)&pl_count, sizeof(pl_count), 0);
	return pl_count;
}

Pos GetPlayerPos(HANDLE game_handle, int p_id)
{
	Pos p_pos;
	ReadProcessMemory(game_handle, (BYTE*)(SoldatOffset::playerX + (p_id - 1) * 8), (BYTE*)&p_pos.x, sizeof(p_pos.x), 0);
	ReadProcessMemory(game_handle, (BYTE*)(SoldatOffset::playerY + (p_id - 1) * 8), (BYTE*)&p_pos.y, sizeof(p_pos.y), 0);
	return p_pos;
}

void SetCameraPos(HANDLE game_handle, Pos cam_pos)
{
	WriteProcessMemory(game_handle, (BYTE*)SoldatOffset::cameraX, (BYTE*)&cam_pos.x, sizeof(cam_pos.x), 0);
	WriteProcessMemory(game_handle, (BYTE*)SoldatOffset::cameraY, (BYTE*)&cam_pos.y, sizeof(cam_pos.y), 0);
}

void GetKeyEvent(int& currentSpecID, int pl_count)
{
	if (GetAsyncKeyState(VK_LEFT) & 1)
	{
		if (currentSpecID > 1)
		{
			currentSpecID -= 1;
			printf("new specid = %i | pl_count = %i\n", currentSpecID, pl_count);
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 1)
	{
		if (currentSpecID < pl_count + 5)
		{
			currentSpecID += 1;
			printf("new specid = %i | pl_count = %i\n", currentSpecID, pl_count);
		}
	}

}