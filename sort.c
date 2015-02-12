#include <stdlib.h>
#include "sort.h"

//Does not sort in-place.
//Array keys is replaced by the new memory block containing sorted keys.
//unstable.
//N^2 worst, average, best time.
void sortByComparisonCounting(int** keys, int N)
{
	int* count = (int*) calloc(N, sizeof(int));
	int* sortedKeys = (int*) calloc(N, sizeof(int));
	int i,j;

	for(i=0;i<N;i++)
	{
		for(j=i+1;j<N;j++)
		{
			if(*keys[i] > *keys[j])
				count[i] += 1;
			else
				count[j] += 1;
		}
	}

	for(i=0;i<N;i++)
	{
		sortedKeys[count[i]] = i;
	}

	free(count);
	free(*keys);

	*keys = sortedKeys;
}

void sortByDistributionCounting(int** keys, int N, int startN, int endN)
{
	
}