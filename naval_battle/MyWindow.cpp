#include "MyWindow.h"

MyWindow::MyWindow(Graph_lib::Point p, int w, int h, int size, int start_x, int start_y, const std::string& title) :
	Window{ p, w, h, title  },
	quit_button{new Graph_lib::Button( Graph_lib::Point{x_max() - w/15, h/100}, w/20, h/50, "Quit",
	[](Graph_lib::Address, Graph_lib::Address pw) {
							 Graph_lib::reference_to<MyWindow>(pw).quit();
							 }
				)},
	next_button{new Graph_lib::Button( Graph_lib::Point{w/5, h/100}, w/20, h/50, "Next",
	[](Graph_lib::Address , Graph_lib::Address pw) {
							  Graph_lib::reference_to<MyWindow>(pw).next();
							  }
				)},
	start{Graph_lib::Point {w/20, h/100}, 100, h/50, "Ship Start" },
	end{Graph_lib::Point { w/7, h/100}, 100, h/50, "Ship End" },
	folder{Graph_lib::Point{w / 10, 3 * h / 4}, 3 * w / 4, w / 20, "Path"},
	squareLenght{size},
	startX{start_x}, startY{start_y},
	warning{ new Graph_lib::Rectangle{{w - w / 3, h/8}, w / 3, size * 10 } },
	warningX{ w - w / 3 + 15}, warningNow{ h/8 + 30}
{
	warning->set_fill_color(Graph_lib::Color::white);
	warning->set_color(Graph_lib::Color::black);
	attach(*warning);

	attach(*quit_button);
	attach(*next_button);
	attach(start);
	attach(end);
}

MyWindow::MyWindow(Graph_lib::Point p, int w, int h):
	Window{p, w, h, "Menu"},
	quit_button{new Graph_lib::Button(Graph_lib::Point{6*w/7, h/30}, w/9, w/30,
		"Quit",
	[](Graph_lib::Address, Graph_lib::Address pw) {
							 Graph_lib::reference_to<MyWindow>(pw).quit();
							 }
				)},
	pvp_button{new Graph_lib::Button( Graph_lib::Point{w/8, 2*h/7}, 3*w/4, h/20,
		"Player VS Player",
	[](Graph_lib::Address , Graph_lib::Address pw) {
						  Graph_lib::reference_to<MyWindow>(pw).pvp();
						  }
				)},
	pve_button{new Graph_lib::Button( Graph_lib::Point{w/8, 3*h/7}, 3*w/4, h/20,
		"Player VS Environment",
	[](Graph_lib::Address , Graph_lib::Address pw) {
					   Graph_lib::reference_to<MyWindow>(pw).pve();
					   }
				)},
	help_button{new Graph_lib::Button(Graph_lib::Point{w / 8, 4 * h / 7}, 3 * w / 4, h / 20,
		"Rules",
	[](Graph_lib::Address , Graph_lib::Address pw) {
					   Graph_lib::reference_to<MyWindow>(pw).help();
					   }
				) },
	input_button{new Graph_lib::Button(Graph_lib::Point{6*w/7, 3*h/4}, w/9, w/30,
					   "Input",
	[](Graph_lib::Address, Graph_lib::Address pw){
						Graph_lib::reference_to<MyWindow>(pw).input();
											  }
		)},
	start{ Graph_lib::Point {100, 10}, 100, 20, "Ship Start" },
	end{ Graph_lib::Point { 300, 10}, 100, 20, "Ship End" },
	folder{Graph_lib::Point{w/10, 3*h/4}, 3*w/4, w/30, "Path"}	
{
	attach(*quit_button);
	attach(*pvp_button);
	attach(*pve_button);
	attach(*help_button);
	attach(*input_button);
	attach(folder);
}

void MyWindow::next()
{
	if(!is_full())
	{
		std::string StartCord = start.get_string();
		std::string EndCord = end.get_string();

		field_point Start = string_to_point(StartCord);
		field_point End = string_to_point(EndCord);

		if (add_position(Start, End))
		{
			ship.push_back(new Ship(Start, End, squareLenght, startX, startY));
			attach(*ship[ship.size() - 1]);
			ship_position.push_back(Start);
		}

		redraw();
	}
}

