#include "Engine.h"

void start()
{
	std::string mode = "";
	while (mode != "pvp")
	{
		MyWindow menu({ 500 , 100 }, 800, 800);
		Graph_lib::gui_main();
		mode = menu.get_mode();
	}
	std::cout << mode;
}