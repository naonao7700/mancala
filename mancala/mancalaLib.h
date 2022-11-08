#pragma once
#include <vector>
#include <string>

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

	//石を空にする
	void ResetStone();
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
	//01～06は上側のポケット
	//07～12は下側のポケット
	//13は下側のゴール

	int handCursor;	//石を落とす位置
	int handNum;	//つかんでいる石の数

	int GetCursorPos();	//カーソルの位置を取得する
	int GetCursorPos(PlayerID id, int index);	//引数からカーソルの位置を取得する
	int GetNextPos();	//次に石を落とす場所を取得する

	void MoveUpdate();
	void JustUpdate();
	void SteelUpdate();
	void FinishUpdate();

	void ChangeTurn();	//相手のターンへ

	int GetSteelPos(int pos);	//横取りの位置を取得する

	//横取り可能か取得する
	bool CanSteal();

	//ぴったりゴールか取得する
	bool IsJust();

	//終了するか判定する
	bool IsFinish();

	//横取りしたか判定する
	bool IsSteel();

public:
	GameState gameState;	//ゲームの状態
	int cursor;	//カーソル位置
	PlayerID turnPlayer;	//現在ターンのプレイヤー
	Result result;	//勝敗

	//ゴールポケットを取得する
	const Pocket& GetGool( PlayerID playerID );

	//ゴール以外のポケットを取得する(playerIDで陣営を指定する)
	std::vector<Pocket> GetPockets( PlayerID playerID );

	//指定したポケットを取得する
	const Pocket& GetPocket( int pocketID );

	//コンストラクタ
	Mancala();

	//デストラクタ
	~Mancala();

	//ボードの変化を反映させる
	void Update();

	void OnUpKey();	//↑キーを押したとき
	void OnDownKey();	//↓キーを押したとき
	void OnEnterKey();	//Enterキーを押したとき

	//ポケットの矢印描画を取得する
	std::string GetCursorText(PlayerID id, int index);

	//ゴールポケットの矢印描画を取得する
	std::string GetGoalText(PlayerID id);

	//ゲーム中に描画するテキストを取得する
	std::string GetGameText();
};