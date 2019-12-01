#include "MyWindow.h"

using namespace std;
using namespace Graph_lib;

MyWindow::MyWindow(Point p, int w, int h, const std::string& title) :
	Graph_lib::Window{ p, w, h, title  },
	quit_button{ Point{x_max() - 100, 10}, 70, 20, "Quit",
	[](Address, Address pw) {
							 reference_to<MyWindow>(pw).next();
							 }
				},
	next_button{ Point{420, 10}, 70, 20, "Next",
	[](Address , Address pw) {
							  reference_to<MyWindow>(pw).quit();
							  }
				},
	start{ Point {100, 10}, 100, 20, "Ship Start" },
	end{ Point { 300, 10}, 100, 20, "Ship End" }

{
	attach(quit_button);
	attach(next_button);
	attach(start);
	attach(end);
}

point string_to_point(const string& s)
{
	int y { s[s.length] };
	string strX = "";

	for (const auto& c : s)
		if (c == ':')
			break;
		else
			strX += c;

	int x = atoi(strX.c_str());

	return { x,y };
}

void MyWindow::next()
{
	string StartCord = start.get_string();
	string EndCord = end.get_string();

	point Start = string_to_point(StartCord);
	point End = string_to_point(EndCord);

	Ship(Start, End);
	
}



