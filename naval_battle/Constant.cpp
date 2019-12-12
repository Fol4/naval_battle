#include "Constant.h"

int random_int(int a)
{
	return (rand() / double(RAND_MAX)) * a;
}