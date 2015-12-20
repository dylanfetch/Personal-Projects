//Author: Dylan Fetch

#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<stdio.h>
#include<math.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef _OPENMP
#include <omp.h>
#endif

// Credit to Dr.Kamesh Madduri for the timer() function
static double timer()
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return ((double) (tp.tv_sec) + 1e-9 * tp.tv_nsec);
    
}

// Baseline function using serial algorithm and array of 32 bit integers
void serialSieve(int n)
{
	int *A;
	int i;
	int j;
	int count;
	
	
	A = malloc( n * sizeof(int) );
	
	// In A[], the index represents the integer, and the value is boolean,
	//		0 representing not prime, and 1 representing prime, all values
	//		are initialized to 1 except for 0 and 1 which are not prime
	A[0] = 0;
	A[1] = 0;
	for( i = 2; i < n; i++ )
	{
		A[i] = 1;
	}
	
	// Outer loop increments i from 2 to the square root of n because when i
	//		reaches the square root of n, the iterations start checking indexes
	//		that have already been checked by previous iterations of the loop
	for( i = 2; i < sqrt( n ); i++ )
	{
		// If a number is prime, mark its square as not prime. Increment by i 
		//		and mark each of the indexes as not prime. Since each of these
		//		indexes is divisible by i, they are all not prime.
		if( A[i] == 1)
		{
			for( j = i * i; j < n; j = j + i )
			{
				A[j] = 0;
			}
		}
	}
	
	// Increment through A[] counting all of the primes
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
	
	printf("Primes:\t%d/%d\n", count, n);
	
	free( A );
	
}

// Serial algorithm, but uses array of 8 bit integers allowing more values
//		to fit into the cache, making the function run faster
void serialSieveBetterMem(int n)
{
	uint8_t *A;
	int i;
	int j;
	int count;
	
	
	A = malloc( n * sizeof(uint8_t) );
	
	// In A[], the index represents the integer, and the value is boolean,
	//		0 representing not prime, and 1 representing prime, all values
	//		are initialized to 1 except for 0 and 1 which are not prime
	A[0] = 0;
	A[1] = 0;
	for( i = 2; i < n; i++ )
	{
		A[i] = 1;
	}
	
	// Outer loop increments i from 2 to the square root of n because when i
	//		reaches the square root of n, the iterations start checking indexes
	//		that have already been checked by previous iterations of the loop
	for( i = 2; i < sqrt( n ); i++ )
	{
		// If a number is prime, mark its square as not prime. Increment by i 
		//		and mark each of the indexes as not prime. Since each of these
		//		indexes is divisible by i, they are all not prime.
		if( A[i] == 1)
		{
			for( j = i * i; j < n; j = j + i )
			{
				A[j] = 0;
			}
		}
	}
	
	// Increment through A[] counting all of the primes
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
	
	printf("Primes:\t%d/%d\n", count, n);
	
	free( A );
	
}

// Multithreaded algorithm with array of 32 bit integers
void threadedInitSieve(int n, int threadNum)
{
	int *A;
	int i;
	int j;
	int count;
	omp_set_num_threads(threadNum);
	
	
	A = malloc( n * sizeof(int) );
	
	// In A[], the index represents the integer, and the value is boolean,
	//		0 representing not prime, and 1 representing prime, all values
	//		are initialized to 1 except for 0 and 1 which are not prime
	A[0] = 0;
	A[1] = 0;
	#pragma omp parallel for
	for( i = 2; i < n; i++ )
	{
		A[i] = 1;
	}
	
	// Outer loop increments i from 2 to the square root of n because when i
	//		reaches the square root of n, the iterations start checking indexes
	//		that have already been checked by previous iterations of the loop	
	for( i = 2; i < sqrt( n ); i++ )
	{
		// If a number is prime, mark its square as not prime. Increment by i 
		//		and mark each of the indexes as not prime. Since each of these
		//		indexes is divisible by i, they are all not prime.
		if( A[i] == 1)
		{
			#pragma omp parallel for
			for( j = i * i; j < n; j = j + i )
			{
				A[j] = 0;
			}
		}
	}
	
	// Increment through A[] counting all of the primes
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
	
	printf("Primes:\t%d/%d\n", count, n);
	
	free( A );
	
}

// Multithreaded algorithm with 8 bit array of integers, allowing more
//		values to fit into the cache, making the function run faster
void threadedPlusSieve(int n, int threadNum)
{
	uint8_t *A;
	int i;
	int j;
	int count;
	omp_set_num_threads(threadNum);
	
	
	A = malloc( n * sizeof(uint8_t) );
	
	// In A[], the index represents the integer, and the value is boolean,
	//		0 representing not prime, and 1 representing prime, all values
	//		are initialized to 1 except for 0 and 1 which are not prime
	A[0] = 0;
	A[1] = 0;
	#pragma omp parallel for schedule(static)
	for( i = 2; i < n; i++ )
	{
		A[i] = 1;
	}
	
	// Outer loop increments i from 2 to the square root of n because when i
	//		reaches the square root of n, the iterations start checking indexes
	//		that have already been checked by previous iterations of the loop
	for( i = 2; i < sqrt( n ); i++ )
	{
		// If a number is prime, mark its square as not prime. Increment by i 
		//		and mark each of the indexes as not prime. Since each of these
		//		indexes is divisible by i, they are all not prime.
		if( A[i] == 1)
		{
			#pragma omp parallel for schedule(static)
			for( j = i * i; j < n; j = j + i )
			{
				A[j] = 0;
			}
		}
	}
	
	// Increment through A[] counting all of the primes
	count = 0;
	#pragma omp parallel for reduction(+:count) schedule(static)
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
	
	printf("Primes:\t%d/%d\n", count, n);
	
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

void callSerialSieveBetterMem( int size )
{
	double time = 0.0;
	
	time = timer();
	serialSieveBetterMem(size);
	time = timer() - time;
	printf("Serial time Better Mem: %9.3lf ms\n", time*1e3);
}

void callParallelInitSieve( int size, int threadNum )
{
	double time = 0.0;
	
	time = timer();
	threadedInitSieve(size, threadNum);
	time = timer() - time;
	printf("%3d Threaded time: %9.3lf ms\n", threadNum, time*1e3);
}

void callParallelPlusSieve( int size, int threadNum )
{
	double time = 0.0;
	
	time = timer();
	threadedPlusSieve(size, threadNum);
	time = timer() - time;
	printf("%3d Threaded time: %9.3lf ms\n", threadNum, time*1e3);
}

void callSieves( int size )
{
	callSerialSieve( size );
	callSerialSieveBetterMem( size );
	printf("Init:\n");
	callParallelInitSieve( size, 2 );
	callParallelInitSieve( size, 4 );
	callParallelInitSieve( size, 8 );
	printf("Plus:\n");
	callParallelPlusSieve( size, 2 );
	callParallelPlusSieve( size, 4 );
	callParallelPlusSieve( size, 8 );
	printf("\n");
}

int main()
{
	callSieves(1000000);
	callSieves(10000000);
	callSieves(100000000);
	callSieves(1000000000);
	
}