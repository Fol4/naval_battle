#include "Field.h"

Field::Field(Graph_lib::Point p, int size, const std::string& title):
	MyWindow{ p, 1200, 1080, title },
	startX { p.x }, startY { p.y },
	squareLenght{ size }
{
	for (int i = 0; i < 10; ++i)
	{
		fieldB.emplace_back();
		fieldR.emplace_back();
		for (int j = 0; j < 10; ++j)
		{
			fieldB[i].push_back(new Graph_lib::Button({ startY + i * squareLenght,
				startX + j * squareLenght }, cell_size, cell_size, "",
				[](Graph_lib::Address widget, Graph_lib::Address pw)
			{
					Graph_lib::reference_to<Field>(pw).clicked(widget);
			}
			));
			attach(*fieldB[i][j]);

			fieldR[i].push_back(new Graph_lib::Rectangle({ startY + i * squareLenght,
				startX + j * squareLenght }, cell_size, cell_size));
			fieldR[i][j]->set_fill_color(Graph_lib::Color::blue);
			attach(*fieldR[i][j]);
		}
	}
}

void Field::clicked(Graph_lib::Address widget)
{
	Fl_Widget& w = Graph_lib::reference_to<Fl_Widget>(widget);

	int x = (w.x() - start_x) / cell_size;
	int y = (w.y() - start_y) / cell_size;

	if (is_ship({ x,y }))
	{
		change_status({ x,y });
		
	}
}