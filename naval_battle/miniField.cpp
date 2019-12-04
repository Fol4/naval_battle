#include "miniField.h"

miniField::miniField(Graph_lib::Point p, int size, std::vector<Ship*> sh) :
	squareLenght{size},
	startX{ p.x }, startY{ p.y },
	miniship{ sh }
{
	for (int i = 0; i < 10; ++i)
	{
		minifield.emplace_back();
		for (int j = 0; j < 10; ++j)
		{
			minifield[i].push_back(new Graph_lib::Rectangle({ startY + i * squareLenght,
				startX + j * squareLenght },
				squareLenght, squareLenght));
			minifield[i][j]->set_fill_color(Graph_lib::Color::blue);
			minifield[i][j]->set_color(Graph_lib::Color::black);
		}
	}
	for (int i = 0; i < miniship.size(); ++i)
	{
		miniship.push_back(new Ship(miniship[i]->start(), miniship[i]->end(), squareLenght,
			startX, startY));
	}
}