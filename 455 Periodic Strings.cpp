#include <stdio.h>
#include <string.h>

int periodicStrings(char *a)
{
	int l = strlen(a); //get the length of the test string
	int h = l/2;

	char m[41];	//
	for(int i = 1; i <= h; i++)
	{
		if(l%i!=0)	
			continue;

		strncpy(m,a,i);
		m[i]=0;

		bool match = true;
		for(int s = 0; match && s < l; s++) //test if m is period of a
		{
			if(m[s%(i)] != a[s])
				match = false;
		}
		if(match)
			return i;
	}

	return l;
}



int main()
{
	
	int a;scanf("%d", &a);

	for(int i = 1; i<a; i++)
	{
		char s[85];
		scanf("\n%s",&s);
		printf("%d\n\n",periodicStrings(s));
	}
	char s[85];
	scanf("\n%s",&s);
	printf("%d\n",periodicStrings(s));
	
	
	
	return 0;
}

