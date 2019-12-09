#include "Engine.h"

bool can(const std::vector<std::vector<int>>& position, int cnt, int direction , int x, int y)
{
	if (direction == 1)
	{
		if (y + cnt > 10)
			return false;
		if (position[x][y] != 0)
		{
			return false;
		}
		else
		{
			if (x != 0)
				if (position[x - 1][y] != 0)
				{
					return false;
				}
			if (x != 9)
				if (position[x][y] != 0)
				{
					return false;
				}
			if (y != 0)
				if (position[x][y - 1] != 0)
				{
					return false;
				}
			if (y != 0 and x != 0)
				if (position[x - 1][y - 1] != 0)
				{
					return false;
				}
			if (y != 0 and x != 9)
				if (position[x + 1][y - 1] != 0)
				{
					return false;
				}
		}
		for (int i = y; i < y+cnt; ++i)
		{
			if (i != 9)
			{
				if (x != 0)
					if (position[x - 1][i + 1] != 0)
					{
						return false;
					}
				if (x != 9)
					if (position[x + 1][i + 1] != 0)
					{
						return false;
					}
				if (position[x][i + 1] != 0)
				{
					return false;
				}
			}
			else
				return false;
		}
	}
	else
	{
		if (x + cnt > 10)
			return false;
		if (position[x][y] != 0)
		{
			return false;
		}
		else
		{
			if (y != 0)
				if (position[x][y - 1] != 0)
				{
					return false;
				}
			if (y != 9)
				if (position[x][y + 1] != 0)
				{
					return false;
				}
			if (x != 0)
				if (position[x - 1][y] != 0)
				{
					return false;
				}
			if (y != 0 and x != 0)
				if (position[x - 1][y - 1] != 0)
				{
					return false;
				}
			if (y != 9 and x != 0)
				if (position[x - 1][y + 1] != 0)
				{
					return false;
				}
		}
		for (int i = x; i < x+cnt; ++i)
		{
			if (i != 9)
			{
				if (y != 0)
					if (position[i + 1][y - 1] != 0)
					{
						return false;
					}
				if (y != 9)
					if (position[i + 1][y + 1] != 0)
					{
						return false;
					}
				if (position[i + 1][y] != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int random_int(int a)
{
	return (rand() / double(RAND_MAX)) * a;
}

void delete_point(std::vector<field_point>& all, int x, int y)
{
	bool d = false;
	for (int i = 0; i < all.size(); ++i)
	{
		if (d)
		{
			all[i - 1].first = all[i].first;
			all[i - 1].second = all[i].second;
		}
		if (all[i].first == x and all[i].second == y)
			d = true;
	}
	all.pop_back();
}

void fill(std::vector<field_point>& all, std::vector<std::vector<int>>& position, int x, int y, int direction, int cnt)
{
	if (direction == 1)
	{
		if (y != 0)
		{
			if (x != 0)
			{
				position[x - 1][y - 1] = 2;
				delete_point(all, x-1, y-1);
			}
			if (x != 9)
			{
				position[x + 1][y - 1] = 2;
				delete_point(all, x+1, y-1);
			}
			position[x][y - 1] = 2;
			delete_point(all, x, y-1);
		}
		for (int i = y; i <= y + cnt; ++i)
		{
			if (x != 0)
			{
				position[x - 1][i] = 2;
				delete_point(all, x-1, i);
			}
			if (x != 9)
			{
				position[x + 1][i] = 2;
				delete_point(all, x+1, i);
			}
			position[x][i] = 1;
			delete_point(all, x, i);
		}
		if (y + cnt != 9)
		{
			if (x != 0)
			{
				position[x - 1][y + cnt + 1] = 2;
				delete_point(all, x - 1, y + cnt + 1);
			}
			if (x != 9)
			{
				position[x + 1][y + cnt + 1] = 2;
				delete_point(all, x+1, y+cnt + 1);
			}
			position[x][y + cnt + 1] = 2;
			delete_point(all, x, y+cnt + 1);
		}
	}
	else
	{
		if (x != 0)
		{
			if (y != 0)
			{
				position[x - 1][y - 1] = 2;
				delete_point(all, x-1, y - 1);
			}
			if (y != 9)
			{
				position[x - 1][y + 1] = 2;
				delete_point(all, x+1, y-1);
			}
			position[x - 1][y] = 2;
			delete_point(all, x, y-1);
		}
		for (int i = x; i <= x+cnt; ++i)
		{
			if (y != 0)
			{
				position[i][y - 1] = 2;
				delete_point(all, i, y-1);
			}
			if (y != 9)
			{
				position[i][y + 1] = 2;
				delete_point(all, i, y+1);
			}
			position[i][y] = 1;
			delete_point(all, i, y);
		}
		if (x + cnt!= 9)
		{
			if (y != 0)
			{
				position[x + cnt + 1][y - 1] = 2;
				delete_point(all, x + cnt + 1, y - 1);
			}
			if (y != 9)
			{
				position[x + cnt + 1][y + 1] = 2;
				delete_point(all, x + cnt + 1, y + 1);
			}
			position[x + cnt + 1][y] = 2;
			delete_point(all, x, y);
		}
	}
}

std::vector<std::vector<int>> bot_field()
{
	std::vector<std::vector<int>> position =
		matrix_2d<int>(10, 10, 0);
	std::vector<field_point> all;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			all.push_back({ i,j });
	int i = 0;
	int  j = 0;
	while (i < 2)
	{
		j = i;
		while (j < 4)
		{
			int p = random_int(all.size() - 1);
			int x = all[p].first;
			int y = all[p].second;
			int direction = random_int(2);
			while (direction == 2)
				direction = random_int(2);

			if (can(position, i + 1, direction, x, y))
			{
				fill(all, position, x, y, direction, i);
				j++;
			}
		}
		i++;
	}
	while (i < 4)
	{
		j = i;
		while (j < 4)
		{
			int direction;
			int x;
			int y;
			for (int i1 = 0; i1 < 10; i1++)
				for (int j1 = 0; j1 < 10; j1++)
				{
					if (position[i1][j1] == 0)
					{
						int d1 = 0;
						int d2 = 0;
						for (int c = 0; c < i + 1; ++c)
						{
							if (j1 + c < 10)
								d1 += position[i1][j1 + c];
							else
								d1 = 1;
							if (i1 + c < 10)
								d2 += position[i1 + c][j1];
							else
								d2 = 1;
						}
						if (d1 == 0)
						{
							x = i1;
							y = j1;
							direction = 1;
						}
						else if (d2 == 0)
						{
							x = i1;
							y = j1;
							direction = 0;
						}
					}
				}
			fill(all, position, x, y, direction, i);
			j++;
		}
		i++;
	}

	return position;
}

void start()
{
	std::string mode;
	std::string folder_path;
	while (mode != "pvp" and mode != "pve" and mode != "help" and mode != "quit")
	{
		MyWindow menu({ 500 , 100 }, 800, 800);
		Graph_lib::gui_main();
		mode = menu.get_mode();
		folder_path = menu.get_folder();
	}

	if (mode == "pvp")
	{
		Field player1{ {0,0}, 1920, 1080, "player 1" , folder_path};
		player1.hide();
		Field player2{ {0,0}, 1920, 1080, "player 2" , folder_path};
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
	else if (mode == "pve")
	{
		std::vector<std::vector<int>> position = bot_field();

		for (int i1 = 0; i1 < 10; ++i1)
		{
			for (int j1 = 0; j1 < 10; ++j1)
				std::cout << position[i1][j1] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}