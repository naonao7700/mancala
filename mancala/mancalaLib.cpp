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

//�҂�����S�[���̏���
void Mancala::JustUpdate()
{
	gameState = GameState::Game_Input;
}

//�����̏���
//�����ƌ��������̑���̃|�P�b�g�̐΂�S�Ď����̃S�[���֓����
void Mancala::SteelUpdate()
{
	//�����̃|�P�b�g����ɂ���
	int num = 1;
	pockets[handCursor].ResetStone();

	//�����������擾����
	int pos = GetSteelPos(handCursor);

	//�����΂����Z
	num += pockets[pos].GetStoneNum();

	//���������̃|�P�b�g����ɂ���
	pockets[pos].ResetStone();

	//�S�[���֐΂�����
	if (turnPlayer == PlayerID::Left)
	{
		pockets[0].AddStoneNum(num);
	}
	else
	{
		pockets[13].AddStoneNum(num);
	}

	if (IsFinish())
	{//�I������

		gameState = GameState::Game_Finish;
	}
	else
	{
		//����̃^�[����
		gameState = GameState::Game_Input;
		ChangeTurn();
	}
}

//�I�����̏���
void Mancala::FinishUpdate()
{
	//�w�n�|�P�b�g�̐΂������̃S�[���։��Z����
	for (int i = 0; i < 6; ++i)
	{
		int Lindex = 1 + i;
		int Rindex = 7 + i;

		//�S�[���։��Z
		pockets[0].AddStoneNum(pockets[Lindex].GetStoneNum());
		pockets[Lindex].ResetStone();	//�΂����Z�b�g

		//�S�[���։��Z
		pockets[13].AddStoneNum(pockets[Rindex].GetStoneNum());
		pockets[Rindex].ResetStone();	//�΂����Z�b�g
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

//�^�[����؂�ւ���
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

//�S�[���|�P�b�g���擾����
const Pocket& Mancala::GetGool(PlayerID playerID)
{
	if (playerID == PlayerID::Left) return pockets[0];
	return pockets[13];
}

//�w�n�̃|�P�b�g���擾����
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

//�C�ӂ̃|�P�b�g���擾����
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

//�Q�[���̏�����
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

//�҂�����S�[��������
//�Ō�ɐ΂𗎂Ƃ����ʒu���S�[���|�P�b�g�Ȃ�҂�����S�[��
bool Mancala::IsJust()
{
	return (handCursor == 0 || handCursor == 13);
}

//�Q�[�����I�����邩����
//�ǂ��炩�̃|�P�b�g���S��0�Ȃ�I��
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

//����肵�������肷��
bool Mancala::IsSteel()
{
	if (handCursor == 0 || handCursor == 13) return false;	//�S�[���͉���肵�Ȃ�
	
	//���葤�̐w�n�Ȃ甭�����Ȃ�
	if ((turnPlayer == PlayerID::Right && handCursor < 7) || (turnPlayer == PlayerID::Left && handCursor > 6)) return false;

	//��������擾����
	int pos = GetSteelPos(handCursor);

	//������ɐ΂����邩�A�Ō�̃|�P�b�g���󂾂�����(�΂𗎂Ƃ����̂łP�ɂȂ��Ă���)
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

//�J�[�\������ֈړ�����
void Mancala::OnUpKey()
{
	do
	{
		cursor--;
		if (cursor < 0) cursor = 5;

	} while (GetPocket(GetCursorPos()).GetStoneNum() <= 0);
}

//�J�[�\�������ֈړ�����
void Mancala::OnDownKey()
{
	do
	{
		cursor++;
		if (cursor >= 6) cursor = 0;
	} while (GetPocket(GetCursorPos()).GetStoneNum() <= 0);
}

//����L�[���������Ƃ��̏���
void Mancala::OnEnterKey()
{
	handCursor = GetCursorPos();
	auto pocket = pockets[handCursor];
	handNum = pocket.GetStoneNum();
	if (handNum == 0) return;	//��͑I��s��

	//�|�P�b�g����ɂ���
	pockets[handCursor].ResetStone();

	gameState = GameState::Game_Move;

}

//�J�[�\���̕`����擾����
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

//�Q�[�����̕\���e�L�X�g���擾����
std::string Mancala::GetGameText()
{
	if (gameState == GameState::Game_Input)
	{
		if (turnPlayer == PlayerID::Left)
		{
			return "�����̃^�[��";
		}
		else
		{
			return "�E���̃^�[��";
		}
	}
	else if (gameState == GameState::Game_Move)
	{
		return "�ړ���";
	}
	else if (gameState == GameState::Game_Just)
	{
		return "�҂�����S�[���I";
	}
	else if (gameState == GameState::Game_Steel)
	{
		return "�����I";
	}
	else if (gameState == GameState::Game_Finish)
	{
		return "�Q�[���I���I";
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
