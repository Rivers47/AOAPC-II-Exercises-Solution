#include <cstdio>
#include <map>
#include <set>
using namespace std;


bool findSymmetryLine(const pair <const int, set<int>>& line, double& symmetryLine)
{
	if (line.second.size()>1)
	{
		//find the middle point of the points on the horizontal line
		auto a = line.second.begin();	//auto a = ++line.second.begin();
		auto b = line.second.rbegin();
		for (int i = 0; i < line.second.size() / 2; i++)
		{
			
			int d1 = *(a++);
			int d2 = *a;
			int d3 = *(b++);
			int d4 = *b;
			
			if(d2 - d1 != d3-d4)	//if (*a-- - *a++++ != *b++ - *b)//two pointers alogrithm
				return false;
		}
		symmetryLine = ((double)*a + *b) / 2;
		return true;
	}
	else
	{
		symmetryLine = *line.second.begin();
		return true;
	}
}


map<int, set<int>> graph;
bool Symmetry()
{
	int nDots;
	scanf("%d",&nDots);
	graph.clear();
	while(nDots--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		graph[y].insert(x);
	}

	double symmetryLine;
	if (!findSymmetryLine(*graph.begin(), symmetryLine))
		return false;
	for(auto& line : graph)
	{
		double ns;
		if (!findSymmetryLine(line, ns))
			return false;;
		if (ns != symmetryLine)	//may need to use fdim function
			return false;
	}
	return true;
}


int main()
{
	int nCase;
	scanf("%d",&nCase);
	while(nCase--)
	{
		if (Symmetry())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
