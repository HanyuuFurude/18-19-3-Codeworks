#include"resourceRow.h"
bool operator>=(const ResourceRow& a, const ResourceRow& b)
{
	for (int i = 0; i < ROW_COUNT; ++i)
	{
		if (a.res[i] < b.res[i])
			return false;
	}
	return true;
}