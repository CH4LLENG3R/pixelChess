#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "Game.h"

int main()
{
	Game game;
	int xf, yf, xt, yt;
	bool move_OK;
	char promote_to;
	std::vector<Position> availibleMoves;
	for (int i = 0; i < 20; i++)
	{
		game.debug();
		std::cout << "from: ";
		std::cin >> xf >> yf;

		std::cout << "availible moves:\n";
		availibleMoves = game.getPieceMoves(xf, yf);
		for (Position p : availibleMoves)
		{
			std::cout << '(' << p.x << ", " << p.y << ") ";
		}
		std::cout << '\n';

		std::cout << "to: ";
		std::cin >> xt >> yt;
		if (game.isPromotion(Position(xf, yf), Position(xt, yt)))
		{
			std::cout << "Promote to [Q/B/K/R]: ";
			std::cin >> promote_to;
			move_OK = game.move(Position(xf, yf), Position(xt, yt), promote_to);
		}
		else
			move_OK = game.move(Position(xf, yf), Position(xt, yt));

		if (!move_OK)
			std::cout << "incorrect move\n";

		std::cout << "FEN: " << game.getFEN() << '\n';
	}
}
