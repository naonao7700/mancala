#include "mancalaLib.h"
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

//ゴールポケットを取得する
const Pocket& Mancala::GetGool(int playerID)
{
	if (playerID == 0) return pockets[0];
	return pockets[13];
}

//陣地のポケットを取得する
std::vector<Pocket> Mancala::GetPockets(int playerID)
{
	std::vector<Pocket> list;
	if (playerID == 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			list.push_back(pockets[1 + i]);
		}
	}
	else
	{
		for (int i = 0; i < 6; ++i)
		{\
			list.push_back(pockets[7 + i]);
		}
	}

	return list;
	//if (playerID == 0) return pockets[1];
	//return pockets[7];
}

//任意のポケットを取得する
const Pocket& Mancala::GetPocket(int pocketID)
{
	return pockets[pocketID];
}

Mancala::Mancala()
{
	gameState = GameState::Game_Input;
	cursor = 0;
	turnPlayer = PlayerID::Left;
	result = Result::None;

	for (int i = 0; i < 14; ++i)
	{
		pockets.push_back(Pocket(5));
	}
	handCursor = 0;
	handNum = 0;
}

Mancala::~Mancala()
{
	pockets.clear();
}

bool Mancala::CanSteal()
{
	return false;
}

bool Mancala::IsJust()
{
	return false;
}

void Mancala::Update()
{
}

void Mancala::OnUpKey()
{
	cursor--;
	if (cursor < 0) cursor = 5;
}

void Mancala::OnDownKey()
{
	cursor++;
	if (cursor >= 6) cursor = 0;
}

void Mancala::OnEnterKey()
{
	if (turnPlayer == PlayerID::Left)
	{
		turnPlayer = PlayerID::Right;
	}
	else
	{
		turnPlayer = PlayerID::Left;
	}
}

Pocket::Pocket(int stoneNum)
{
	stone = stoneNum;
}

Pocket::~Pocket()
{
}

int Pocket::GetStoneNum() const
{
	return stone;
}

void Pocket::AddStoneNum(int num)
{
	stone += num;
}
