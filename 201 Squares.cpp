#include <cstring>
#include <cstdio>

int board[10][10];
int n, m;
int square[10];

int isSquare(int x, int y, int size)
{
	
	for(int i = 0; i < size; i++)
	{
		//前两个expression判断横向，后两个判断竖向
		if(!(board[x][y+i] & 1 && board[x+size][y+i] & 1 && board[x+i][y] & 2 && board[x+i][y+size] & 2))
			return 0;
	}


	return 1;
}


/*
从最大的方块开始，坐标为左上方的角，依次经过grid的每个可能的位置之后，
将size-1然后递归
starts with the largest square, the coordinates is the top left corner, 
iterate over the grid, go to the smaller size
*/
void count(int size = n-1)
{
	int num = 0;
	//i is the total number of loops, so there is no deed to determine whther x has overflown
	int i = (n-size)*(n-size);//i为当前size下可能的位置个数，使用这个变量的好处是在后面的循环里无需判断x是否越界
	for(int k = 0, x = 1, y = 1; k < i; k++)
	{
		num += isSquare(x, y, size);
		if(y + size >= n)//whther to start with a new line,是否换行
		{
			x++;
			y = 1;
			continue;
		}
		y++;
	}
	square[size] = num;
	size--;
	if(size > 0)
		count(size);
	
	return;
}

//0代表没有线，1代表横线，2代表竖线，3代表横竖线
//0represents no line, 1 represents a horizontal line, 2 is a vertical line, 3 means both
void mark(int l, int i, int j)
{
	if(l=='H')
		board[i][j]++;
	else
		board[j][i]+=2;
	return;
}

int main()
{
	int problem = 1;
	while (scanf("%d%d",&n, &m) == 2)
	{
		if(problem > 1)
			printf("\n**********************************\n\n");

		//initilization
		memset(board,0,sizeof board);

		for(int k = 0; k < m; k++)
		{
			char l;
			int i, j;
			scanf("\n%c",&l);
			scanf("%d%d",&i,&j);
			mark(l, i, j);
		}
		count();

		int number = 0;
		for(int i = 1; i < n; i++)
			number += square[i];
		printf("Problem #%d\n\n", problem);
		problem++;
		if(number == 0)
			printf("No completed squares can be found.\n");
		else
			for(int i = 1; i < n; i++)
			{
				if(square[i])
					printf("%d square (s) of size %d\n", square[i], i);
			}
	}
	return 0;
}

