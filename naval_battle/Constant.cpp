#include "Constant.h"

int random_int(int a)
{
	return (rand() / double(RAND_MAX)) * a;
}

const std::string find_path()
{
	std::string path = __FILE__;
	std::vector<std::string> vresult;
	std::string result;
	for (int i = 0; i < path.length(); ++i)
		if (path[i] == '\\')
		{
			vresult.push_back(result);
			result = "";
		}
		else
		{
			result += path[i];
		}

	vresult.push_back(result);
	result = "";

	for (int i = 0; i < vresult.size(); ++i)
		if (vresult[i] == "naval_battle")
		{
			result += vresult[i] + "\\" + vresult[i] + "\\pic\\";
			break;
		}
		else
			result += vresult[i] + "\\";

	return result;
}