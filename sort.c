#include <stdlib.h>
#include <assert.h>
#include "sort.h"

//Does not sort in-place.
//Array keys is replaced by the new memory block containing sorted keys.
//unstable.
//N^2 worst, average, best time.
void sortByComparisonCounting(int** keys, int N)
{
	assert(N>0);
	assert(keys!=NULL);
	assert(*keys!=NULL);

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

//startN<=keys[i]<=endN for all i belonging to [0,N).
//Array keys is replaced by the new memory block containing sorted keys.
//Linear running time.
//Not a comparison sort.
//Stable.
void sortByDistributionCounting(int** keys, int N, int startN, int endN)
{
	assert(N>0);
	assert(endN>=startN);
	assert(keys!=NULL);
	assert(*keys!=NULL);

	int* count = (int*)	calloc(endN-startN+1, sizeof(int));
	int* sortedKeys = (int*) calloc(N, sizeof(int));
	int i;

	for(i=0; i<N; i++)
	{
		count[(*keys[i])-startN] += 1;
	}

	for(i=1; i<endN-startN+1; i++)
	{
		count[i] = count[i] + count[i-1];
	}

	for(i=N; i>=0; i--)
	{
		sortedKeys[count[(*keys[i])-startN]-1] = *keys[i];
		count[(*keys[i])-startN] -= 1;
	}

	free(count);
	free(*keys);

	*keys = sortedKeys;
}