#include "mancalaLib.h"

int Mancala::GetCursorPos()
{
	int pos = 1 + cursor;
	if (turnPlayer == PlayerID::Right) pos += 6;
	return pos;
}

int Mancala::GetNextPos()
{
	switch (handCursor)
	{
	case 0: return 13;
	case 1: return 2;
	case 2: return 3;
	case 3: return 4;
	case 4: return 5;
	case 5: return 6;
	case 6: return (turnPlayer == PlayerID::Left) ? 0 : 12;
	case 7: return (turnPlayer == PlayerID::Left) ? 1 : 13;
	case 8: return 7;
	case 9: return 8;
	case 10: return 9;
	case 11: return 10;
	case 12: return 11;
	}
	return 0;
}

void Mancala::MoveUpdate()
{
	handCursor = GetNextPos();
	auto pocket = pockets[handCursor];
	pocket.AddStoneNum(1);
	handNum--;

	if (handNum <= 0)
	{
		ChangeTurn();

		gameState = GameState::Game_Input;
	}

}

void Mancala::JustUpdate()
{
}

void Mancala::SteelUpdate()
{
}

void Mancala::FinishUpdate()
{
}

void Mancala::ChangeTurn()
{
	if (turnPlayer == PlayerID::Right) turnPlayer = PlayerID::Left;
	else
	{
		turnPlayer = PlayerID::Right;
	}
}

//ゴールポケットを取得する
const Pocket& Mancala::GetGool(PlayerID playerID)
{
	if (playerID == PlayerID::Left) return pockets[0];
	return pockets[13];
}

//陣地のポケットを取得する
std::vector<Pocket> Mancala::GetPockets(PlayerID playerID)
{
	std::vector<Pocket> list;
	if (playerID == PlayerID::Left)
	{
		for (int i = 0; i < 6; ++i)
		{
			list.push_back(pockets[1 + i]);
		}
	}
	else
	{
		for (int i = 0; i < 6; ++i)
		{
			list.push_back(pockets[7 + i]);
		}
	}

	return list;
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
	pockets[0].AddStoneNum(-5);
	pockets[13].AddStoneNum(-5);
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
	switch (gameState)
	{
	case GameState::Game_Move: MoveUpdate(); break;
	case GameState::Game_Just: JustUpdate(); break;
	case GameState::Game_Steel: SteelUpdate(); break;
	case GameState::Game_Finish: FinishUpdate(); break;
	}
}

//カーソルを上へ移動する
void Mancala::OnUpKey()
{
	do
	{
		cursor--;
		if (cursor < 0) cursor = 5;

	} while (GetPocket(GetCursorPos()).GetStoneNum() <= 0);
}

//カーソルを下へ移動する
void Mancala::OnDownKey()
{
	do
	{
		cursor++;
		if (cursor >= 6) cursor = 0;
	} while (GetPocket(GetCursorPos()).GetStoneNum() <= 0);
}

//決定キーを押したときの処理
void Mancala::OnEnterKey()
{
	handCursor = GetCursorPos();
	auto pocket = pockets[handCursor];
	handNum = pocket.GetStoneNum();

	//ポケットを空にする
	pocket.AddStoneNum(-handNum);

	gameState = GameState::Game_Move;

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
