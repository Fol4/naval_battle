#pragma once
#include "FieldChunck.h"


class Field : MyWindow
{
public:
	Field(Graph_lib::Point p, int h);

	void hide() {}
	void draw() {}

private:
	static void cb_clicked(Graph_lib::Address, Graph_lib::Address pw)
	{
		Graph_lib::reference_to<Field>(pw).clicked();
	}

	void clicked();

	std::vector<std::vector<int*>> position = matrix_2d<int*>(10, 10, nullptr);
	std::vector<std::vector<Graph_lib::Button>> field;
	int squareLenght;
	int startX;
	int startY;
};

