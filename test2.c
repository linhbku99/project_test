#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define MAX_ITEMS 1
#define THREADS 1
// 1 producer and 1 consumer
#define LOOPS 2 * MAX_ITEMS
// v a r i a b l e
// I n i t i a t e shared b u f f e r
int buffer[MAX_ITEMS];
int fill = 0;
int use = 0;
sem_t empty;
sem_t full;
void put(int value);
// put data into b u f f e r
int get();
// get data from b u f f e r
void *producer(void *arg)
{
    int i;
    int tid = (int)arg;
    for (i = 0; i < LOOPS; i++)
    {
        sem_wait(&empty);
        put(i);
        printf("Producer %d put data data % d\n ", tid, i);
        sleep(1);
        sem_post(&full);
    }
    pthread_exit(NULL);
}
// l i n e P1
// l i n e P2

// l i n e P3
void *consumer(void *arg)
{
    int i, tmp = 0;
    int tid = (int)arg;
    while (tmp != -1)
    {
        sem_wait(&full);
        // l i n e C1
        tmp = get();
        // l i n e C2
        printf("Consumer %d get data %d\n", tid, tmp);
        sleep(1);
        sem_post(&empty);
        // l i n e C3
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv)
{
    int i, j;
    int tid[THREADS];
    pthread_t producers[THREADS];
    pthread_t consumers[THREADS];
    sem_init(&empty, 0, MAX_ITEMS);
    sem_init(&full, 0, 0);
    for (i = 0; i < THREADS; i++)
    {
        tid[i] = i;
        // Create producer thread
        pthread_create(&producers[i], NULL, producer, (void *)tid[i]);
        // Create consumer thread
        pthread_create(&consumers[i], NULL, consumer, (void *)tid[i]);
    }
    for (i = 0; i < THREADS; i++)
    {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
void put(int value)
{
    buffer[fill] = value;          // l i n e f1
    fill = (fill + 1) % MAX_ITEMS; // l i n e f2
}
int get()
{
    int tmp = buffer[use];       // l i n e g1
    use = (use + 1) % MAX_ITEMS; // l i n e g2
    return tmp;
}