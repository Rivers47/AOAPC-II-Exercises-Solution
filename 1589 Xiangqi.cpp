//This one didn't get AC, but I can't identify the bug.
#include <stdio.h>
#include <string.h>
#include <math.h>

struct piece 
{
	char type; 
	int x; 
	int y;
};

char board[12][11];
piece BG,RG;
piece R[7];
int N;

int checkG(int x, int y, piece p);
int checkR(int x, int y, piece p);
int checkH(int x, int y, piece p);
int checkC(int x, int y, piece p);
int check(int x, int y);


int check(int x, int y)
{
	
	for(int i = 0; i < N; i++)
	{
		int checkmate = 0;
		switch(R[i].type)
		{
			case 'G':
				checkmate = checkG(x,y,R[i]);
				break;
			case 'R':
				checkmate = checkR(x,y,R[i]);
				break;
			case 'H':
				checkmate = checkH(x,y,R[i]);
				break;
			case 'C':
				checkmate = checkC(x,y,R[i]);
				break;
			default:
				break;
		}
		if(checkmate)
			return 1;
	}
	return 0;

}

//不考虑黑将原位
int checkG(int x, int y, piece p)
{
	if(p.y==y)
	{
		for(int i = p.x-1; i > x; i--)
			if(board[i][y] > 1)
				return 0;
		return 1;
	}	
	return 0;
}

int checkR(int x, int y, piece p)
{
	if(p.x==x && p.y==y)
		return 0;
	
	//horizontal
	if(p.x == x)
	{
		if(p.y - y > 0)
		{
			for(int s = 1; s < p.y - y; s++)
				if(board[x][p.y-s] > 1)
					return 0;
			return 1;
		}
		else
		{
			for(int s = 1; s < p.y - y; s++)
				if(board[x][p.y+s] > 1)
					return 0;
			return 1;
		}
	}
	else if(p.y == y)	//vertical
	{
		if(p.x - x > 0)
		{
			for(int s = 1; s < p.x - x; s++)
				if(board[p.x-s][y] > 1)
					return 0; 
			return 1;
		}
		else
		{
			for(int s = 1; s< p.x -x; s++)
				if(board[p.x+s][y] > 1)
					return 0;
			return 1;
		}
	}
	return 0;
}

int checkH(int x, int y, piece p)
{
	if(p.x == x && p.y == y)
		return 0;

	int dx = p.x - x;
	int dy = p.y - y;

	//vertical
	if(abs(dx)==2 && abs(dy)==1)
		return board[p.x-dx/2][p.y] <= 1;

	//horizontal
	else if(abs(dx) == 1 && abs(dy) == 2)
		return board[p.x][p.y-dy/2] <= 1;
			
	return 0;
}

int checkC(int x, int y, piece p)
{
	if(p.x==x && p.y==y)
		return 0;

	//horizontal
	if(p.x == x)
	{
		if(p.y-y > 0)
		{
			int have = 0;
			for(int s = 1; s<p.y-y; s++)
				if(board[x][p.y-s] > 1)
					have++;
			if(board[BG.x][BG.y+1] > 1)
				have--;
			return have == 1;
		}
		else
		{
			int have = 0;
			for(int s = 1; s < p.y-y; s++)
				if(board[x][p.y+s] > 1)
					have++;
			if(board[BG.x][BG.y-1] > 1)
				have--;
			return have == 1;
		}
	}
	else if(p.y == y)
	{
		if(p.x - x > 0)
		{
			int have = 0;
			for(int s = 1; s < p.x - x; s++)
				if(board[p.x-s][y] > 1)
					have++;
			if(board[BG.x+1][BG.y] > 1)
				have--;
			return have == 1;
		}
		else
		{
			int have = 0;
			for(int s= 1; s < p.x -x;s++)
				if(board[p.x+s][y] > 1)
					have++;
			if(board[BG.x-1][BG.y] > 1)
				have--;
			return have == 1;
		}

	}
	return 0;
}

int checkBG(piece p)
{
	//检查是否黑将能直接赢
	if(p.y==BG.y)
	{
		for(int k = p.x-1; k > BG.x; k--)
			if(board[k][p.y] > 1)
				return 0;
		return 1;
	}
	return 0;
}

int main()
{
	while(scanf("%d%d%d",&N,&BG.x,&BG.y) == 3 && N)
	{
		for(int i = 0; i<11; i++)
			memset(board[i],0,10);

		//board上0代表空，1代表不能走
		board[BG.x][BG.y] = 'B';

		for(int n = 0; n < N; n++)
		{
			scanf("\n%c%d%d",&R[n].type,&R[n].x,&R[n].y);
			if(R[n].type == 'G')
				RG = R[n];
			board[R[n].x][R[n].y] = R[n].type;
		}
		if(checkBG(RG))
		{
			printf("NO\n");//输出no
			continue;
		}

		int checkmate=1;
		if(BG.y<6)
			if(!check(BG.x,BG.y+1))
				checkmate=0;
		if(BG.y>4)
			if(!check(BG.x,BG.y-1))
				checkmate=0;
		if(BG.x<3)
			if(!check(BG.x+1,BG.y))
				checkmate=0;
		if(BG.x>1)
			if(!check(BG.x-1,BG.y))
				checkmate=0;
		if(checkmate)
			printf("YES\n");
		else
			printf("NO\n");
		
	}
	
	return 0;	
}

