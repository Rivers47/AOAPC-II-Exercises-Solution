#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
	int n;
	unsigned int s[1000];
	while (cin >> n)
	{
		for (int i = 0; i < n; i++)
		{
			s[i] = 0;
			for (int k = 3; k >= 0; k--)
			{
				int x;
				cin >> x;
				cin.ignore(1, '.');
				s[i] += x << k * 8;
			}
		}


		unsigned int mask = -1;

		for (int k = 1; k < 32; k++)
		{
			mask <<= k;
			unsigned com1 = s[0] & mask;

			for (int i = 1; i < n; i++)
			{
				unsigned int com1 = s[0] & mask;
				unsigned int com2 = s[i] & mask;
				if (com1 == com2)
					continue;
			}
		}


		unsigned lowestIPAddress = s[0] & mask;
		unsigned char mask1[4] =
		{
			mask >> 24,mask >> 16,mask >> 8,mask
		};
		printf("%d.%d.%d.%d\n%d.%d.%d.%d\n", lowestIPAddress >> 24, (lowestIPAddress >> 16) & 0xff, (lowestIPAddress >> 8) & 0xff, lowestIPAddress & 0xff, mask1[0], mask1[1], mask1[2], mask1[3]);

	}
	return 0;
}
