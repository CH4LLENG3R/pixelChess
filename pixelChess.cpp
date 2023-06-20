#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>

#include "Game.h"
#include "Clock.h"

//game history
int main()
{

	return 0;
}

////clock
//int main()
//{
//	Timestamp whiteTime(0, 10, 0);
//	Timestamp blackTime(0, 10, 0);
//	Clock clock(whiteTime, blackTime);
//	for (int i = 0; i < 100; i++)
//	{
//		system("cls");
//		std::cout << "frame: " << i << '\n';
//		std::cout << "white:" << clock.getWhiteTime() << '\n';
//		std::cout << "black:" << clock.getBlackTime() << '\n';
//		Sleep(100);
//	}
//	return 0;
//}

//// logic
//int main()
//{
//	Game game;
//	int xf, yf, xt, yt;
//	bool move_OK;
//	char promote_to;
//	std::vector<Position> availibleMoves;
//	for (int i = 0; i < 20; i++)
//	{
//		game.debug();
//		std::cout << "from: ";
//		std::cin >> xf >> yf;
//
//		std::cout << "availible moves:\n";
//		availibleMoves = game.getPieceMoves(xf, yf);
//		for (Position p : availibleMoves)
//		{
//			std::cout << '(' << p.x << ", " << p.y << ") ";
//		}
//		std::cout << '\n';
//
//		std::cout << "to: ";
//		std::cin >> xt >> yt;
//		if (game.isPromotion(Position(xf, yf), Position(xt, yt)))
//		{
//			std::cout << "Promote to [Q/B/K/R]: ";
//			std::cin >> promote_to;
//			move_OK = game.move(Position(xf, yf), Position(xt, yt), promote_to);
//		}
//		else
//			move_OK = game.move(Position(xf, yf), Position(xt, yt));
//
//		if (!move_OK)
//			std::cout << "incorrect move\n";
//
//		std::cout << "FEN: " << game.getFEN() << '\n';
//	}
//}
