#pragma once
#include "Constant.h"

class Ship: public Graph_lib::Image
{
private:
	field_point p1;
	field_point p2;
public:
	Ship(field_point Start, field_point End);

	field_point start() const { return p1; }
	field_point end() const { return p2; }
	std::string get_picture(field_point start, field_point end);

	int length(int x1, int x2)
	{
		return abs(int((x1 - x2) / cell_size));
	}
};

