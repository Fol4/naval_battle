#include "Field.h"


int main()
try
{
	Field f({ 0,0 }, 1920, 1080, "field");

	f.draw_minifield();

	return Graph_lib::gui_main();
}
catch (std::exception & e)
{
	std::cerr << e.what() << std::endl;
	return 1;
}
catch (...)
{
	std::cerr << "Oops, something went wrong..." << std::endl;
	return 2;
}