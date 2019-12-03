#include "Constant.h"

field_point string_to_point(const std::string& s)
{
	if (s.size() > 4 or s[s.size() - 2] != ':'
		or (s[0] < '0' or s[0] > '9') 
		or (s[s.size() - 1] < 'A' or  s[s.size() - 1] > 'J'))
		throw std::runtime_error("Wrong Input");
	int x = s[s.length() - 1] - 65;
	std::string strY = "";

	for (const auto& c : s)
		if (c == ':')
			break;
		else
			strY += c;

	int y = atoi(strY.c_str()) - 1;

	return { x,y };
}