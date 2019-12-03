#include "Field.h"

using namespace std;
using namespace Graph_lib;

int main()
try
{
	Field f{ {start_x,start_y}, cell_size, "Field" };

	return gui_main();
}
catch (std::exception & e)
{
	cerr << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Oops, something went wrong..." << endl;
	return 2;
}