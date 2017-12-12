#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
//#define TEST

#ifdef TEST
void printVector(std::vector<int>& a)
{
	for (int& n : a)
		printf("%d ", n);
	printf("\n");
}
#endif

int tupleType(std::vector<int>& tuple)
{
	std::set<int> n;
	for (int i : tuple)
	{
		n.insert(i);
		if (n.size() > 2)
			return 0;
	}
	if(n.size()==2)
		return 2;
	//zero loop
	return 1;
}


int isSequence(std::vector<int>& tuple)
{
	int n = tupleType(tuple);
	if (n)
		return n;

	n = tuple[0];
	int i;
	for (i = 0; i < tuple.size()-1; i++)
	{	
		tuple[i] = abs(tuple[i] - tuple[i + 1]);
	}
	tuple[i] = abs(tuple[i] - n);
#ifdef TEST
	printVector(tuple);
#endif
	return isSequence(tuple);
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		int k;
		scanf("%d", &k);

		double pow2 = log2(k);
		if (pow2 == floor(pow2))
		{
			printf("ZERO\n");
			std::cin.ignore();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//this may not be supported by older compilers
			continue;
		}

		std::vector<int> tuple(k);
		
		for(int i = 0; i < k; i++)
		{
			int in;
			scanf("%d", &in);
			tuple[i] = in;
		}
		int is = isSequence(tuple);
		if (is == 2)
			printf("LOOP\n");
		else
			printf("ZERO\n");
	}
	return 0;
}
