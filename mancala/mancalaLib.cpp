#include "mancalaLib.h"
#include<stdio.h>
#include<windows.h>

int Mancala::GetCursorPos()
{
	int pos = 1 + cursor;
	if (turnPlayer == PlayerID::Right) pos += 6;
	return pos;
}

int Mancala::GetCursorPos(PlayerID id, int index)
{
	int pos = 1 + index;
	if (id == PlayerID::Right) pos += 6;
	return pos;
}

int Mancala::GetNextPos( int pos )
{
	switch (pos)
	{
	case 0: return 12;
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
	case 13: return 1;
	}
	return 0;
}

int Mancala::GetPos(PlayerID id, int index)
{
	int pos = 1;
	if (id == PlayerID::Right) pos += 6;
	return pos + index;
}

void Mancala::MoveUpdate()
{
	handCursor = GetNextPos( handCursor );
	pockets[handCursor].AddStoneNum(1);
	handNum--;

	if (handNum <= 0)
	{
		if (IsFinish())
		{
			gameState = GameState::Game_Finish;
		}
		else if (IsJust())
		{
			gameState = GameState::Game_Just;
		}
		else if (IsSteel())
		{
			gameState = GameState::Game_Steel;
		}
		else
		{
			ChangeTurn();
			gameState = GameState::Game_Input;
		}

	}

}

//ぴったりゴールの処理
void Mancala::JustUpdate()
{
	gameState = GameState::Game_Input;
}

//横取りの処理
//自分と向かい側の相手のポケットの石を全て自分のゴールへ入れる
void Mancala::SteelUpdate()
{
	//自分のポケットを空にする
	int num = 1;
	pockets[handCursor].ResetStone();

	//向かい側を取得する
	int pos = GetSteelPos(handCursor);

	//入れる石を加算
	num += pockets[pos].GetStoneNum();

	//向かい側のポケットを空にする
	pockets[pos].ResetStone();

	//ゴールへ石を入れる
	if (turnPlayer == PlayerID::Left)
	{
		pockets[0].AddStoneNum(num);
	}
	else
	{
		pockets[13].AddStoneNum(num);
	}

	if (IsFinish())
	{//終了判定

		gameState = GameState::Game_Finish;
	}
	else
	{
		//相手のターンへ
		gameState = GameState::Game_Input;
		ChangeTurn();
	}
}

//終了時の処理
void Mancala::FinishUpdate()
{
	//陣地ポケットの石を自分のゴールへ加算する
	for (int i = 0; i < 6; ++i)
	{
		int Lindex = 1 + i;
		int Rindex = 7 + i;

		//ゴールへ加算
		pockets[0].AddStoneNum(pockets[Lindex].GetStoneNum());
		pockets[Lindex].ResetStone();	//石をリセット

		//ゴールへ加算
		pockets[13].AddStoneNum(pockets[Rindex].GetStoneNum());
		pockets[Rindex].ResetStone();	//石をリセット
	}

	if (pockets[0].GetStoneNum() < pockets[13].GetStoneNum())
	{
		result = Result::Win;
	}
	else if (pockets[0].GetStoneNum() > pockets[13].GetStoneNum())
	{
		result = Result::Lose;
	}
	else
	{
		result = Result::Draw;
	}

	gameState = GameState::Result;
}

//ターンを切り替える
void Mancala::ChangeTurn()
{
	if (turnPlayer == PlayerID::Right) turnPlayer = PlayerID::Left;
	else
	{
		turnPlayer = PlayerID::Right;
	}
}

int Mancala::GetSteelPos(int pos)
{
	if (pos < 7) return pos + 6;
	else return pos - 6;
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
	gameState = GameState::Title;
	cursor = 0;
	turnPlayer = PlayerID::Left;
	result = Result::None;
	for (int i = 0; i < 14; ++i)
	{
		pockets.push_back(Pocket(4));
	}
	handCursor = 0;
	handNum = 0;
}

Mancala::~Mancala()
{
	pockets.clear();
}

