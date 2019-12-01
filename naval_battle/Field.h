#pragma once
#include "FieldChunck.h"

class Field : MyWindow
{
public:
	Field(Graph_lib::Point p, int size, const std::string& title);

	void hide() {}
	void draw() {}

	void clicked();
private:
	std::vector<std::vector<FieldChunck*>> field;
	int squareLenght = cell_size;
	int startX;
	int startY;
};


