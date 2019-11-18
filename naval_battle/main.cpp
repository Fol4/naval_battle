#include "MyWindow.h"

using namespace std;
using namespace Graph_lib;

int main()
try
{
	MyWindow win{ {100, 100}, 800, 800, "test" };

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