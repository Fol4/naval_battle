#pragma once 
#include "Constant.h"

struct MyWindow : Graph_lib::Window
{
	MyWindow(Graph_lib::Point p, int w, int h, const std::string& title);

private:
	void quit() { hide(); }
	void next () {}

	Graph_lib::Button quit_button;
	Graph_lib::Button next_button;
	Graph_lib::In_box start;
	Graph_lib::In_box end;
};

