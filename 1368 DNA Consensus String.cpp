#include <stdio.h>
#include <string.h>
#include <iostream>

int mp(int c[])
{
	int max = -1, maxp = -1;

	for(int i=0; i<4; i++)
	{
		if(maxp < c[i])
		{
			maxp = c[i];
			max = i;
		}
	}
	return max;
}

const char ACGT[5] = "ACGT";

void DNA()
{
	int m,n;
	scanf("%d%d",&m,&n);
	
	char **s = new char*[m];
	for(int i = 0; i < m; i++)
	{
		s[i] = new char[n];
		std::cin>>s[i];
	}
	
	
	
	char *con = new char[n+1];
	int hamming = 0;
	for(int i=0; i<n; i++)	
	{			
		int c[4];
		memset(c,0,16);
		for(int k=0; k<m; k++)	
		{
			switch(s[k][i])
			{
				case 'A':
					c[0]++;
					break;
				case 'C':
					c[1]++;
					break;
				case 'G':
					c[2]++;
					break;
				case 'T':
					c[3]++;
					break;
				default:
					break;
			}
		}
		int p = mp(c);
		con[i] = ACGT[p];//con[i] = s[p][i]; 
		hamming += m-c[p]; 
	}
	con[n] = 0;
	printf("%s\n%d\n",con,hamming);
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++)
		DNA();
	
	
	return 0;
}


