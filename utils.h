#include <Windows.h>

struct PlayerPos
{
    float pl_x;
    float pl_y;
};

enum SoldatOffset
{
    cameraX = 0x8CBFE8,
    cameraY = 0x8CBFEC,
    playerX = 0x767914,
    playerY = 0x767918,
    playerCount = 0xCF270C
};

void SetCameraPos(HANDLE game_handle, float x, float y)
{
    WriteProcessMemory(game_handle, (void *) SoldatOffset::cameraX, (void *) &x, sizeof(x), 0);
    WriteProcessMemory(game_handle, (void *) SoldatOffset::cameraY, (void *) &y, sizeof(y), 0);
}

int GetPlayerCount(HANDLE game_handle)
{
    int pl_count;
    ReadProcessMemory(game_handle, (void *) SoldatOffset::playerCount, (void *) &pl_count, sizeof(pl_count), 0);
    return pl_count;
}

PlayerPos GetPlayerPos(HANDLE game_handle, int p_id)
{
    PlayerPos p_pos;
    ReadProcessMemory(game_handle, (void *) (SoldatOffset::playerX + (p_id - 1) * 8), (void *) &p_pos.pl_x, sizeof(p_pos.pl_x), 0);
    ReadProcessMemory(game_handle, (void *) (SoldatOffset::playerY + (p_id - 1) * 8), (void *) &p_pos.pl_y, sizeof(p_pos.pl_y), 0);
    return p_pos;
}

void GetKeyEvent(int& currentSpecID, int pl_count)
{
    if (GetAsyncKeyState(VK_LEFT) & 1)
    {
        if(currentSpecID > 1)
        {
            currentSpecID -= 1;
            printf("new specid = %i | pl_count = %i\n", currentSpecID, pl_count);
        }
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 1)
    {
        if(currentSpecID < pl_count + 5)
        {
            currentSpecID += 1;
            printf("new specid = %i | pl_count = %i\n", currentSpecID, pl_count);
        }
    }

}