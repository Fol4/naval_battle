#include "MyWindow.h"

MyWindow::MyWindow(Graph_lib::Point p, int w, int h, const std::string& title) :
	Window{ p, w, h, title  },
	quit_button{ Graph_lib::Point{x_max() - 100, 10}, 70, 20, "Quit",
	[](Graph_lib::Address, Graph_lib::Address pw) {
							 Graph_lib::reference_to<MyWindow>(pw).quit();
							 }
				},
	next_button{ Graph_lib::Point{420, 10}, 70, 20, "Next",
	[](Graph_lib::Address , Graph_lib::Address pw) {
							  Graph_lib::reference_to<MyWindow>(pw).next();
							  }
				},
	start{ Graph_lib::Point {100, 10}, 100, 20, "Ship Start" },
	end{ Graph_lib::Point { 300, 10}, 100, 20, "Ship End" }

{
	attach(quit_button);
	attach(next_button);
	attach(start);
	attach(end);
}

void MyWindow::next()
{
	std::string StartCord = start.get_string();
	std::string EndCord = end.get_string();

	field_point Start = string_to_point(StartCord);
	field_point End = string_to_point(EndCord);

	ship.push_back(new Ship(Start, End)); 
	attach(*ship[ship.size() - 1]);
	ship_postition.push_back(Start);
	add_position(Start, End);

	redraw();
}

void MyWindow::add_position(field_point p1, field_point p2)
{
	if (p1.first == p2.first)
	{
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
	}
	if (p1.second == p2.second)
	{
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
	}
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			std::cout << position[j][i] << " ";
		std::cout << std::endl;
	}
}