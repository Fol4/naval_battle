#include "Engine.h"


int main()
try
{
	start();

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