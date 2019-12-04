#include "Field.h"

using namespace std;
using namespace Graph_lib;

int main()
try
{
	Field f({ 0,0 }, 1920, 1080, "field");

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