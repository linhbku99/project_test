#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double incircle = 0;
long points_per_thread;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *runner()
{
    unsigned int rand_state = rand();
    long sum = 0;
    for (int i = 0; i < points_per_thread; i++)
    {
        double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        if (x * x + y * y < 1)
        {
            sum++;
        }
    }
    pthread_mutex_lock(&mutex);
    incircle += sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    long totalpoints = atol(argv[1]);
    points_per_thread = totalpoints / 4;
    double sum_incircle[4];
    clock_t start = clock();
    srand((unsigned)time(NULL));
    pthread_t threads[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, runner, NULL);
        //pthread_join(threads[i], NULL);
    }
    for (i = 3; i >= 0; i--)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("for %d Points & 4 thread Pi = %f\n", (int)totalpoints, (4. * (double)incircle) / ((double)totalpoints));
    printf("Time: %f sec\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}