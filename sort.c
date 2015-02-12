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

static void straightInsertion_rec(int* keys, int start, int end)
{
	if(start==end)
		return;

	int current = keys[start];
	int i = start-1;

	while(i>=0 && keys[i]>current)
	{
		keys[i+1] = keys[i];
		i--;
	}
	keys[i+1] = current;
	straightInsertion_rec(keys, start+1, end);
}

void sortByStraightInsertion_rec(int** keys, int N)
{
	assert(keys!=NULL);
	assert(*keys!=NULL);
	assert(N>0);
	
	straightInsertion_rec(*keys, 1, N);
}

void sortByStraightInsertion_iter(int** keys, int N)
{
	assert(keys!=NULL);
	assert(*keys!=NULL);
	assert(N>0);

	int i, j;
	int current;
	int* k = *keys;

	for(i=1; i<N; i++)
	{
		current = k[i];
		for(j=i-1; j>=0; j--)
		{
			if(k[j] <= current)
				break;

			k[j+1] = k[j];
		}
		k[j+1] = current;
	}
}

static int binaryCompare(int* sortedKeys, int start, int end, int search)
{	
	if((start+1)==end)
	{
		if(sortedKeys[start]<search)
			return start+1;
		else
			return start;
	}

	int mid = (start+end)/2;
	if(sortedKeys[mid] == search)
		return mid;
	else if(sortedKeys[mid] < search)
		return binaryCompare(sortedKeys, mid+1, end);
	else
		return binaryCompare(sortedKeys, start, mid);
}

void sortByBinaryInsertion(int** keys, int N)
{
	assert(keys!=NULL);
	assert(*keys!=NULL);
	assert(N>0);

	int i, j;
	int current;
	int* k = *keys;
	int pos;

	for(i=1; i<N; i++)
	{
		current = k[i];
		pos = binaryCompare(k, 0, i, current);
		for(j=i-1; j>=pos; j--)
		{
			if(k[j] <= current)
				break;

			k[j+1] = k[j];
		}
		k[pos] = current;
	}
}