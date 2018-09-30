#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;


int main()
{
	//because both cstdin and iostream are used, this following line cannot be used
	//cin.tie(0); cin.sync_with_stdio(0);
	int kase = 1;
	while(1)
	{
		
		int depth;
		scanf("%d", &depth);
		if (depth == 0)
			break;
		printf("S-Tree #%d:\n", kase++);
		int i=0, order[10];
		char s[100];
		cin.ignore();
		cin.getline(s, 100);
		
		for (int k = 0;i < depth ;k++)
		{
			if (s[k] == 'x')
				order[i++] = s[k + 1]-48;
		}

			

		int nNodes = pow(2, depth);
		char nodes[150];
		i = 0;
		scanf("%s", nodes);

		int query;
		cin >> query;
		char VVA[10];
		while (query--)
		{
			cin >> VVA;
			int rightOrder[10];
			for(i = 0; i < depth; i++)
			{
				rightOrder[i] = VVA[order[i]-1]-48;
			}

		

			int left = 1, right = nNodes;
			for(i = 0; i < depth; i++)
			{
				if (!rightOrder[i])	//left
				{
					right = right - (right - left + 1) / 2;
				}
				else
				{
					left = left + (right - left + 1) / 2;
				}
			}
			cout << nodes[left-1];
		}
		cout << "\n\n";
	}

	return 0;
}
