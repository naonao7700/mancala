#include "mancalaLib.h"

KeyID Mancala::GetKeyDown()
{
	return KeyID::NONE;
}

Mancala::Mancala()
{
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
