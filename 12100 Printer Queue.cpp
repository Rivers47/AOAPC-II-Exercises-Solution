//#define TEST
#include <cstdio>
#include <queue>
#ifdef TEST
#include <chrono>
#endif
using namespace std;

int timeUsed()
{
	queue<int> line;
	int qsize, pos, time = 0, target;
	int nmax[10] = { 0 };
	scanf("%d%d", &qsize, &pos);
	if (qsize == 1) { scanf("%d",&target); return 1; }
	for (int i = 0; i < qsize; i++)
	{
		int m;
		scanf("%d", &m);
		nmax[m]++;
		if (i == pos)
			target = m;
		line.push(m);
	}

	for (int k = 9; k > target; k--)
		for (int i = 0; i < nmax[k];)
		{
			int x = line.front();
			if (x < k)
			{
				line.pop();
				line.push(x);
				if (pos == 0)
					pos = line.size() - 1;
				else
					pos--;
			}
			else
			{
				line.pop();
				i++;
				time++;
				pos--;
			}
		}

	while(1)
	{
		int x = line.front();
		if (x < target)
		{
			line.pop();
			line.push(x);
			pos--;
		}
		else
		{
			line.pop();
			time++;
			
			if (pos == 0)
				return time;
			pos--;
		}
	}

}


int main()//Printer Queue
{
#ifdef TEST
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
#endif

	//1 2 1 *1* 1 9 8 9 2 1 1
	int nCase;
	scanf("%d",&nCase);
	while (nCase--)
		printf("%d\n", timeUsed());

#ifdef TEST
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	printf("%f", time_span.count());
#endif
	return 0;
}