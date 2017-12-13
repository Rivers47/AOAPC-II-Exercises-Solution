#include <cstdio>
#include <set>
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
			printf("NO\n");
			skipLines(n);	//The current case is ignored
			continue;
		}
		map<set<int>,int> student;
		for (int i = 0; i < n; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			set<int> s;
			s.insert(a); s.insert(b);
			student[s]++;
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
