//◊•≈£Œ Ã‚
//Farmer John has been informed of the location of a fugitive cowand wants to catch her immediately.He starts at a point N(0 °‹ N °‹ 100, 000) on a number lineand the cow is at a point K(0 °‹ K °‹ 100, 000) on the same number line.Farmer John has two modes of transportation : walking and teleporting.
//
//* Walking : FJ can move from any point X to the points X - 1 or X + 1 in a single minute
//* Teleporting : FJ can move from any point X to the point 2 °¡ X in a single minute.
//
//If the cow, unaware of its pursuit, does not move at all, how long does it take for Farmer John to retrieve it ?
//Input
//Line 1 : Two space - separated integers : N and K
//Output
//Line 1 : The least amount of time, in minutes, it takes for Farmer John to catch the fugitive cow.
//Sample Input
//
//5 17
//
//Sample Output
//
//4
//
//Hint
//The fastest way for Farmer John to reach the fugitive cow is to move along the following path : 5 - 10 - 9 - 18 - 17, which takes 4 minutes.

//
//Farmer John has been informed of the location of a fugitive cowand wants to catch her immediately.He starts at a point N(0 °‹ N °‹ 100, 000) on a number lineand the cow is at a point K(0 °‹ K °‹ 100, 000) on the same number line.Farmer John has two modes of transportation : walking and teleporting.
//
//* Walking : FJ can move from any point X to the points X - 1 or X + 1 in a single minute
//* Teleporting : FJ can move from any point X to the point 2 °¡ X in a single minute.
//
//If the cow, unaware of its pursuit, does not move at all, how long does it take for Farmer John to retrieve it ?
//Input
//Line 1 : Two space - separated integers : N and K
//Output
//Line 1 : The least amount of time, in minutes, it takes for Farmer John to catch the fugitive cow.
//Sample Input
//
//5 17
//
//Sample Output
//
//4
//
//Hint
//The fastest way for Farmer John to reach the fugitive cow is to move along the following path : 5 - 10 - 9 - 18 - 17, which takes 4 minutes.

#include<iostream>
#include<limits>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 100001;
class Hanyuu
{
public:
	int calc002()
	{
		int src, opt;
		cin >> src >> opt;
		unsigned count = 0;
		unsigned sum;
		vector<int> arr;
		arr.push_back(src);
		while (true)
		{
			count += 1;
			sum = arr.size();
			for (int i = 0; i < sum; ++i)
			{
				int org = arr[i];
				if (org - 1 > 0 && (org - 1) * 2 >= opt)
				{
					arr.push_back(org - 1);
					if (org - 1 == opt)
					{
						return count;
					}
				}
				if (org + 1 < SIZE && (org + 1) <= opt)
				{
					arr.push_back(org + 1);
					if (org + 1 == opt)
					{
						return count;
					}
				}
				if (org * 2 < SIZE && org <= opt)
				{
					arr.push_back(org * 2);
					if (org * 2 == opt)
					{
						return count;
					}
				}
			}
			sort(arr.begin(), arr.end());
			arr.erase(unique(arr.begin(), arr.end()), arr.end());
		}
	}
};
int main()
{
	Hanyuu exp;
	cout<<exp.calc002();
	return 0;
}

