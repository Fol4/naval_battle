#pragma once 
#include "Ship.h"
struct MyWindow : Graph_lib::Window
{
	MyWindow(Graph_lib::Point p, int w, int h, int size, 
		int start_x, int start_y, const std::string& title);
	MyWindow(Graph_lib::Point p, int w, int h);

	void add_position(field_point p1, field_point p2);
	std::string get_mode() { return mode; };
	bool is_full();

	std::vector<Ship*> ship;
	std::vector<field_point> ship_position;
	std::vector<std::vector<int>> position =
		matrix_2d<int>(10, 10, 0);

protected:
	std::map<int, int> ship_count = { {1,0}, {2,0}, {3,1}, {4,0} };

	std::vector<Graph_lib::Image*> fire;
	std::vector<Graph_lib::Image*> cross;
private:
	Graph_lib::Button* quit_button;
	Graph_lib::Button* next_button;
	Graph_lib::Button* pvp_button;
	Graph_lib::Button* pve_button;
	Graph_lib::Button* help_button;
	Graph_lib::Button* input_button;
	Graph_lib::In_box start;
	Graph_lib::In_box end;
	Graph_lib::In_box folder;

	int squareLenght;
	int startX;
	int startY;
	std::string mode;
	std::string folder_path;
	bool is_folder = false;


	void quit() { hide(); mode = "quit"; }
	void next();
	void pvp();
	void pve();
	void help();
	void input();
};