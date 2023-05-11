#include <iostream>
#include <fcntl.h>
#include <io.h>

#include "Game.h"

int main()
{
	_setmode(_fileno(stdout), _O_U8TEXT);
	std::wcout << L'\u2654' << ' ' << L'\u2655' << ' ' << L'\u2656' << ' '
		<< L'\u2657' << ' ' << L'\u2658' << ' ' << L'\u2659' << std::endl;
	std::wcout << L'\u265A' << ' ' << L'\u265B' << ' ' << L'\u265C' << ' '
		<< L'\u265D' << ' ' << L'\u265E' << ' ' << L'\u265F' << std::endl;

	Game game;
	game.move("dupa");
	game.~Game();
}
