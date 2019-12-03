#pragma once
#include "MyWindow.h"

struct FieldChunck: public Graph_lib::Button, public Graph_lib::Rectangle
{
	FieldChunck(Graph_lib::Point p, Graph_lib::Callback cb, 
		int size);

	void attach(Graph_lib::Window& win) override;
};

