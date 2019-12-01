#include "Field.h"

using namespace std;
using namespace	Graph_lib;

Field::Field(Point p, int size, const std::string& title):
	MyWindow{ p, 800, 800, title },
	startX { p.x }, startY { p.y },
	squareLenght{ size }
{
	for (int i = 0; i < 10; ++i)
	{
		field.emplace_back();
		for (int j = 0; j < 10; ++j)
		{
			field[i].push_back(new FieldChunck({ startY + i * squareLenght,
				startX + j * squareLenght },
				[](Graph_lib::Address, Graph_lib::Address pw)
			{
				Graph_lib::reference_to<Field>(pw).clicked();
			}
			, squareLenght));
		}
	}
}

