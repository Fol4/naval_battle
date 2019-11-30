#pragma once
#include "Constant.h"

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Ship : public Image
{
public:
	Ship (int amount, direction dir);
private:
	int amount;
	Direction dir;