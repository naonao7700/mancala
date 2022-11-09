#include <iostream>
#include "mancalaLib.h"
#include <stdlib.h>
#include <conio.h>

enum class KeyCode
{
    NONE,
    UP,
    DOWN,
    ENTER,
};

void clearText();
void drawTitle();
void drawRule();
void drawGame(Mancala mancala);
void drawResult(Mancala mancala);
void drawResult_leftWin(Mancala mancala);
void drawResult_rightWin(Mancala mancala);
void drawResult_drawGame(Mancala mancala);
void drawStoneNum(Pocket pocket);
KeyCode getKeyCode();

int main()
{
    Mancala mancala{};

    mancala.gameState = GameState::Title;

    while (true)
    {
        switch (mancala.gameState)
        {
        case GameState::Title:
            drawTitle();
            if (getKeyCode() == KeyCode::ENTER)   mancala.gameState = GameState::Rule;
            break;
        case GameState::Rule:
            drawRule();
            if (getKeyCode() == KeyCode::ENTER)   mancala.gameState = GameState::Game_Input;
            break;
        case GameState::Game_Input:
            drawGame(mancala);
            switch (getKeyCode())
            {
            case KeyCode::UP:
                mancala.OnUpKey();
                break;
            case KeyCode::DOWN:
                mancala.OnDownKey();
                break;
            case KeyCode::ENTER:
                mancala.OnEnterKey();
                break;
            default:
                break;
            }
            break;
        case GameState::Game_Move:
            mancala.Update();
            drawGame(mancala);
            break;
        case GameState::Game_Just:
            mancala.Update();
            drawGame(mancala);
            break;
        case GameState::Game_Steel:
            mancala.Update();
            drawGame(mancala);
            break;
        case GameState::Game_Finish:
            mancala.Update();
            drawGame(mancala);
            break;
        case GameState::Result:
            drawResult(mancala);
            if (getKeyCode() == KeyCode::ENTER)   return 0;
            break;
        default:
            break;
        }
    }

    return 0;
}

void clearText()
{
    //std::cout << "\x1B[2J\x1B[H";
    system("cls");
}

void drawTitle()
{
    clearText();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■　　　　　　" << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■　　　　　　" << std::endl;
    std::cout << "　　　■■■■■　　■■■　　■■■　　■■■　　■■■　　■　　■■■　" << std::endl;
    std::cout << "　　　■　■　■　　■　■　　■　■　　■　　　　■　■　　■　　■　■　" << std::endl;
    std::cout << "　　　■　■　■　　■■■■　■　■　　■■■　　■■■■　■　　■■■■" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　PRESS ENTER KEY" << std::endl;
}

void drawRule()
{
    clearText();

    std::cout << "・ルールの概要（参考：wikipedia）" << std::endl;
    std::cout << "　1. プレイ人数は2人。" << std::endl;
    std::cout << "　2. 縦長に6個ずつ2列に並べた穴を使いゲームを行う。" << std::endl;
    std::cout << "　　 一方の列の穴は一人のプレイヤーのものであり、他方の列の穴はもう一方のプレイヤーのものである。" << std::endl;
    std::cout << "　3. 開始時に各穴に4つの石を入れ、各手番ごとにsowing(種蒔き)と呼ばれる方法で石を動かす。" << std::endl;
    std::cout << "　　 これは自分の穴からどれか1つを選び、その穴にある全ての石を1つずつ隣の穴から順番に入れていく動作である。" << std::endl;
    std::cout << "　4. 2列に並んだ穴の上下に1つずつ大きな穴があり、それぞれがプレイヤーのゴールとなる。" << std::endl;
    std::cout << "　　 sowingの際自陣のゴールには、他の穴と同様に石がまかれる。" << std::endl;
    std::cout << "　　 プレイヤーはこのゴールにより多くの石を集めることで勝利となる。" << std::endl;
    std::cout << "　5. 穴に入れる石自体には敵味方の区別がなく、全ての石は同じ価値を持つ。" << std::endl;
    std::cout << "　　 各プレイヤーは自分の列の穴にある石のみをsowingにより動かせる。" << std::endl;
    std::cout << "　6. sowingした石の最後の石が撒かれる穴の状態によって、「横取り」と「ぴったりゴール」の2つのルールが発生する。" << std::endl;
    std::cout << "　7. どちらかの陣地の石が全て無くなればゲーム終了となる。" << std::endl;
    std::cout << "　　 このとき陣地の石を先に無くしたプレイヤーは敵陣に残っている石を全て獲得することができ、" << std::endl;
    std::cout << "　　 最終的により多くの石が自分のゴールに入っているプレイヤーが勝利となる。" << std::endl;

    std::cout << std::endl;

    std::cout << "・追加ルール" << std::endl;
    std::cout << "　今回は上記の基本ルールに加えて2つの追加ルールを採用する。" << std::endl;
    std::cout << "　1. 横取り" << std::endl;
    std::cout << "　　 sowingした石の最後の石がぴったり自陣の空の窪みに入った場合、その石と" << std::endl;
    std::cout << "　　 向かい側の敵陣の窪みに残っている石をゴールに入れることができる。" << std::endl;
    std::cout << "　2. ぴったりゴール" << std::endl;
    std::cout << "　　 sowingした石の最後の石がぴったり自陣のゴールに入った場合、もう一度自分のターンを行うことができる。" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "　　　　　　　　　　　　　　PRESS ENTER KEY　⇒　Game Start!!" << std::endl;
}

