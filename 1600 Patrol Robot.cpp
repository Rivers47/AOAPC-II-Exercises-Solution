#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
//#define TEST
using namespace std;

int m,n;
int K;




char board[30][30];
int steps[30][30];
int obstacle[30][30];	//used to record how many consecutive cells with obstacles have been passed
#ifdef TEST
void printBoard()
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%3d", board[i][j]);
		}
		printf("\n");
	}
}
void printSteps()
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%3d", steps[i][j]);
		}
		printf("\n");
	}
}
#endif
#define cell pair<int,int>
void bfs()
{
	cell c(0,0);
	queue<cell> q;
	q.push(c);
	int step,turbo;
	steps[0][0]=0;
	int x,y;
	int direction[] = {1,-1};
	while(!q.empty())
	{
		c = q.front();
		q.pop();
		step = steps[c.first][c.second] + 1;

		x = c.first;
		for(int i = 0; i < 2; i++)
		{
			y=c.second+direction[i];
			if(y < 0 || y >= n)
					continue;	

			if(steps[x][y] == -1)
			{
				if(board[x][y] == 1)
				{
					if(board[c.first][c.second] == 1)
						obstacle[x][y]= obstacle[c.first][c.second]+1;
					else
						obstacle[x][y] = 1;
				}
				if(obstacle[x][y] > K)
				{
					continue;
				}		
				steps[x][y] = step;
				q.push(cell(x,y));
			}
			else
			{
				if(board[x][y] == 1)
				{
					if(board[c.first][c.second] == 1)
						turbo = obstacle[c.first][c.second]+1;
					else
						obstacle[x][y] = turbo = 1;
					if(turbo < obstacle[x][y])
					{
						obstacle[x][y] = turbo;
						q.push(cell(x,y));
					}
				}
			}
		}
		y=c.second;
		for(int i = 0; i < 2; i++)
		{
			x=c.first+direction[i];
			if(x < 0 || x >= m)
					continue;

			if(steps[x][y] == -1)
			{
				if(board[x][y] == 1)
				{
					if(board[c.first][c.second] == 1)
						obstacle[x][y]= obstacle[c.first][c.second]+1;
					else
						obstacle[x][y] = 1;
				}
				if(obstacle[x][y] > K)
				{
					continue;
				}		
				steps[x][y] = step;
				q.push(cell(x,y));
			}
			else
			{
				if(board[x][y] == 1)
				{
					if(board[c.first][c.second] == 1)
						turbo = obstacle[c.first][c.second]+1;
					else
						obstacle[x][y] = turbo = 1;
					if(turbo < obstacle[x][y])
					{
						obstacle[x][y] = turbo;
						q.push(cell(x,y));
					}
				}
			}
		}
		
	}

	


}



//from[0][0]to[m-1][n-1]
int main()
{
	int N;
	cin >> N;
	int kase = 1;
	while(N--)
	{
		cin >> m >> n >> K;
		for(int i = 0; i < m; i++)
		{
			memset(steps[i],-1,n*sizeof(int));
			memset(obstacle[i],0,n*sizeof(int));
		}
		
		
		for(int i = 0, c; i < m; i++)
		{
			for(int j = 0; j < n; j++)
			{
				cin >> c;
				board[i][j] = c;
			}
		}
		
		bfs();
		cout << steps[m-1][n-1] << '\n';
		#ifdef TEST 
		if(kase++ == 334) {printBoard(); cout << "\n\n"; printSteps();};
		#endif 
		//for some reason this board got a different answer from the debug system UDebug in UVa.
		/*
		0  1  1  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  1  1  1  0  1  1  1
		1  1  1  1  1  0  0  1
		1  1  1  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  1  0  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  0  1  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  1  1  1  1  1  1  1
		1  1  1  0  1  1  1  1
		1  1  1  1  1  1  1  0
		1  1  1  1  1  1  1  1
		1  1  0  1  1  1  1  0
		*/
	}
	







	return 0;
}
