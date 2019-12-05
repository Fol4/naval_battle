#pragma once
#include "miniField.h"

class Field : public MyWindow
{
public:
	Field(Graph_lib::Point p, int w, int h, const std::string& title);

	void clicked(Graph_lib::Address widget);
	void destroy_ship();
	void surround(field_point p1, field_point p2);
	int get_squareLenght() { return squareLenght; }
	void draw_minifield();
	void draw_button();
private:
	std::vector<std::vector<Graph_lib::Button*>> fieldB;
	std::vector<std::vector<Graph_lib::Image*>> fieldR;
	int squareLenght;
	int startX;
	int startY;
	int width;
	int height;
	miniField mf;
};


