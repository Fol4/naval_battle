#pragma once
#include "MyWindow.h"

class Field : public MyWindow
{
public:
	Field(Graph_lib::Point p, int size, const std::string& title);

	void clicked(Graph_lib::Address widget);
private:
	std::vector<std::vector<Graph_lib::Button*>> fieldB;
	std::vector<std::vector<Graph_lib::Rectangle*>> fieldR;
	int squareLenght = cell_size;
	int startX;
	int startY;
};