void drawGame(Mancala mancala)
{
    clearText();

    auto leftPockets = mancala.GetPockets(PlayerID::Left);
    auto rightPockets = mancala.GetPockets(PlayerID::Right);

    std::cout << mancala.GetGameText() << std::endl;

    std::cout << std::endl;
    std::cout << "  右側：" << mancala.GetGool(PlayerID::Right).GetStoneNum();
    std::cout << mancala.GetGoalText(PlayerID::Right) << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 6; i++)
    {
        std::cout << mancala.GetCursorText(PlayerID::Left, i) << "|";
        drawStoneNum(leftPockets[i]);
        std::cout << "| |";
        drawStoneNum(rightPockets[i]);
        std::cout << "|" << mancala.GetCursorText(PlayerID::Right, i);

        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "  左側：" << mancala.GetGool(PlayerID::Left).GetStoneNum();
    std::cout << mancala.GetGoalText(PlayerID::Left) << std::endl;
}

void drawResult(Mancala mancala)
{
    if (mancala.GetGool(PlayerID::Left).GetStoneNum() > mancala.GetGool(PlayerID::Right).GetStoneNum())
    {
        drawResult_leftWin(mancala);
    }
    else if (mancala.GetGool(PlayerID::Left).GetStoneNum() == mancala.GetGool(PlayerID::Right).GetStoneNum())
    {
        drawResult_drawGame(mancala);
    }
    else
    {
        drawResult_rightWin(mancala);
    }
}

void drawResult_rightWin(Mancala mancala)
{
    clearText();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　■　　　　　　　　　　　　　　　　　　　　■　■　　　" << std::endl;
    std::cout << "　　　　　　　■　　　　　■　　　　■　　　　　　　　　■　　　　　■　■　　　" << std::endl;
    std::cout << "　　　■■■　　　■■■　■■■　■■■　　■　■　■　　　■■■　■　■　　　" << std::endl;
    std::cout << "　　　■　■　■　■　■　■　■　　■　　　■　■　■　■　■　■　　　　　　　" << std::endl;
    std::cout << "　　　■　　　■　■■■　■　■　　■■　　　■　■　　■　■　■　■　■　　　" << std::endl;
    std::cout << "　　　　　　　　　　　■　　　　　　　　　　　　　　　　　　　　　　　　　　　　" << std::endl;
    std::cout << "　　　　　　　　　■■■　　　　　　　　　　　　　　　　　　　　　　　　　　　　" << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　  　" << mancala.GetGool(PlayerID::Left).GetStoneNum() << " - " << mancala.GetGool(PlayerID::Right).GetStoneNum() << std::endl;
    std::cout << "　　　　　　　　　　　　　　右側のプレイヤーの勝利!!" << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　 　　　PRESS ENTER KEY" << std::endl;
}

void drawResult_leftWin(Mancala mancala)
{
    clearText();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "　　　■　　　　　　■■　　　　　　　　　　　　　　　　　　■　■　　　" << std::endl;
    std::cout << "　　　■　　■　　　■　　　■　　　　　　　　　■　　　　　■　■　　　" << std::endl;
    std::cout << "　　　■　■　■　■■■　■■■　　■　■　■　　　■■■　■　■　　　" << std::endl;
    std::cout << "　　　■　■■■　　■　　　■　　　■　■　■　■　■　■　　　　　　　" << std::endl;
    std::cout << "　　　■　■　　　　■　　　■■　　　■　■　　■　■　■　■　■　　　" << std::endl;
    std::cout << "　　　　　　■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　 　 " << mancala.GetGool(PlayerID::Left).GetStoneNum() << " - " << mancala.GetGool(PlayerID::Right).GetStoneNum() << std::endl;
    std::cout << "　　　　　　　　　　　左側のプレイヤーの勝利!!" << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　PRESS ENTER KEY" << std::endl;
}

void drawResult_drawGame(Mancala mancala)
{
    clearText();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" << std::endl;
    std::cout << "　　　　　■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■　　" << std::endl;
    std::cout << "　　　■■■　■■■　■■■　■　■　■　　■■■　■■■　　■■■■■　■　■　" << std::endl;
    std::cout << "　　　■　■　■　■　■　■　■　■　■　　■　■　■　■　　■　■　■　■■■　" << std::endl;
    std::cout << "　　　■■■　■　　　■■■■　■　■　　　■■■　■■■■　■　■　■　■　　　" << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　　　　　　　■　　　　　　　　　　　　　■　　" << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　　　　　■■■　　　　　　　　　　　　　　　　" << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　 " << mancala.GetGool(PlayerID::Left).GetStoneNum() << " - " << mancala.GetGool(PlayerID::Right).GetStoneNum() << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　　　引き分け!!" << std::endl;
    std::cout << std::endl;
    std::cout << "　　　　　　　　　　　　　　　　PRESS ENTER KEY" << std::endl;
}

void drawStoneNum(Pocket pocket)
{
    if (pocket.GetStoneNum() < 10)   std::cout << " ";
    std::cout << pocket.GetStoneNum();
}

KeyCode getKeyCode()
{
    int key = 0;
    while (key == 0)
    {
        while (_kbhit())
        {
            key = _getch(); //キー入力コードを取得
        }
    }
    if (key == 13)   return KeyCode::ENTER;
    if (key == 72)   return KeyCode::UP;
    if (key == 80)   return KeyCode::DOWN;
    return KeyCode::NONE;
}




