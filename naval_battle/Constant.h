#pragma once
#include <iostream>
#include <sstream>
#include <cmath>
#include <string.h>
#include <exception>
#include <cmath>
#include "Graph.h"
#include "Simple_window.h"

template <typename T>
std::vector<T> matrix_1d(int l, T fill = 0)
{
	std::vector<T> res(l);
	for (int i = 0; i < l; ++i)
	{
		res[i] = fill;
	}
	return res;
}

template <typename T>
std::vector<std::vector<T>> matrix_2d(int h, int l, T fill = 0)
{
	std::vector<std::vector<T>> res(h, matrix_1d(l, fill));
	return res;
} 

struct point
{
	int x;
	int y;
	point(int xx, int yy) : x{ xx }, y{ yy } {}
};

constexpr int cell_size{ 70 };
constexpr int start_x = 100;
constexpr int start_y = 100;
