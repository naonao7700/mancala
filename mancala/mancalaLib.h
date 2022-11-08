#pragma once
#include <vector>
#include <string>

//�Q�[���̏��
enum class GameState
{
	Title,
	Rule,
	Game_Input,
	Game_Move,
	Game_Just,
	Game_Steel,
	Game_Finish,
	Result,
};

//�v���C���[�̎��
enum class PlayerID
{
	Left,
	Right,
};

//�|�P�b�g�N���X
class Pocket
{
private:
	int stone;	//�΂̐�
public:
	Pocket( int stoneNum = 0 );
	~Pocket();

	//�����Ă���΂̐����擾����
	int GetStoneNum() const;

	//�΂�ǉ�����
	void AddStoneNum(int num);

	//�΂���ɂ���
	void ResetStone();
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

//�}���J���N���X
class Mancala
{
private:
	std::vector<Pocket> pockets;//�S�Ẵ|�P�b�g
	//00�͏㑤�̃S�[��
	//01�`06�͏㑤�̃|�P�b�g
	//07�`12�͉����̃|�P�b�g
	//13�͉����̃S�[��

	int handCursor;	//�΂𗎂Ƃ��ʒu
	int handNum;	//����ł���΂̐�

	int GetCursorPos();	//�J�[�\���̈ʒu���擾����
	int GetCursorPos(PlayerID id, int index);	//��������J�[�\���̈ʒu���擾����
	int GetNextPos();	//���ɐ΂𗎂Ƃ��ꏊ���擾����

	void MoveUpdate();
	void JustUpdate();
	void SteelUpdate();
	void FinishUpdate();

	void ChangeTurn();	//����̃^�[����

	int GetSteelPos(int pos);	//�����̈ʒu���擾����

	//�����\���擾����
	bool CanSteal();

	//�҂�����S�[�����擾����
	bool IsJust();

	//�I�����邩���肷��
	bool IsFinish();

	//����肵�������肷��
	bool IsSteel();

public:
	GameState gameState;	//�Q�[���̏��
	int cursor;	//�J�[�\���ʒu
	PlayerID turnPlayer;	//���݃^�[���̃v���C���[
	Result result;	//���s

	//�S�[���|�P�b�g���擾����
	const Pocket& GetGool( PlayerID playerID );

	//�S�[���ȊO�̃|�P�b�g���擾����(playerID�Őw�c���w�肷��)
	std::vector<Pocket> GetPockets( PlayerID playerID );

	//�w�肵���|�P�b�g���擾����
	const Pocket& GetPocket( int pocketID );

	//�R���X�g���N�^
	Mancala();

	//�f�X�g���N�^
	~Mancala();

	//�{�[�h�̕ω��𔽉f������
	void Update();

	void OnUpKey();	//���L�[���������Ƃ�
	void OnDownKey();	//���L�[���������Ƃ�
	void OnEnterKey();	//Enter�L�[���������Ƃ�

	//�|�P�b�g�̖��`����擾����
	std::string GetCursorText(PlayerID id, int index);

	//�S�[���|�P�b�g�̖��`����擾����
	std::string GetGoalText(PlayerID id);

	//�Q�[�����ɕ`�悷��e�L�X�g���擾����
	std::string GetGameText();
};