#include <iostream>
#include "mancalaLib.h"

void Clear();
void drawAll(Mancala mancala);

int main()
{
    int a = 0;
    Mancala mancala{};
    drawAll(mancala);

    std::cin >> a;
    std::cout << a << std::endl;
    return 0;
}

void Clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

void drawAll(Mancala mancala)
{
    Clear();

    Pocket* leftPockets = mancala.GetPockets(0);
    Pocket* rightPockets = mancala.GetPockets(1);

    std::cout << std::endl;
    std::cout << "  右側：" << mancala.GetGool(1)->GetStoneNum() << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 6; i++)
    {
        if (mancala.turn == Turn::Player && mancala.cursor == i)
        {
            std::cout << "   > ";
        }
        else
        {
            std::cout << "     ";
        }

        std::cout << "|" << leftPockets[i].GetStoneNum() << "| |" << rightPockets[i].GetStoneNum() << "|" << std::endl;

        if (mancala.turn == Turn::Enemy && mancala.cursor == i)
        {
            std::cout << " < ";
        }
    }

    std::cout << std::endl;
    std::cout << "  左側：" << mancala.GetGool(0)->GetStoneNum() << std::endl;
    std::cout << std::endl;
}




