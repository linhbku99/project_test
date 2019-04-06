#include <stdio.h>
#include <pthread.h>
static volatile int counter = 0;
void *mythread(void *arg)
{
    printf("%d : begin\n", (int *)arg);
    int i;
    for (i = 0; i < 1e7; i++)
    {
        counter = counter + 1;
    }
    printf("%d : done\n", (int *)arg);
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t p1, p2;
    pthread_t p[3];
    printf("main : begin ( counter = %d)\n", counter);
    pthread_create(&p1, NULL, mythread, 4);
    pthread_create(&p2, NULL, mythread, 5);
    // j o i n waits f o r the threads to f i n i s h
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main : done with both ( counter = %d)\n", counter);
    for(int i = 0; i < 3; i++)
    {
        pthread_create(&p[i], NULL, mythread, i);
        pthread_join(p[i], NULL);
    }
    printf("main : done with both ( counter = %d)\n", counter);
    return 0;
}
