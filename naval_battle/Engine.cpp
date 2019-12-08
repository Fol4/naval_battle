#include "Engine.h"

void start()
{
	std::string mode;
	while (mode != "pvp" and mode != "pve" and mode != "help" and mode != "quit")
	{
		MyWindow menu({ 500 , 100 }, 800, 800);
		Graph_lib::gui_main();
		mode = menu.get_mode();
	}

	if (mode == "pvp")
	{
		bool second = false;
		Field player1{ {0,0}, 1920, 1080, "player 1" };
		player1.hide();
		Field player2{ {0,0}, 1920, 1080, "player 2" };
		player2.hide();
		for (int i = 0; mode != "quit"; ++i)
		{
			if (i % 2 == 0)
			{
				if (player2.get_first())
				{
					player2.show();
					Graph_lib::gui_main();
					mode = player2.get_mode();
				}
				else
				{
					player1.show();
					Graph_lib::gui_main();
					mode = player1.get_mode();
					if (player1.all_ship() == 0)
					{
						std::cout << "1 You won" << std::endl;
						break;
					}
				}
			}
			else
			{
				if (player1.get_first())
				{
					player1.show();
					Graph_lib::gui_main();
					mode = player1.get_mode();
				}
				else
				{
					player2.show();
					Graph_lib::gui_main();
					mode = player2.get_mode();
					if (player2.all_ship() == 0)
					{
						std::cout << "2 You won" << std::endl;
						break;
					}
				}
			}
		}
	}
}