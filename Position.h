#pragma once

struct Position
{
	short x;
	short y;

	Position(): x(-1), y(-1)
	{}

	Position(const short& x, const short& y) : x(x), y(y)
	{}
};