#include <immintrin.h>
#include <stdint.h>
#include <Windows.h>
#include <stdio.h>

int test_clflush()
{
	int array[100];

	/* this is optional */
	/* will bring array in the cache */
	for (int i = 0; i < 100; i++)
		array[i] = i;

	printf("address = %p \n", &array[0]); /* guaranteed to be aligned within a single cache line */

	_mm_mfence();                      /* prevent clflush from being reordered by the CPU or the compiler in this direction */

	/* flush the line containing the element */
	_mm_clflush(&array[0]);

	//unsigned int aux;
	uint64_t time1, time2, msl, hsl, osl; /* initial values don't matter */

	/* rdtscp is not suitbale for measuing very small sections of code because
	 the write to its parameter occurs after sampling the TSC and it impacts
	 compiler optimizations and code gen, thereby perturbing the measurement */

	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
	time1 = __rdtsc();                 /* set timer */
	_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
	int temp = array[0];             /* array[0] is a cache miss */
	/* measring the write miss latency to array is not meaningful because it's an implementation detail and the next write may also miss */
	/* no need for mfence because there are no stores in between */
	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp and the load*/
	time2 = __rdtsc();
	_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions */
	msl = time2 - time1;

	printf("array[ 0 ] = %i \n", temp);             /* prevent the compiler from optimizing the load */
	printf("miss section latency = %lu \n", msl);   /* the latency of everything in between the two rdtscp */

	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
	time1 = __rdtsc();                 /* set timer */
	_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp and the load */
	temp = array[0];                 /* array[0] is a cache miss */
	/* measring the write miss latency to array is not meaningful because it's an implementation detail and the next write may also miss */
	/* no need for mfence because there are no stores in between */
	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp and the load */
	time2 = __rdtsc();
	_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions */
	hsl = time2 - time1;

	printf("array[ 0 ] = %i \n", temp);            /* prevent the compiler from optimizing the load */
	printf("hit section latency = %lu \n", hsl);   /* the latency of everything in between the two rdtscp */


	_mm_mfence();                      /* this properly orders both clflush and rdtscp*/
	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
	time1 = __rdtsc();                 /* set timer */
	_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions + compiler barrier for rdtscp */
	/* no need for mfence because there are no stores in between */
	_mm_lfence();                      /* mfence and lfence must be in this order + compiler barrier for rdtscp */
	time2 = __rdtsc();
	_mm_lfence();                      /* serialize __rdtscp with respect to trailing instructions */
	osl = time2 - time1;

	printf("overhead latency = %lu \n", osl); /* the latency of everything in between the two rdtscp */


	printf("Measured L1 hit latency = %lu TSC cycles\n", hsl - osl); /* hsl is always larger than osl */
	printf("Measured main memory latency = %lu TSC cycles\n", msl - osl); /* msl is always larger than osl and hsl */

	return 0;
}

//int main()
//{
//	test_clflush();
//}