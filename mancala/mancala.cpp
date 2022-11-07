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

void Clear();
void drawAll(Mancala mancala);
KeyCode getKeyCode();


int main()
{
    Mancala mancala{};

    while (true)
    {
        drawAll(mancala);
        switch (mancala.gameState)
        {
        case GameState::Game_Input:
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
        default:
            break;
        }
        if (mancala.gameState == GameState::Result)   break;
    }

    return 0;
}

void Clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

void drawAll(Mancala mancala)
{
    Clear();

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

        std::cout << "|" << leftPockets[i].GetStoneNum() << "| |" << rightPockets[i].GetStoneNum() << "|" << std::endl;

        if (mancala.turnPlayer == PlayerID::Right && mancala.cursor == i)
        {
            std::cout << " < ";
        }
    }

    std::cout << std::endl;
    std::cout << "  左側：" << mancala.GetGool(0).GetStoneNum() << std::endl;
    std::cout << std::endl;
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




