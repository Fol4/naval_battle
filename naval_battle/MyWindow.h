#pragma once 
#include "Ship.h"
struct MyWindow : Graph_lib::Window
{
	MyWindow(Graph_lib::Point p, int w, int h, int size, 
		int start_x, int start_y, const std::string& title, const std::string& fp);
	MyWindow(Graph_lib::Point p, int w, int h);

	bool add_position(field_point p1, field_point p2);
	std::string get_mode() { return mode; };
	bool is_full();
	void clear_warning() { for (auto i : warnings) detach(*i);  warnings.clear(); warningNow = 1080 / 8 + 30;}
	void attach_warnings(int& warningNow, const std::string& s, std::vector<Graph_lib::Text*>& warnings, int warningX);
	std::string get_folder() { return folder_path; }
	field_point string_to_point(const std::string& s);
	std::vector<Ship*> ship;
	std::vector<field_point> ship_position;
	std::vector<std::vector<int>> position =
		matrix_2d<int>(10, 10, 0);

protected:
	std::map<int, int> ship_count = { {1,4}, {2,3}, {3,2}, {4,1} };

	std::vector<Graph_lib::Image*> fire;
	std::vector<Graph_lib::Image*> cross;
	std::vector<Graph_lib::Text*> warnings;
	int warningX;
	int warningNow;
	std::string folder_path;
	Graph_lib::Button* random_button;
	Graph_lib::Button* quit_button;
	Graph_lib::Button* next_button;
	Graph_lib::Button* pvp_button;
	Graph_lib::Button* help_button;
	Graph_lib::Button* input_button;
	Graph_lib::In_box start;
	Graph_lib::In_box end;
	Graph_lib::In_box folder;
	Graph_lib::Rectangle* warning;
private:
	int squareLenght;
	int startX;
	int startY;
	std::string mode;
	bool is_folder = false;


	void quit() { hide(); mode = "quit"; }
	void next();
	void pvp();
	void help();
	void input();
	void random_fun();
};