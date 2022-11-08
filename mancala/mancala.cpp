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
                mancala.cursor--;
                break;
            case KeyCode::DOWN:
                mancala.cursor++;
                break;
            case KeyCode::ENTER:
                mancala.gameState = GameState::Result;
                break;
            default:
                break;
            }

            break;
        case GameState::Game_Move:
            break;
        case GameState::Game_Just:
            break;
        case GameState::Game_Steel:
            break;
        case GameState::Game_Finish:
            break;
        case GameState::Result:
            break;
        default:
            break;
        }
        if (mancala.gameState == GameState::Result)   break;
    }

    return 0;
}

void clearText()
{
    std::cout << "\x1B[2J\x1B[H";
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
    std::cout << "　2. 多くのゲームでは横長に6～12個程度を2列に並べた穴を使いゲームを行う。" << std::endl;
    std::cout << "　　 一方の列の穴は一人のプレイヤーのものであり、他方の列の穴はもう一方のプレイヤーのものである。" << std::endl;
    std::cout << "　　 今回は縦長に各列6個の穴を用意した。" << std::endl;
    std::cout << "　3. 開始時に各穴に決まった数の石を入れ、各手番ごとにsowing(種蒔き)と呼ばれる方法で石を動かす。" << std::endl;
    std::cout << "　　 これは自分の穴からどれか1つを選び、その穴にある全ての石を1つずつ隣の穴から順番に入れていく動作である。" << std::endl;
    std::cout << "　4. 2列に並んだ穴の左右に1つずつ大きな穴があることも多い。今回は縦長のため、上下にこの穴を設置した。" << std::endl;
    std::cout << "　　 この穴は単に取った石を入れておくだけの役割のこともあるが、sowingで石を入れるルールもある。" << std::endl;
    std::cout << "　　 今回は後者を採用し、この大きな穴をゴールと呼ぶ。" << std::endl;
    std::cout << "　5. 穴に入れる石自体には敵味方の区別がなく、全ての石は同じ価値を持つ。" << std::endl;
    std::cout << "　　 各プレイヤーは自分の列の穴にある石のみをsowingにより動かせる。" << std::endl;
    std::cout << "　6. sowingした石の最後の石が撒かれる穴の状態によって、追加での効果が発生するルールもある。" << std::endl;
    std::cout << "　　 今回は「横取り」と「ぴったりゴール」の2つのルールを追加する。" << std::endl;
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

    auto leftPockets = mancala.GetPockets(0);
    auto rightPockets = mancala.GetPockets(1);

    std::cout << std::endl;
    std::cout << "  右側：" << mancala.GetGool(1).GetStoneNum() << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 6; i++)
    {
        if (mancala.turnPlayer == PlayerID::Left && mancala.cursor == i)
        {
            std::cout << "   > ";
        }
        else
        {
            std::cout << "     ";
        }

        std::cout << "|" << leftPockets[i].GetStoneNum() << "| |" << rightPockets[i].GetStoneNum() << "|";

        if (mancala.turnPlayer == PlayerID::Right && mancala.cursor == i)
        {
            std::cout << " < ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "  左側：" << mancala.GetGool(0).GetStoneNum() << std::endl;
    std::cout << std::endl;
}

void drawResult(Mancala mancala)
{

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




