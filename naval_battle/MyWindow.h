#pragma once 
#include "Ship.h"


struct MyWindow : public Graph_lib::Window
{
	MyWindow(Graph_lib::Point p, int w, int h,
		const std::string& title);

	void add_position(field_point p1, field_point p2);

protected:
	std::vector<Ship*> ship;
	std::vector<field_point> ship_position;

	std::vector<Graph_lib::Rectangle*> fire;
	std::vector<field_point> fire_cord;

	std::vector<std::vector<int>> position =
		matrix_2d<int>(10, 10, 0);
private:
	Graph_lib::Button quit_button;
	Graph_lib::Button next_button;
	Graph_lib::In_box start;
	Graph_lib::In_box end;

	void quit() { hide(); }
	void next();
};
