#pragma once
#include "MyWindow.h"

class Field : public MyWindow
{
public:
	Field(Graph_lib::Point p, int w, int h, const std::string& title);

	void clicked(Graph_lib::Address widget);
	void destroy_ship();
	void surround(field_point p1, field_point p2);
	int get_squareLenght() { return squareLenght; }
	void draw_button();
	bool ship_destroyed();
	bool get_first() { return first; }
	void clear_field();
	int all_ship() { int i = 0; for (auto j : ship) if (!j) ++i; return i; }
private:
	Graph_lib::Button* next_turn_button;

	std::vector<std::vector<Graph_lib::Button*>> fieldB;
	std::vector<std::vector<Graph_lib::Image*>> fieldR;

	int squareLenght;
	int startX;
	int startY;
	int width;
	int height;
	bool first = true;
	bool turn_down = false;

	void next_turn();
};