void MyWindow::pvp() 
{
	if (is_folder)
	{
		mode = "pvp";
		hide();
	}
	else
		std::cerr << "Need a path" << std::endl;
}

void MyWindow::pve()
{
	if (is_folder)
	{
		mode = "pve";
		hide();
	}
	else
		std::cerr << "Need a path" << std::endl;
}

void MyWindow::help()
{
	if (is_folder)
	{
		mode = "help";
		hide();
	}
	else
		std::cerr << "Need a path" << std::endl;
}

void MyWindow::input()
{
	folder_path = folder.get_string();
	is_folder = true;
}

void MyWindow::attach_warnings(int& warningNow, const std::string& s, std::vector<Graph_lib::Text*>& warnings, int warningX)
{
	if (warningNow > 1000)
		clear_warning();
	warnings.push_back(new Graph_lib::Text({ warningX, warningNow }, "Wrong postition"));
	warnings[warnings.size() - 1]->set_color(Graph_lib::Color::red);
	warnings[warnings.size() - 1]->set_font_size(35);
	attach(*warnings[warnings.size() - 1]);
	warningNow += 30;
}

bool MyWindow::add_position(field_point p1, field_point p2)
{
	if (p1.first == p2.first)
	{
		if (ship_count[abs(p1.second - p2.second) + 1] == 0)
		{
			attach_warnings(warningNow, "Ship is full", warnings, warningX);
			return false;
		}
		if (position[p1.first][p1.second] != 0)
		{
			attach_warnings(warningNow, "Wrong position", warnings, warningX);
			return false;
		}
		else
		{
			if (p1.first != 0)
				if (position[p1.first - 1][p1.second] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.first != 9)
				if (position[p1.first + 1][p1.second] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.second != 0)
				if (position[p1.first][p1.second - 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if(p1.second != 0 and p1.first != 0)
				if (position[p1.first - 1][p1.second - 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.second != 0 and p1.first != 9)
				if (position[p1.first + 1][p1.second - 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
		}
		for (int i = p1.second; i <= p2.second; ++i)
		{
			if (i != 9)
			{
				if (p1.first != 0)
					if (position[p1.first - 1][i + 1] != 0)
					{
						attach_warnings(warningNow, "Wrong position", warnings, warningX);
						return false;
					}
				if (p1.first != 9)
					if (position[p1.first + 1][i + 1] != 0)
					{
						attach_warnings(warningNow, "Wrong position", warnings, warningX);
						return false;
					}
				if (position[p1.first][i + 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			}
			position[p1.first][i] = 1;
		}
		ship_count[abs(p1.second - p2.second) + 1]--;
	}
	else if (p1.second == p2.second)
	{
		if (ship_count[abs(p1.first - p2.first) + 1] == 0)
		{
			attach_warnings(warningNow, "Ship is full", warnings, warningX);
			return false;
		}
		if (position[p1.first][p1.second] != 0)
		{
			attach_warnings(warningNow, "Wrong position", warnings, warningX);
			return false;
		}
		else
		{
			if (p1.second != 0)
				if (position[p1.first][p1.second - 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.second != 9)
				if (position[p1.first][p1.second + 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.first != 0)
				if (position[p1.first - 1][p1.second] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.second != 0 and p1.first != 0)
				if (position[p1.first - 1][p1.second - 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			if (p1.second != 9 and p1.first != 0)
				if (position[p1.first - 1][p1.second + 1] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
		}
		for (int i = p1.first; i <= p2.first; ++i)
		{
			if (i != 9)
			{
				if (p1.second != 0)
					if (position[i + 1][p1.second - 1] != 0)
					{
						attach_warnings(warningNow, "Wrong position", warnings, warningX);
						return false;
					}
				if (p1.second != 9)
					if (position[i + 1][p1.second + 1] != 0)
					{
						attach_warnings(warningNow, "Wrong position", warnings, warningX);
						return false;
					}
				if (position[i + 1][p1.second] != 0)
				{
					attach_warnings(warningNow, "Wrong position", warnings, warningX);
					return false;
				}
			}
			position[i][p1.second] = 1;
		}
		ship_count[abs(p1.first - p2.first) + 1]--;
	}
	return true;
}

bool MyWindow::is_full()
{
	for (auto [a, b] : ship_count)
		if (b != 0)
			return false;
	return true;
}