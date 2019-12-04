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
			fieldR[i][j]->set_color(Graph_lib::Color::black);
			attach(*fieldR[i][j]);
		}
	}
}

void Field::clicked(Graph_lib::Address widget)
{
	Fl_Widget& w = Graph_lib::reference_to<Fl_Widget>(widget);

	int x = (w.x() - start_x) / cell_size;
	int y = (w.y() - start_y) / cell_size;

	if (position[x][y] == 1)
	{
		position[x][y] = 2;
		fire.push_back(new Graph_lib::Rectangle({ w.x(), w.y() }, cell_size, cell_size));
		fire_cord.push_back({ x,y });
		fire[fire.size() - 1]->set_fill_color(Graph_lib::Color::red);
		attach(*fire[fire.size() - 1]);
	}

	fieldB[y][x]->hide();

	destroy_ship();

}

void Field::destroy_ship()
{
	for (int i = 0; (i < ship_position.size()) and ship_position[i].first != -1 
		and ship_position[i].second != -1; ++i)
	{
		int x = ship_position[i].first;
		int y = ship_position[i].second;

		if (position[x][y] == 2)
		{
			if (ship[i]->start() == ship[i]->end())
			{
				detach(*ship[i]);
				ship_position[i] = { -1,-1 };

				int i_fire = 0;
				while (fire_cord[i_fire] != ship_position[i])
					++i_fire;
				detach(*fire[i_fire]);
				fire_cord[i_fire] = { -1,-1 };
				break;
			}
			int s = 0;
			int k = 0;
			std::vector<field_point> now;

			if (position[x][y] + position[x + 1][y] > 3)
				for (int j = x; j <= ship[i]->end().first; ++j)
				{
					if (position[j][y] == 2)
						s++;
					now.push_back({ j,y });
					k++;
				}
			else if (position[x][y] + position[x][y + 1] > 3)
				for (int j = y; j <= ship[i]->end().second; ++j)
				{
					if (position[x][j] == 2)
						s++;
					now.push_back({ x,j });
					++k;
				}

			if (s == k and s != 0)
			{
				detach(*ship[i]);
				ship_position[i] = {-1, -1};

				int i_fire = 0;
				while (now.size() != 0)
				{
					if (fire_cord[i_fire].first != -1 and fire_cord[i_fire].second != -1)
						for (int l = 0; l < now.size(); ++l)
							if (fire_cord[i_fire] == now[l])
							{
								detach(*(fire[i_fire]));
								fire_cord[i_fire] = { -1,-1 };
								now.erase(now);
								break;
							}
					++i_fire;
				}
				break;
			}

		}
	}

	redraw();
}
