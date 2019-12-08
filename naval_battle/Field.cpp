#include "Field.h"

Field::Field(Graph_lib::Point p, int w, int h, const std::string& title) :
	MyWindow{ p, w, h, cell_size * w / 1500, w / 15, h / 5, title },
	next_turn_button{ new Graph_lib::Button{{w/4, h/100}, w/20, h/50, "Next Turn",
	[](Graph_lib::Address, Graph_lib::Address pw)
			{
				Graph_lib::reference_to <Field> (pw).next_turn();
			}} },
	startX{ w / 15 }, startY{ h / 5 },
	squareLenght{ cell_size * w / 1500 }
{
	attach(*next_turn_button);
	for (int i = 0; i < 10; ++i)
	{
		fieldR.emplace_back();
		for (int j = 0; j < 10; ++j)
		{
			fieldR[i].push_back(new Graph_lib::Image({ startY + i * squareLenght,
				startX + j * squareLenght },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\water_texture.jpg"));
			attach(*fieldR[i][j]);
		}
	}
}

void Field::clear_field()
{
	for (auto i : ship)
		detach(*i);
}

void Field::draw_button()
{
	for (int i = 0; i < 10; ++i)
	{
		fieldB.emplace_back();
		for (int j = 0; j < 10; ++j)
		{
			fieldB[i].push_back(new Graph_lib::Button({ startY + i * squareLenght,
				startX + j * squareLenght }, squareLenght, squareLenght, "",
				[](Graph_lib::Address widget, Graph_lib::Address pw)
				{
					Graph_lib::reference_to<Field>(pw).clicked(widget);
				}
			));
			attach(*fieldB[i][j]);
		}
	}
}
void Field::clicked(Graph_lib::Address widget)
{
	Fl_Widget& w = Graph_lib::reference_to<Fl_Widget>(widget);

	int x = (w.x() - startY) / squareLenght;
	int y = (w.y() - startX) / squareLenght;

	if (position[x][y] == 1)
	{
		if (!turn_down)
		{
			position[x][y] = 2;
			fire.push_back(new Graph_lib::Image({ w.x(), w.y() },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\explosion.jpg"));
			attach(*fire[fire.size() - 1]);
			fieldB[x][y]->hide();

			destroy_ship();
		}
	}
	else if (position[x][y] == 0)
	{
		if (!turn_down)
		{
			position[x][y] = 2;
			cross.push_back(new Graph_lib::Image({ w.x(), w.y() },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			turn_down = true;
			fieldB[x][y]->hide();
		}
	}
}

void Field::next_turn()
{
	if (first)
	{
		if (!is_full())
			std::cerr << "Field not full" << std::endl;
		else
		{
			hide();
			draw_button();
			first = false;
			turn_down = false;
			clear_field();
		}
	}
	else
		if (!turn_down)
			std::cerr << "Turn not down" << std::endl;
		else
		{
			turn_down = false;
			hide();
		}
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
				surround(ship[i]->start(), ship[i]->end());
				ship_position[i] = { -1, -1 };
				break;
			}
			int s = 0;
			int k = 0;

			if (position[x][y] + position[x + 1][y] > 3)
				for (int j = x; j <= ship[i]->end().first; ++j)
				{
					if (position[j][y] == 2)
						s++;
					k++;
				}
			else if (position[x][y] + position[x][y + 1] > 3)
				for (int j = y; j <= ship[i]->end().second; ++j)
				{
					if (position[x][j] == 2)
						s++;
					++k;
				}

			if (s == k and s != 0)
			{
				surround(ship[i]->start(), ship[i]->end());
				ship_position[i] = {-1, -1};
				break;
			}

		}
	}

	redraw();
}

void Field::surround(field_point p1, field_point p2)
{
	
	if (p1.first == p2.first)
	{
		if (p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1)*squareLenght + startY,
				p1.second*squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second]->hide();
		}
		if (p1.first != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first + 1) * squareLenght + startY, 
				p1.second* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first + 1][p1.second]->hide();
		}
		if (p1.second != 0)
		{
			cross.push_back(new Graph_lib::Image({ p1.first * squareLenght + startY, 
				(p1.second - 1)* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
		}
		if (p1.second != 0 and p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second - 1) * squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second - 1]->hide();
		}
		if (p1.second != 0 and p1.first != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first + 1) * squareLenght + startY,
				(p1.second - 1) * squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first + 1][p1.second - 1]->hide();
		}
		for (int i = p1.second; i <= p2.second; ++i)
		{
			if (i != 9)
			{
				if (p1.first != 0)
				{
					cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
						(i + 1) * squareLenght + startX },
						"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[p1.first - 1][i+1]->hide();
				}
				if (p1.first != 9)
				{
					cross.push_back(new Graph_lib::Image({ (p1.first + 1) * squareLenght + startY,
						(i + 1) * squareLenght + startX },
						"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[p1.first + 1][i + 1]->hide();
				}
			}
		}
		if (p2.second != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first) * squareLenght + startY, 
				(p2.second + 1)* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first ][p1.second + 1]->hide();
		}
	}
	else if (p1.second == p2.second)
	{
		if (p1.second != 0)
		{
			cross.push_back(new Graph_lib::Image({ p1.first * squareLenght + startY, 
				(p1.second - 1)* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first ][p1.second - 1]->hide();
		}
		if (p1.second != 9)
		{
			cross.push_back(new Graph_lib::Image({ p1.first * squareLenght + startY,
				(p1.second + 1)* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first][p1.second + 1]->hide();
		}
		if (p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second)* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second]->hide();
		}
		if (p1.second != 0 and p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second - 1) * squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second - 1]->hide();
		}
		if (p1.second != 9 and p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second + 1) * squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second + 1]->hide();
		}
		for (int i = p1.first; i <= p2.first; ++i)
		{
			if (i != 9)
			{
				if (p1.second != 0)
				{
					cross.push_back(new Graph_lib::Image({ (i + 1) * squareLenght + startY,
						(p1.second - 1) * squareLenght + startX },
						"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[i + 1][p1.second - 1]->hide();
				}
				if (p1.second != 9)
				{
					cross.push_back(new Graph_lib::Image({ (i + 1) * squareLenght + startY,
						(p1.second + 1) * squareLenght + startX },
						"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[i + 1][p1.second + 1]->hide();
				}
			}
		}
		if (p2.first != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first + 3) * squareLenght + startY,
				p1.second* squareLenght + startX },
				"C:\\Users\\user\\source\\repos\\naval_battle\\naval_battle\\pic\\cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first + 3][p1.second ]->hide();
		}
	}
}

bool Field::ship_destroyed()
{
	for (int i = 0; i < ship_position.size(); ++i)
		if (ship_position[i].first != -1 and ship_position[i].second != -1)
			return false;
	return true;
}