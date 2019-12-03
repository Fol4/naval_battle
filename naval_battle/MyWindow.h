#pragma once 
#include "Ship.h"


struct MyWindow : public Graph_lib::Window
{
	MyWindow(Graph_lib::Point p, int w, int h,
		const std::string& title);

	void add_position(field_point p1, field_point p2);
	bool is_ship(field_point p1) { return position[p1.first][p1.second]; }
	void change_status(field_point p1) { position[p1.first][p1.second] = 2; }

	std::vector<std::vector<Graph_lib::Rectangle>> fire;
private:
	Graph_lib::Button quit_button;
	Graph_lib::Button next_button;
	Graph_lib::In_box start;
	Graph_lib::In_box end;
	std::vector<Ship*> ship;
	std::vector<field_point> ship_postition;
	std::vector<std::vector<int>> position =
		matrix_2d<int>(10, 10, 0);

	void quit() { hide(); }
	void next();
};
