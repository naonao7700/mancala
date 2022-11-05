#include "mancalaLib.h"

Mancala::Mancala()
{
	for (int i = 0; i < 14; ++i)
	{
		pockets[i] = *new Pocket(5);
	}
}

Pocket::Pocket(int stoneNum)
{
	stone = stoneNum;
}
