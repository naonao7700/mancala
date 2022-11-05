#pragma once

//�|�P�b�g�N���X
class Pocket
{
private:
	int stone;	//�΂̐�
public:
	Pocket( int stoneNum = 0 );
	~Pocket();

	//�����Ă���΂̐����擾����
	int GetStoneNum();

	//�΂�ǉ�����
	void AddStoneNum(int num);
};

//���͂����L�[�̎��
enum class KeyID
{
	NONE,	//���͂Ȃ�
	Left,	//�����
	Right,	//�E���
	Enter,	//����
};

//���s�̎��
enum class Result
{
	None,	//�Q�[����
	Win,	//����
	Lose,	//����
	Draw,	//��������
};

enum class Turn
{
	Player,
	Enemy,
};

//�}���J���N���X
class Mancala
{
private:
	Pocket pockets[14];
public:
	int cursor;	//�J�[�\���ʒu
	Turn turn;	//���݂̃^�[��
	Result result;	//���s

	//�S�[���|�P�b�g���擾����
	Pocket* GetGool(int playerID);

	//�S�[���ȊO�̃|�P�b�g���擾����(playerID�Őw�c���w�肷��)
	Pocket* GetPockets(int playerID);

	//�w�肵���|�P�b�g���擾����
	Pocket* GetPocket(int pocketID);

	//�R���X�g���N�^
	Mancala();

	//�f�X�g���N�^
	~Mancala();
	
};