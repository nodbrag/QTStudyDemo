#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <emmintrin.h>

#define INT_COUNT        (5*1024*1024)

inline int calculate(int input)
{
	int val = (input % 99) * (input / 98);
	val = val ? val : 1;
	double n = sqrt(sqrt((double)(unsigned)input * 1.3));
	double m = sqrt(sqrt((double)(unsigned)val * 0.9));
	return (int)((double)input * (double)val * m / (n ? n : 1.1));
}

int run_withprefetch(const int *array, int size, int step, int prefetch)
{
	int result = 0;
	printf("run with prefetch(%d)...\n", prefetch);
	for (int i = 0; i < step; i++) 
	{
		for (int j = i; j < size; j += step) 
		{
			int k = j + step * prefetch;
			if (k < size) 
			{
				_mm_prefetch((char*)&array[k], _MM_HINT_T0);
				_mm_clflush(&array[k]);
			}
			result += calculate(array[j]);
		}
	}
	return result;
}

int run(const int *array, int size, int step)
{
	int result = 0;
	printf("run...\n");
	for (int i = 0; i < step; i++) 
	{
		for (int j = i; j < size; j += step) 
		{
			result += calculate(array[j]);
		}
	}
	return result;
}

int main()
{
	int select;
	scanf("%d", &select);

	int* array = new int[INT_COUNT];
	for (int i = 0; i < INT_COUNT; i++)
	{
		array[i] = i;
	}
	long t1 = GetTickCount();

	int result;
	if (select == 0)
	{
		result = run(array, INT_COUNT, 1024);
	}
	else
	{
		result = run_withprefetch(array, INT_COUNT, 1024, 1);
	}

	long t2 = GetTickCount();
	std::cout << (t2 - t1) << "ms" << std::endl;
	std::cout << "result:" << result << std::endl;
	delete[] array;
}