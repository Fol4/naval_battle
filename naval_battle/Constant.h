#pragma once
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <string.h>
#include <exception>
#include <random>
#include <ctime>
#include "Graph.h"
#include "Simple_window.h"

#define field_point std::pair<int, int>

const std::string find_path();

int random_int(int a);

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

constexpr int cell_size{ 70 };
