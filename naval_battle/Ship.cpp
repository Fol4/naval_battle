#include "Ship.h"

using namespace std;

Ship::Ship(point Start, point End) :
	p1{ Start }, p2{ End }
{
	string file_ship_name = "ship_";
	if (p1.x == p2.x)
	{
		file_name_ship += length(p1.x - p2.x) + '0'; //ship_n (n is length)
		file_name_ship += "_h.jpg"; //h - horizontal
	}
	else if (p1.y == p1.y)
	{
		file_name_ship += length(p1.x - p2.x) + '0';
		file_name_ship += "_v.jpg"; //v - vertical
	}
	Image(p1, file_name_ship);
}