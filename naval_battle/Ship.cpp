#include "Ship.h"

std::string Ship::get_picture(field_point start, field_point end)
{
	std::string file_ship_name = "ship_";
	if (start.first == end.first)
	{
		file_ship_name += abs(start.second - end.second) + 1 + '0'; //ship_n (n is length)
		file_ship_name += "_v.jpg"; //h - horizontal
	}
	else if (start.second == end.second)
	{
		file_ship_name += abs(start.first - end.first) + 1 + '0';
		file_ship_name += "_h.jpg"; //v - vertical
	}
	return file_ship_name;
}

Ship::Ship(field_point Start, field_point End, int size, int start_x, int start_y ) :
	Graph_lib::Image({ Start.first * size + start_y, Start.second * size + start_x },
		"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\"+get_picture(Start, End)),
	p1{ Start }, p2{ End }
{
}