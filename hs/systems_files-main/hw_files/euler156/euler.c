#include "euler.h"
int euler1()
{
	int total=0;
	for(int i = 0; i < 1000; i++)
	{
		if ((i%3==0)||(i%5==0))
		{
			total+=i;
		}
	}
	return total;
}

unsigned int euler5()
{
	unsigned int min = 2520; // answer must be even
	for(int i = 1; i <=20; i++)
	{
		if (min % i != 0)
		{
			min+=2;
			i = 0;			
		}
	}
	return min;
}

unsigned int euler6()
{
	unsigned int sum_squares=0;
	unsigned int square_sums=0;
	for(int i = 1; i<=100;i++)
	{
		sum_squares+=(i*i);
		square_sums+=i;
	}
	square_sums*=square_sums;
	return square_sums-sum_squares;
}
