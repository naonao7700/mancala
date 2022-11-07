#pragma once
#include <vector>

//ゲームの状態
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

//プレイヤーの種類
enum class PlayerID
{
	Left,
	Right,
};

//ポケットクラス
class Pocket
{
private:
	int stone;	//石の数
public:
	Pocket( int stoneNum = 0 );
	~Pocket();

	//入っている石の数を取得する
	int GetStoneNum() const;

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

//マンカラクラス
class Mancala
{
private:
	std::vector<Pocket> pockets;//全てのポケット
	//00は上側のゴール
	//01〜06は上側のポケット
	//07〜12は下側のポケット
	//13は下側のゴール

	int handCursor;	//石を落とす位置
	int handNum;	//つかんでいる石の数
public:
	GameState gameState;	//ゲームの状態
	int cursor;	//カーソル位置
	PlayerID turnPlayer;	//現在ターンのプレイヤー
	Result result;	//勝敗

	//ゴールポケットを取得する
	const Pocket& GetGool(int playerID);

	//ゴール以外のポケットを取得する(playerIDで陣営を指定する)
	std::vector<Pocket> GetPockets(int playerID);

	//指定したポケットを取得する
	const Pocket& GetPocket(int pocketID);

	//コンストラクタ
	Mancala();

	//デストラクタ
	~Mancala();

	//横取り可能か取得する
	bool CanSteal();

	//ぴったりゴールか取得する
	bool IsJust();

	//ボードの変化を反映させる
	void Update();
	
};