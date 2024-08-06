#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"


int sieve(int n)
{
	if (n<=0) return 1;
	if (n==1) return 2;
	int pplace = 3;
	int pcount = 1; // 2nd prime : 3
	int *numlist;
	int numlen = (n * (log(n)+1))*3;

	numlist = calloc (numlen, sizeof(int));
	
	for (;pplace < numlen;pplace=pplace+2)
	{
		numlist[pplace]=pplace;
	}

	for (int j = 3; ((j*j)<=numlen); j=j+2)
	{
		if (numlist[j] != 0)
		{
			pcount++;
			pplace=j;
			for (int i = 3; numlist[j]*i<numlen; i=i+2)
			{
				numlist[numlist[j]*i] = 0;
			}
		
		}
	}
	for (int i = pplace; pcount <= n; i=i+2)
	{
		if (numlist[i] != 0)
		{
			pcount++;
			pplace=i;
		}
	}
	free(numlist);

	return pplace;
}

