#pragma once
#include "MyWindow.h"

class miniField
{
public:
	miniField(Graph_lib::Point p, int size,
		std::vector<Ship*> sh);
	std::vector<std::vector<Graph_lib::Rectangle*>> minifield;
	std::vector<Ship*> miniship;
private:
	int squareLenght;
	int startX;
	int startY;
};