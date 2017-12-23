#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define area 100

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int main()
{
	int n, m, g = 1;
	while (scanf("%d%d", &n, &m) && n && m)
	{
		int l = n * m;
		int* regionHeight = (int*)calloc(l, sizeof(int));

		int i = 0;
		while(i < l)
			scanf("%d", &regionHeight[i++]);
		
		int volume;
		scanf("%d", &volume);
		qsort(regionHeight, l, sizeof(int), compare);

		i = 0;
		while(i < l - 1)
		{
			int s = 0;
			while(s<l-1)
			{
				if (i != i + 1)
					break;
				i++;
				s++;
			}
			int k = abs(regionHeight[i + 1] - regionHeight[i]) * (i + 1) * area;
			if (volume < k)
				break;
			else
				volume -= k;
			i++;
		}

		double h = volume / ((i + 1.)*area) + regionHeight[i];
		if (volume == 0)
			i--;
		double percentage = (i + 1) / (l * 100.);
		printf("Region %d\nWater level is %.2f meters.\n%.2f percent of the region is under water.\n\n", g++, h, percentage);
		free(regionHeight);
	}
	return 0;
}
