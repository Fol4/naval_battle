#include "FieldChunck.h"

using namespace std;
using namespace Graph_lib;

FieldChunck::FieldChunck(Graph_lib::Point p, Graph_lib::Callback cb, int size):
	Button{ p, size, size, "", cb },
	Graph_lib::Rectangle(p, size, size)
{
}

void FieldChunck::attach(Graph_lib::Window& win)
{
	Button::attach(win);
}