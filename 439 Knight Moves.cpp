#include <cstdio>
#include <cstring>
#include <queue>
#define grid std::pair<char, char>
#define add(x,y) if(board[x][y] == 0){ board[x][y] = step; q.push(grid(x, y));}	
char board[10][10];


//bfs
void go(char endy, char endx, char starty, char startx)
{
	std::queue< grid > q;
	
	char x,y;
	char step = 0;
	q.push(grid(startx,starty));

	while(board[endx][endy] == 0 && !q.empty())
	{
		grid c = q.front();
		q.pop();
	
		step = board[c.first][c.second]+1;
		x=c.first-2; 
		if(x >= 0)
		{
			y=c.second+1;
			if(y < 8)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}		
			}
			y=c.second-1;
			if(y >= 0)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}	
			}
		}
		x=c.first+2; 
		if(x < 8)
		{
			y=c.second+1;
			if(y < 8)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}		
			}
			y=c.second-1;
			if(y >= 0)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}	
			}
		}
		y=c.second-2;
		if(y >= 0)
		{
			x=c.first+1;
			if(x < 8)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}		
			}
			x=c.first-1;
			if(x >= 0)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}	
			}
		}
		y=c.second+2;
		if(y < 8)
		{
			x=c.first+1;
			if(x < 8)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}		
			}
			x=c.first-1;
			if(x >= 0)
			{
				if(board[x][y] == 0)
				{
					board[x][y] = step;
					q.push(grid(x, y));
				}	
			}
		}

	}
	
}



int main()
{
	char a,b,c,d;
	while(scanf("%c%c", &a, &b) == 2)
	{
		for(int i = 0; i < 10; i++)
		{
			memset(board[i],0,10);
		}

		scanf("%*c", &a);
		scanf("%c%c", &c, &d);
		if(a==c && b==d)
		{
			printf("To get from %c%c to %c%c takes 0 knight moves.\n",a,b,c,d);
			scanf("%*c", &a);
			continue;
		}
		go(c-97,d-49, a-97, b-49);
		printf("To get from %c%c to %c%c takes %d knight moves.\n",a,b,c,d,board[d-49][c-97]);
		scanf("%*c", &a);
	}
	
	return 0;
}
