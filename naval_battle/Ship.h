#pragma once
#include "Constant.h"

class Ship
{
private:
	point p1;
	point p2;
public:
	Ship(point Start, point End);

	point start() const { return p1; }
	point end() const { return p2; }

	int length(int x1, int x2)
	{
		return abs(int((x1 - x2) / cell_size));
	}

};