//ゲームの初期化
void Mancala::Init(int stoneNum)
{
	cursor = 0;
	turnPlayer = PlayerID::Left;
	result = Result::None;

	for (int i = 0; i < 14; ++i)
	{
		pockets[i].ResetStone();
		pockets[i].AddStoneNum(stoneNum);
	}
	pockets[0].ResetStone();
	pockets[13].ResetStone();
	handCursor = 0;
	handNum = 0;
}

bool Mancala::CanSteal()
{
	return false;
}

//ぴったりゴールか判定
//最後に石を落とした位置がゴールポケットならぴったりゴール
bool Mancala::IsJust()
{
	return (handCursor == 0 || handCursor == 13);
}

//ゲームが終了するか判定
//どちらかのポケットが全て0なら終了
bool Mancala::IsFinish()
{
	int cnt = 0;
	for (int i = 0; i < 6; ++i)
	{
		int index = 1 + i;
		cnt += pockets[index].GetStoneNum();
	}
	if (cnt <= 0) return true;

	cnt = 0;
	for (int i = 0; i < 6; ++i)
	{
		int index = 7 + i;
		cnt += pockets[index].GetStoneNum();
	}
	if (cnt <= 0) return true;
	return false;
}

//横取りしたか判定する
bool Mancala::IsSteel()
{
	if (handCursor == 0 || handCursor == 13) return false;	//ゴールは横取りしない
	
	//相手側の陣地なら発動しない
	if ((turnPlayer == PlayerID::Right && handCursor < 7) || (turnPlayer == PlayerID::Left && handCursor > 6)) return false;

	//横取り先を取得する
	int pos = GetSteelPos(handCursor);

	//横取り先に石があるかつ、最後のポケットが空だったら(石を落としたので１つになっている)
	return (pockets[pos].GetStoneNum() > 0 && pockets[handCursor].GetStoneNum() == 1);
}

int Mancala::GetEndPos()
{
	int pos = GetCursorPos();
	int num = pockets[pos].GetStoneNum();
	for (int i = 0; i < num; ++i)
	{
		pos = GetNextPos( pos );
	}
	return pos;
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
	Sleep(1000);
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
	if (handNum == 0) return;	//空は選択不可

	//ポケットを空にする
	pockets[handCursor].ResetStone();

	gameState = GameState::Game_Move;

}

//カーソルの描画を取得する
std::string Mancala::GetCursorText(PlayerID id, int index)
{
	std::string end = " ";
	std::string str = ">";
	if (id == PlayerID::Right) str = "<";

	if (gameState == GameState::Game_Input )
	{

		if (cursor != index) str = " ";
		if (turnPlayer != id) str = " ";

		if (GetEndPos() == GetPos(id, index))
		{
			end = "o";
		}
		else
		{
			end = " ";
		}

	}
	else
	{
		int pos = GetCursorPos(id, index);
		if (pos != handCursor)
		{
			str = " ";
		}
	}

	if (id == PlayerID::Left) str = str + end;
	else str = end + str;

	return str;
}

std::string Mancala::GetGoalText(PlayerID id)
{
	auto str = " ";
	if (gameState != GameState::Game_Input )
	{
		if (id == PlayerID::Left && handCursor == 0)
		{
			str = "<";
		}
		else if (id == PlayerID::Right && handCursor == 13)
		{
			str = "<";
		}
	}
	else
	{
		if (GetEndPos() == 0 && id == PlayerID::Left) str = " o";
		if (GetEndPos() == 13 && id == PlayerID::Right) str = " o";
	}
	return str;
}

//ゲーム中の表示テキストを取得する
std::string Mancala::GetGameText()
{
	if (gameState == GameState::Game_Input)
	{
		if (turnPlayer == PlayerID::Left)
		{
			return "左側のターン";
		}
		else
		{
			return "右側のターン";
		}
	}
	else if (gameState == GameState::Game_Move)
	{
		return "移動中";
	}
	else if (gameState == GameState::Game_Just)
	{
		return "ぴったりゴール！";
	}
	else if (gameState == GameState::Game_Steel)
	{
		return "横取り！";
	}
	else if (gameState == GameState::Game_Finish)
	{
		return "ゲーム終了！";
	}

	return "";
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

void Pocket::ResetStone()
{
	stone = 0;
}
