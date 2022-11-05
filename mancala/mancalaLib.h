#pragma once

//ポケットクラス
class Pocket
{
private:
	int stone;	//石の数
public:
	Pocket( int stoneNum = 0 );
	~Pocket();

	//入っている石の数を取得する
	int GetStoneNum();

	//石を追加する
	void AddStoneNum(int num);

};

//入力したキーの種類
enum class KeyID
{
	NONE,	//入力なし
	Left,	//左矢印
	Right,	//右矢印
	Enter,	//決定
};

//勝敗の種類
enum class Result
{
	None,	//ゲーム中
	Win,	//勝ち
	Lose,	//負け
	Draw,	//引き分け
};

enum class Turn
{
	Player,
	Enemy,
};

//マンカラクラス
class Mancala
{
public:
	int cursor;	//カーソル位置
	Turn turn;	//現在のターン
	Result result;	//勝敗

	//ポケット
	Pocket pockets[14];

	//KeyID GetKeyDown();
	

	//コンストラクタ
	Mancala();

	//デストラクタ
	~Mancala();
	
};