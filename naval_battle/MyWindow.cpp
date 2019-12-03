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
	attach(*ship[ship.size()-1]); 

	for (int i = Start.first - 1; i < End.first; ++i)
		for (int j = Start.second - 1; j < End.second; ++j)
			position[i][j] = 1;

	redraw();
}



