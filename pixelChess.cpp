#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "Game.h"

int main()
{
	Game game;
	game.move("dupa");
	int xf, yf, xt, yt;
	bool move_OK;
	std::vector<Position> availibleMoves;
	for (int i = 0; i < 10; i++)
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
		move_OK = game.move(Position(xf, yf), Position(xt, yt));
		if (!move_OK)
			std::cout << "incorrect move\n";

		std::cout << "FEN: " << game.getFEN() << '\n';
	}
}
