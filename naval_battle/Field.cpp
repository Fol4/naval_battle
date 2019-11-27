#include "Field.h"

using namespace std;
using namespace	Graph_lib;

Field::Field(Point p, int size):
	startX { p.x }, startY { p.y },
	squareLenght{ size }
{
	for(int i =0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
		{
			field[i].push_back(new FieldChunck({startY + i * squareLenght, startX + j * squareLenght},
				cb_clicked, squareLenght));
		}
}