#include "Engine.h"

void start();

void mods(const std::string& folder_path, std::string& mode)
{
	if (mode == "pvp")
	{
		Field player1{ {0,0}, 1920, 1080, "player 1" , folder_path };
		player1.hide();
		Field player2{ {0,0}, 1920, 1080, "player 2" , folder_path };
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
				}
			}
			if (player1.get_smn_win() or player2.get_smn_win())
			{
				player1.hide();
				player2.hide();
				mode = "quit";
				start();
			}
		}
	}
}

void change_mode()
{
	std::string mode;
	std::string folder_path;
	while (mode != "pvp" and mode != "help" and mode != "quit")
	{
		MyWindow menu({ 500 , 100 }, 800, 800);
		Graph_lib::gui_main();
		mode = menu.get_mode();
		folder_path = find_path();
	}

	mods(folder_path, mode);
}

void start()
{
	change_mode();
}


