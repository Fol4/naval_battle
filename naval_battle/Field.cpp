#include "Field.h"

Field::Field(Graph_lib::Point p, int w, int h, const std::string& t, const std::string& fp) :
	MyWindow{ p, w, h, cell_size * w / 1500, w / 15, h / 5, t , fp},
	next_turn_button{ new Graph_lib::Button{{w/4, h/100}, w/20, h/50, "Next Turn",
	[](Graph_lib::Address, Graph_lib::Address pw)
			{
				Graph_lib::reference_to <Field> (pw).next_turn();
			}} },
	win_button{ new Graph_lib::Button{ {w/2,h/2}, w/10, h/25, "Restart",
	[](Graph_lib::Address, Graph_lib::Address pw)
			{
					Graph_lib::reference_to<Field>(pw).win();
			}
	} },
	startX{ w / 15 }, startY{ h / 5 },
	squareLenght{ cell_size * w / 1500 },
	title{t}
{
	attach(*win_button);
	win_button->hide();
	attach(*next_turn_button);
	for (int i = 0; i < 10; ++i)
	{
		if (i != 9)
		{
			vertical.push_back(new Graph_lib::Mark({ startX + 55, startY + i * squareLenght - 50 }, '1' + i));
			vertical[i]->set_color(FL_DARK_MAGENTA);
			attach(*vertical[i]);
		}
		horizontal.push_back(new Graph_lib::Mark({ startX + i * squareLenght + 135, startY - 100}, 'A' + i));
		horizontal[i]->set_color(FL_DARK_MAGENTA);
		attach(*horizontal[i]);

		fieldR.emplace_back();
		for (int j = 0; j < 10; ++j)
		{
			fieldR[i].push_back(new Graph_lib::Image({ startY + i * squareLenght,
				startX + j * squareLenght },
				folder_path + "water_texture.jpg"));
			attach(*fieldR[i][j]);
		}
	}
	vertical.push_back(new Graph_lib::Mark({ startX + 50, startY + 9 * squareLenght - 50 }, '1'));
	vertical.push_back(new Graph_lib::Mark({ startX + 60, startY + 9 * squareLenght - 50 }, '0'));
	vertical[vertical.size() - 2]->set_color(FL_DARK_MAGENTA);
	vertical[vertical.size() - 1]->set_color(FL_DARK_MAGENTA);
	attach(*vertical[vertical.size() - 2]);
	attach(*vertical[vertical.size() - 1]);
}

void Field::clear_field()
{
	for (int i = 0; i < cross.size(); ++i)
		detach(*cross[i]);

	for (int i = 0; i < fire.size(); ++i)
		detach(*fire[i]);

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			detach(*fieldR[i][j]);

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			detach(*fieldB[i][j]);

	for (int i = 0; i < horizontal.size(); ++i)
		detach(*horizontal[i]);

	for (int i = 0; i < vertical.size(); ++i)
		detach(*vertical[i]);

	for (int i = 0; i < warnings.size(); ++i)
		detach(*warnings[i]);

	next_turn_button->hide();
	next_button->hide();
	start.hide();
	end.hide();

	detach(*warning);
}
void Field::win()
{
	smn_win = true;
	hide();
}

void Field::clear_ship()
{
	for (auto i : ship)
		detach(*i);
}

