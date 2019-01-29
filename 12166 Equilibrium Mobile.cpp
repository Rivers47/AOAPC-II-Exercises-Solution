#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
using namespace std;

const int MAX = 100000000;

int N;
int change = 0;
stringstream ss;
char line[MAX];
char c;
int nWeight = 0;
map<long long,int> mp;

void read(int depth = 0)
{
	if(ss.peek() == '[')
	{
		ss.ignore();
		read(depth+1);
		ss.ignore();

		read(depth+1);
		ss.ignore();
	}
	else
	{
		nWeight++;
		long long n;
		ss >> n;
		mp[n << depth]++;
	}

}

int main()
{
	cin >> N;
	cin.ignore();
	while (N--)
	{
		cin.getline(line, MAX);
		ss.clear();
		ss.str(line);
		//cout << ss.str()<<endl;
		change = 0;
		nWeight = 0;
		mp.clear();
		read();
		int maxcount = 0;
		for(auto& i : mp)
		{
			if(i.second > maxcount)
			{
				maxcount = i.second;
			}
		
		}
		change = nWeight - maxcount;
		cout << change << '\n';
	}
	return 0;
}
