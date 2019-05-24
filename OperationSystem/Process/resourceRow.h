#pragma once
#include<string>
#include<sstream>
//extern const unsigned ROW_COUNT = 4;
//extern const unsigned MAX_PROCESS = 512;
//extern HANDLE mutex;
//extern HANDLE Rmutex;
//extern Container* container;

const unsigned ROW_COUNT = 4;
const unsigned MAX_PROCESS = 512;

struct ResourceRow
{
public:
	unsigned res[ROW_COUNT];
	ResourceRow()
	{
		for (unsigned i = 0; i < ROW_COUNT; ++i)
		{
			res[i] = 0;
		}
	}
	ResourceRow(unsigned* input)
	{
		for (int i = 0; i < ROW_COUNT; ++i)
		{
			res[i] = input[i];
		}
	}
	std::string str()
	{
		std::stringstream res;
		for (unsigned i = 0; i < ROW_COUNT; ++i)
		{
			res << this->res[i] << " ";
		}
		return res.str();
	}
};
bool operator>=(const ResourceRow& a, const ResourceRow& b);