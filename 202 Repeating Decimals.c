//#define TEST
#include <math.h>
#include <stdio.h>
#include <string.h>
#ifdef TEST
#include <time.h>
#endif

int contains(int *remainder, int i, int a)//returns second
{
	for(int n = 0; n<=i; n++)
	{
		if(remainder[n] == a)
			return n;
	}
	return -1;
}

int main()
{
	int a,b;
	while(scanf("%d%d",&a,&b)==2 && a !=-1)
	{
		if(a%b == 0)
		{
			printf("%d/%d = %d.(0)\n   1 = number of digits in repeating cycle\n\n",a,b,a/b);
			continue;
		}
		
		char seg[10000];	//the section after decimal point
		int remainder[10000];	//stores the value of a after each step
		memset(remainder, -1, sizeof(remainder));memset(seg,0,sizeof(seg));
		int a2 = a;
		int integral = 0;
		if(a>b)//a%b
		{
			integral = a/b;
			a = a - b*integral;
		}
		
		
		int begin = -1;
		int i = 0;	
		remainder[0] = a;
		while(1)
		{
			a *= 10;
				
			seg[i] = a/b+'0';
			
			a %= b;
			begin = contains(remainder, i, a);
			remainder[i+1] = a;
			
			if(begin>=0)
			{
				seg[i+1] = '\0';
				i++;
				break;
			}
			
			#ifdef TEST
			printf("i=%d, a=%d, seg[%d]=%c\n", i, a, i, seg[i]);
			#endif
			i++;
		}
		
		/*
		printf("%d/%d = %d.",a2,b,integral);
		if(begin > 0)
			for(int i = 0; i<begin; i++)		
				printf("%c", seg[i]);
				
		char fmt[128];
		sprintf(fmt,"(%%.%ds",50-begin);
		printf(fmt,seg+begin);
		if(strlen(seg+begin)>50)
			printf("...");
		printf(")\n   %d = number of digits in repeating cycle\n\n",strlen(seg+begin));
		*/
		if(begin > 0)
			for(int i = 0; i<begin; i++)		
				printf("%c", seg[i]);
				
		char fmt[128];
		sprintf(fmt,"(%%.%ds",50-begin);
		printf(fmt,seg+begin);
		if(strlen(seg+begin)>50)
			printf("...");
		printf(")\n   %d = number of digits in repeating cycle\n\n",strlen(seg+begin));
		
	}
	#ifdef TEST
	printf("%f\n",((double)clock()/CLOCKS_PER_SEC));
	#endif
	return 0;
	
	
}
