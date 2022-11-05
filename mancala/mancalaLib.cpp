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

Mancala::Mancala()
{
	result = Result::None;
	turn = 0;

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
