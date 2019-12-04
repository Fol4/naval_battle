#include "MyWindow.h"

MyWindow::MyWindow(Graph_lib::Point p, int w, int h, const std::string& title) :
	Window{ p, w, h, title  },
	quit_button{new Graph_lib::Button( Graph_lib::Point{x_max() - 100, 10}, 70, 20, "Quit",
	[](Graph_lib::Address, Graph_lib::Address pw) {
							 Graph_lib::reference_to<MyWindow>(pw).quit();
							 }
				)},
	next_button{new Graph_lib::Button( Graph_lib::Point{420, 10}, 70, 20, "Next",
	[](Graph_lib::Address , Graph_lib::Address pw) {
							  Graph_lib::reference_to<MyWindow>(pw).next();
							  }
				)},

	start{Graph_lib::Point {100, 10}, 100, 20, "Ship Start" },
	end{Graph_lib::Point { 300, 10}, 100, 20, "Ship End" },
	folder{Graph_lib::Point{w / 10, 3 * h / 4}, 3 * w / 4, w / 20, "Path"}
{
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
	std::string StartCord = start.get_string();
	std::string EndCord = end.get_string();

	field_point Start = string_to_point(StartCord);
	field_point End = string_to_point(EndCord);

	add_position(Start, End);
	ship.push_back(new Ship(Start, End)); 
	attach(*ship[ship.size()-1]); 
	ship_position.push_back(Start);

	redraw();
}

void MyWindow::pvp() 
{
	if (is_folder)
	{
		mode = "pvp";
		hide();
	}
	else
		std::cerr << "Need a path";
}

void MyWindow::pve()
{
	if (is_folder)
	{
		mode = "pve";
		hide();
	}
	else
		std::cerr << "Need a path";
}

void MyWindow::help()
{
	if (is_folder)
	{
		mode = "help";
		hide();
	}
	else
		std::cerr << "Need a path";
}

void MyWindow::input()
{
	folder_path = folder.get_string();
	is_folder = true;
}

void MyWindow::add_position(field_point p1, field_point p2)
{
	if (p1.first == p2.first)
	{
		if (ship_count[abs(p1.second - p2.second) + 1] == 0)
			throw std::runtime_error("Ship is full");
		if (position[p1.first][p1.second] != 0)
			throw std::runtime_error("Wrong postition");
		else
		{
			if (p1.first != 0)
				if (position[p1.first - 1][p1.second] != 0)
					throw std::runtime_error("Wrong postition");
			if (p1.first != 9)
				if (position[p1.first + 1][p1.second] != 0)
					throw std::runtime_error("Wrong postition");
			if (p1.second != 0)
				if (position[p1.first][p1.second - 1] != 0)
					throw std::runtime_error("Wrong postition");
		}
		for (int i = p1.second; i <= p2.second; ++i)
		{
			if (i != 9)
			{
				if (p1.first != 0)
					if (position[p1.first - 1][i + 1] != 0)
						throw std::runtime_error("Wrong postition");
				if (p1.first != 9)
					if (position[p1.first + 1][i + 1] != 0)
						throw std::runtime_error("Wrong postition");
				if (position[p1.first][i + 1] != 0)
					throw std::runtime_error("Wrong postition");
			}
			position[p1.first][i] = 1;
		}
		ship_count[abs(p1.second - p2.second) + 1]--;
	}
	else if (p1.second == p2.second)
	{
		if (ship_count[abs(p1.first - p2.first) + 1] == 0)
			throw std::runtime_error("Ship is full");
		if (position[p1.first][p1.second] != 0)
			throw std::runtime_error("Wrong postition");
		else
		{
			if (p1.second != 0)
				if (position[p1.first][p1.second - 1] != 0)
					throw std::runtime_error("Wrong postition");
			if (p1.second != 9)
				if (position[p1.first][p1.second + 1] != 0)
					throw std::runtime_error("Wrong postition");
			if (p1.first != 0)
				if (position[p1.first - 1][p1.second] != 0)
					throw std::runtime_error("Wrong postition");
		}
		for (int i = p1.first; i <= p2.first; ++i)
		{
			if (i != 9)
			{
				if (p1.second != 0)
					if (position[i + 1][p1.second - 1] != 0)
						throw std::runtime_error("Wrong postition");
				if (p1.second != 9)
					if (position[i + 1][p1.second + 1] != 0)
						throw std::runtime_error("Wrong postition");
				if (position[i + 1][p1.second] != 0)
					throw std::runtime_error("Wrong postition");
			}
			position[i][p1.second] = 1;
		}
		ship_count[abs(p1.first - p2.first) + 1]--;
	}
}
