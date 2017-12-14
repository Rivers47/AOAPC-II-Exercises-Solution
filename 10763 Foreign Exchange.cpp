#include <cstdio>
#include <map>
#include <iostream>
using namespace std;


void skipLines(unsigned int n)
{
	n += 1;
	while (n--)
		cin.ignore(100, '\n');
}

int main()
{
	int n;
	while (scanf("%d", &n) && n != 0)
	{
		if (n % 2)
		{
			skipLines(n);
			printf("NO\n");
			//The current case is ignored
			continue;
		}
		
		map<pair<int,int>, int> student;

		for (int i = 0; i < n; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			pair<int, int> s{ b,a };
			if (student.count(s))
				student.erase(s);
			else
				student[{a, b}]++;
		}

		bool workOut = true;
		for (auto s : student)
		{
			if (s.second % 2)
			{
				printf("NO\n");
				workOut = false;
				break;
			}
		}
		if (workOut)
			printf("YES\n");
	}
	return 0;
}
