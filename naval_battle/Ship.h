#pragma once
#include "Constant.h"

class Ship
{
private:
	point p1;
	point p2;
public:
	Ship(point Start, point End) :
		p1{ Start }, p2{ End }
	{
		std::string file_ship_name = "ship_";
		if (p1.x == p2.x)
		{
			file_ship_name += p1.x - p2.x + '0'; //ship_n (n is length)
			file_ship_name += "_h.jpg"; //h - horizontal
		}
		else if (p1.y == p1.y)
		{
			file_ship_name += p1.x - p2.x + '0';
			file_ship_name += "_v.jpg"; //v - vertical
		}
		Graph_lib::Image({p1.x*cell_size + start_x, p1.y*cell_size + start_y}, file_ship_name);
	}

	point start() const { return p1; }
	point end() const { return p2; }

	int length(int x1, int x2)
	{
		return abs(int((x1 - x2) / cell_size));
	}

};

