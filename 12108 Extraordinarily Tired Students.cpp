#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


struct student
{
	int a, b, c;
	int next;
	bool awaken;
	
	
	student(int a=0, int b=0, int c=0) :a(a), b(b), c(c)
	{
		awaken = (c <= a);
		if (awaken)
			next = a - c;
		else
			next = a + b - c;
	}

};

void printState(vector <student>& x)
{
	for (auto& i : x)
	{
		cout << i.awaken << " ";
	}
	cout << "\n";
	
}
bool equal(vector<student>& x, vector<student>& y)
{
	for (int i = 0; i < x.size(); i++)
	{
		if (!(x[i].c == y[i].c && x[i].awaken == y[i].awaken))
			return false;
	}
	return true;

}

int main()
{
	cin.tie(0); cin.sync_with_stdio(0);

	int n, kase = 1;
	
	
	while (cin >> n && n)
	{
		int nAwaken = 0;
		vector<student> s;

		for (int i = 0; i < n; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			s.push_back(student(a, b, c));
			if (s[i].awaken)
				nAwaken++;
		}
		if(nAwaken == n)
		{
			cout << "Case " << kase++ << ": " << "1\n";
			continue;
		}
		vector<student> scopy(s);
		for (int count = 1;; count++)
		{
			//cout << flush;
			//printState(s);
			int nawaken = 0;
			for (auto& i : s)
			{
				if (i.next == 0)
				{
					if (i.awaken)
					{
						if ((double)nAwaken >= (double)n / 2)//cann't sleep
						{
							i.next = i.a - 1;
							i.c = 1;
						}
						else
						{
							i.next = i.b - 1;
							i.awaken = 0;
							i.c = i.a + 1;
							nawaken--;
						}
					}
					else
					{
						i.c = 1;
						i.next = i.a - 1;
						i.awaken = 1;
						nawaken++;
					}
				}
				else
				{
					i.next--;
					i.c++;
				}
			}
			nAwaken += nawaken;
			if (equal(s,scopy))
			{
				cout << "Case " << kase << ": " << "-1\n";
				break;
			}
			int allAwaken = 1;
			for (auto& i : s)
			{
				if (!i.awaken)
				{
					allAwaken = 0;
					break;
				}
			}
			if (allAwaken)
			{
				cout << "Case " << kase << ": " << count + 1 << "\n";
				break;
			}
		}
		kase++;
	}


	return 0;
}
