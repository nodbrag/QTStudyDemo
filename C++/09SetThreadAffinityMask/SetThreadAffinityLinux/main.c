#define _GUN_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>

void *testfunc(void *arg)
{
	cpu_set_t mask;
    CPU_ZERO(&mask);
    for (int i = 0; i < 4; i++) 
	{ /*将Core0、1、2、3添加到集合中*/
        CPU_SET(i, &mask);
    }

    /* 设置cpu 亲和性(affinity)*/
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) 
	{
        fprintf(stderr, "set thread affinity failed\n");
    }

	for(;;)
	{
		
	}
	
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, (void *)testfunc, NULL) != 0) 
	{
        fprintf(stderr, "thread create failed\n");
        return -1;
    }

    pthread_join(tid, NULL);
    return 0;
}