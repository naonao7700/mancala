#include "mancalaLib.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h> 

#define ANY_ARROW	(224)
#define KEY_LEFT	(75)
#define KEY_RIGHT	(78)
#define KEY_ENTER	(28)

//KeyID Mancala::GetKeyDown()
//{
//	int key = _getch();
//	if (key == KEY_ENTER) return KeyID::Enter;
//	else if (key == ANY_ARROW )
//	{
//		key = _getch();
//		if (key == KEY_LEFT) return KeyID::Left;
//		else if (key == KEY_RIGHT) return KeyID::Right;
//	}
//	return KeyID::NONE;
//}

Pocket* Mancala::GetGool(int playerID)
{
	if (playerID == 0) return &pockets[0];
	return &pockets[13];
}

Pocket* Mancala::GetPockets(int playerID)
{
	if (playerID == 0) return &pockets[1];
	return &pockets[7];
}

Pocket* Mancala::GetPocket(int pocketID)
{
	return &pockets[pocketID];
}

Mancala::Mancala()
{
	cursor = 0;
	turn = Turn::Player;
	result = Result::None;

	for (int i = 0; i < 14; ++i)
	{
		pockets[i] = *new Pocket(5);
	}
}

Mancala::~Mancala()
{
	delete[] pockets;
}

Pocket::Pocket(int stoneNum)
{
	stone = stoneNum;
}

Pocket::~Pocket()
{
}

int Pocket::GetStoneNum()
{
	return stone;
}

void Pocket::AddStoneNum(int num)
{
	stone += num;
}
