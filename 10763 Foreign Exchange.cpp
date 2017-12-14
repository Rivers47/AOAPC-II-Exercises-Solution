#include <cstdio>
//#include <set>
//#include <unordered_set>
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
			NotWorkOut:	printf("NO\n");
			//The current case is ignored
			continue;
		}
		
		map<pair<int,int>, int> student;


		for (int i = 0; i < n / 2; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (a > b)
			{
				int c = a;
				a = b;
				b = c;
			}
			pair<int, int> s{ a,b };
			if (student.count(s))
				student.erase(s);
			else
				student[{a, b}];
		}
		for (int i = n / 2; i < n; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (a > b)
			{
				int c = a;
				a = b;
				b = c;
			}
			pair<int, int> s{ a,b };
			if (student.count(s))
				student.erase(s);
			else
				student[{a, b}];
			if (student.size() > n - i)
			{
				skipLines(n - i - 1);
				//The current case is ignored
				goto NotWorkOut;
			}
		}











		/*
		for (int i = 0; i < n / 2; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			pair<int, int> s{ b,a };
			if (student.count(s))
				student.erase(s);
			else
				student[{a, b}]++;
		}
		for (int i = n / 2; i < n; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			pair<int, int> s{ b,a };
			if (student.count(s))
				student.erase(s);
			else
				student[{a, b}]++;
			if (student.size() > n - i)
			{
				skipLines(n - i - 1);
				//The current case is ignored
				goto NotWorkOut;
			}
		}
		*/
		
		if(student.empty())
			printf("YES\n");
		else
			printf("NO\n");
		
		/*
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
		*/
	}
	return 0;
}
