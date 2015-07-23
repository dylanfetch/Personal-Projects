#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef _OPENMP
#include <omp.h>
#endif

static double timer()
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return ((double) (tp.tv_sec) + 1e-9 * tp.tv_nsec);
    
}

void serialSieve(int n)
{
	int *A;
	int i;
	int j;
	int count;
	
	printf("\nPrimes up to %d\n", n);
	
	A = malloc( n * sizeof(int) );
	
	A[1] = 0;
	for( i = 2; i < n; i++ )
	{
		A[i] = 1;
	}
	
	for( i = 2; i < sqrt( n ); i++ )
	{
		if( A[i] == 1)
		{
			for( j = i * i; j < n; j = j + i )
			{
				A[j] = 0;
			}
		}
	}
	
	count = 0;
	for( i = 1; i < n; i++ )
	{
		if( A[i] == 1 )
		{
			count++;
			/*if( count % 8 == 0 )
			{
				printf("%10d\n",i);
			}
			else
			{
				printf("%10d",i);
			}*/
		}
	}
	
	printf("Number of primes:%10d\n", count);
	
	free( A );
	
}

void threadedSieve(int n, int threadNum)
{
	int *A;
	int i;
	int j;
	int count;
	omp_set_num_threads(threadNum);
	
	printf("\nPrimes up to %d\n", n);
	
	A = malloc( n * sizeof(int) );
	
	A[1] = 0;
	
	
	#pragma omp parallel for
	for( i = 2; i < n; i++ )
	{
		A[i] = 1;
	}
		
	for( i = 2; i < sqrt( n ); i++ )
	{
		if( A[i] == 1)
		{
			
			for( j = i * i; j < n; j = j + i )
			{
				A[j] = 0;
			}
		}
	}
	
	
	count = 0;
	for( i = 1; i < n; i++ )
	{
		if( A[i] == 1 )
		{
			count++;
			/*if( count % 8 == 0 )
			{
				printf("%10d\n",i);
			}
			else
			{
				printf("%10d",i);
			}*/
		}
	}
	
	printf("Number of primes:%10d\n", count);
	
	free( A );
	
}

void callSerialSieve( int size )
{
	double time = 0.0;
	
	time = timer();
	serialSieve(size);
	time = timer() - time;
	printf("Serial time: %9.3lf ms\n", time*1e3);
}

void callParallelSieve( int size, int threadNum )
{
	double time = 0.0;
	
	time = timer();
	threadedSieve(size, threadNum);
	time = timer() - time;
	printf("%d Threaded time: %9.3lf ms\n", threadNum, time*1e3);
}

int main()
{
	callSerialSieve( 1000000 );
	callParallelSieve( 1000000, 2 );
	callParallelSieve( 1000000, 4 );
	callParallelSieve( 1000000, 8 );
	printf("\n");
	
	callSerialSieve( 10000000 );
	callParallelSieve( 10000000, 2 );
	callParallelSieve( 10000000, 4 );
	callParallelSieve( 10000000, 8 );
	printf("\n");
	
	callSerialSieve( 100000000 );
	callParallelSieve( 100000000, 2 );
	callParallelSieve( 100000000, 4 );
	callParallelSieve( 100000000, 8 );
	printf("\n");
	
	callSerialSieve( 1000000000 );
	callParallelSieve( 1000000000, 2 );
	callParallelSieve( 1000000000, 4 );
	callParallelSieve( 1000000000, 8 );
	printf("\n");
}