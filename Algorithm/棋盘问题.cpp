//	棋盘问题
//在一个给定形状的棋盘（形状可能是不规则的）上面摆放棋子，棋子没有区别。要求摆放时任意的两个棋子不能放在棋盘中的同一行或者同一列，请编程求解对于给定形状和大小的棋盘，摆放k个棋子的所有可行的摆放方案C。
//Input
//输入含有多组测试数据。
//每组数据的第一行是两个正整数，n k，用一个空格隔开，表示了将在一个n* n的矩阵内描述棋盘，以及摆放棋子的数目。 n <= 8, k <= n
//当为 - 1 - 1时表示输入结束。
//随后的n行描述了棋盘的形状：每行有n个字符，其中 # 表示棋盘区域，.表示空白区域（数据保证不出现多余的空白行或者空白列）。
//Output
//对于每一组数据，给出一行输出，输出摆放的方案数目C （数据保证C < 2 ^ 31）。
//	Sample Input
//
//	2 1
//#.
//	.#
//	4 4
//	...#
//	..#.
//	.#..
//#...
//	- 1 - 1
//
//	Sample Output
//
//	2
//	1
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<string>
#include<stdio.h>
#include<vector>
using namespace std;

int search(int no, int number, int size, int up, int down, char avilable[8][8], int root[]);
bool noconf(int x, int layer, int root[]);
void vj()
{
	//bool flag = false;
	int root[8];
	char avilable[8][8];
	vector<int>res;
	while (true)
	{
		int size = 0, number = 0;
		char* ssize = new char[5], * snumber = new char[5];
		cin >> ssize;
		cin >> snumber;
		size = atoi(ssize); number = atoi(snumber);
		if (size == -1 && number == -1) { 
			for (vector<int>::iterator iter = res.begin(); iter != res.end(); iter++)
			{
				cout << *iter << endl;
			}
			return;
		}
		if (size < number) { cout << 0 << endl; continue; }
		for (int i = 0; i < size; ++i)
		{
			cin >> avilable[i];
			root[i] = -1;
		}
		res.push_back(search(0, number, size, 0, size - number, avilable, root));
	}
}
int search(int no, int number, int size, int up, int down, char avilable[8][8], int root[])
{
	int sum = 0;
	for (int i = up; i <= down; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (avilable[i][j] == '#' && noconf(j, i, root))
			{
				if (no == number -1)
				{
					sum += 1;
				}
				else 
				{
					root[i] = j;
					sum += search(i + 1, number, size, i + 1, size - (number - no - 1), avilable, root);
					root[i] = -1;
				}
			}
		}
	}
	return sum;
}
inline bool noconf(int x, int layer, int root[])
{
	for (int i = 0; i < layer; ++i)
	{
		if (root[i] == x)
			return false;
	}
	return true;
}
int main()
{
	vj();

}