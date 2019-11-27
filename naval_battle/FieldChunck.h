#pragma once
#include "MyWindow.h"

class FieldChunck: public Graph_lib::Button, public Graph_lib::Rectangle
{
public:
	enum Type{empty, busy};

	FieldChunck(Graph_lib::Point p, Graph_lib::Callback cb, Type t, int l);

	bool is_busy() { return type == busy; }
	void activate();
	void deactivate();
private:
	Type type;
};