int Field::all_ship()
{
	int i = 0;
	for (auto j : ship_position)
		if (j.first != -1 and j.second != -1)
			++i;
	return i;
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
				folder_path+"explosion.jpg"));
			attach(*fire[fire.size() - 1]);
			fieldB[x][y]->hide();

			destroy_ship();

			if (all_ship() == 0)
			{
				clear_field();
				win_button->show();
				attach(win_image);
			}
		}
	}
	else if (position[x][y] == 0)
	{
		if (!turn_down)
		{
			position[x][y] = 3;
			cross.push_back(new Graph_lib::Image({ w.x(), w.y() },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			turn_down = true;
			fieldB[x][y]->hide();
		}
	}
}

void Field::next_turn()
{
	random_button->hide();
	if (first)
	{
		if (!is_full())
			attach_warnings(warningNow, "Field not full", warnings, warningX);
		else
		{
			hide();
			draw_button();
			first = false;
			turn_down = false;
			clear_ship();
		}
	}
	else
		if (!turn_down)
			attach_warnings(warningNow, "Turn not down", warnings, warningX);
		else
		{
			turn_down = false;
			hide();
		}
}

void Field::destroy_ship()
{
	std::cout << "NEW" << std::endl;
	for (int i = 0; (i < ship_position.size()); ++i)
	{
		int s = 0;
		int k = 0;

		std::cout << "new :";
		for (int j1 = ship[i]->start().first; j1 <= ship[i]->end().first; ++j1)
			for (int j = ship[i]->start().second; j <= ship[i]->end().second; ++j)
			{
				if (position[j1][j] == 2)
					++s;
				++k;
			}

		std::cout << s << " " << k << std::endl;

		if (s == k and s != 0)
		{
			surround(ship[i]->start(), ship[i]->end());
			ship_position[i] = std::make_pair(-1, -1);
			redraw();
		}
	}
}

void Field::surround(field_point p1, field_point p2)
{
	
	if (p1.first == p2.first)
	{
		if (p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1)*squareLenght + startY,
				p1.second*squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second]->hide();
		}
		if (p1.first != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first + 1) * squareLenght + startY, 
				p1.second* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first + 1][p1.second]->hide();
		}
		if (p1.second != 0)
		{
			cross.push_back(new Graph_lib::Image({ p1.first * squareLenght + startY, 
				(p1.second - 1)* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
		}
		if (p1.second != 0 and p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second - 1) * squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second - 1]->hide();
		}
		if (p1.second != 0 and p1.first != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first + 1) * squareLenght + startY,
				(p1.second - 1) * squareLenght + startX },
				folder_path + "cross.jpg"));
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
						folder_path + "cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[p1.first - 1][i+1]->hide();
				}
				if (p1.first != 9)
				{
					cross.push_back(new Graph_lib::Image({ (p1.first + 1) * squareLenght + startY,
						(i + 1) * squareLenght + startX },
						folder_path + "cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[p1.first + 1][i + 1]->hide();
				}
			}
		}
		if (p2.second != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first) * squareLenght + startY, 
				(p2.second + 1)* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first][p2.second + 1]->hide();
		}
	}
	else if (p1.second == p2.second)
	{
		if (p1.second != 0)
		{
			cross.push_back(new Graph_lib::Image({ p1.first * squareLenght + startY, 
				(p1.second - 1)* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first ][p1.second - 1]->hide();
		}
		if (p1.second != 9)
		{
			cross.push_back(new Graph_lib::Image({ p1.first * squareLenght + startY,
				(p1.second + 1)* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first][p1.second + 1]->hide();
		}
		if (p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second)* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second]->hide();
		}
		if (p1.second != 0 and p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second - 1) * squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p1.first - 1][p1.second - 1]->hide();
		}
		if (p1.second != 9 and p1.first != 0)
		{
			cross.push_back(new Graph_lib::Image({ (p1.first - 1) * squareLenght + startY,
				(p1.second + 1) * squareLenght + startX },
				folder_path + "cross.jpg"));
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
						folder_path + "cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[i + 1][p1.second - 1]->hide();
				}
				if (p1.second != 9)
				{
					cross.push_back(new Graph_lib::Image({ (i + 1) * squareLenght + startY,
						(p1.second + 1) * squareLenght + startX },
						folder_path + "cross.jpg"));
					attach(*cross[cross.size() - 1]);
					fieldB[i + 1][p1.second + 1]->hide();
				}
			}
		}
		if (p2.first != 9)
		{
			cross.push_back(new Graph_lib::Image({ (p2.first + 1) * squareLenght + startY,
				p1.second* squareLenght + startX },
				folder_path + "cross.jpg"));
			attach(*cross[cross.size() - 1]);
			fieldB[p2.first + 1][p1.second ]->hide();
		}
	}
	redraw();
}

bool Field::ship_destroyed()
{
	for (int i = 0; i < ship_position.size(); ++i)
		if (ship_position[i].first != -1 and ship_position[i].second != -1)
			return false;
	return true;
}