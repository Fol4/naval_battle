#pragma once
#include "MyWindow.h"

class Field : public MyWindow
{
public:
	Field(Graph_lib::Point p, int w, int h, const std::string& t, const std::string& fp);

	void clicked(Graph_lib::Address widget);
	void destroy_ship();
	void surround(field_point p1, field_point p2);
	int get_squareLenght() { return squareLenght; }
	bool get_first() { return first; }
	bool get_smn_win() { return smn_win; }
	void draw_button();
	bool ship_destroyed();
	void clear_ship();
	void clear_field();
	int all_ship();
private:
	Graph_lib::Button* next_turn_button;
	Graph_lib::Button* win_button;
	Graph_lib::Image win_image{ {width / 5, height / 3}, folder_path + "win_image.jpg" };
	Graph_lib::Rectangle win_background{ {0,0}, 1920, 1080 };

	std::vector<std::vector<Graph_lib::Button*>> fieldB;
	std::vector<std::vector<Graph_lib::Image*>> fieldR;
	std::vector<Graph_lib::Text*> horizontal;
	std::vector<Graph_lib::Text*> vertical;

	int squareLenght;
	int startX;
	int startY;
	int width;
	int height;
	std::string title;
	bool first = true;
	bool turn_down = false;
	bool smn_win = false;

	void next_turn();
	void win();
};


