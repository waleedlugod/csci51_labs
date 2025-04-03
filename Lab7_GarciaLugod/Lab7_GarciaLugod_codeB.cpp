#include <pthread.h>
#include <iostream>
#include <math.h>
using namespace std;

long double *sums; // array of sums computed by the pthreads
int N;             // number of threads to spawn
long double X;     // arg for sin()

void *sin_threads(void *id)
{
    int term = *(int *)id + 0;
    long double last = 1;
    long double min = powl(10, -16);
    while (abs(last) >= min)
    {
        // calculate numerator
        int power = (term + 1) * 2 - 1;
        long double numerator = powl(X, power);

        // calculate denominator
        // factorial implementation
        long double denominator = 1;
        for (int i = 1; i <= power; i++)
        {
            denominator *= i;
        }

        // calculate final term
        last = numerator / denominator;

        if (term % 2 == 0)
            sums[*(int *)id] += last;
        else
            sums[*(int *)id] -= last;

        term += N;
    }
}

int main(int argc, char *argv[])
{
    N = atoi(argv[1]);
    X = strtold(argv[2], NULL);

    sums = (long double *)malloc(sizeof(long double) * N);
    pthread_t *sin_ts = (pthread_t *)malloc(sizeof(pthread_t) * N);

    int t_ids[N]; // ids of each pthread. uses array to avoid mutation of each id during loop
    for (int i = 0; i < N; i++)
    {
        t_ids[i] = i;
        pthread_create(&sin_ts[i], NULL, sin_threads, (void *)&t_ids[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(sin_ts[i], NULL);
    }

    // calculate final sum of the series
    long double sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += sums[i];
    }

    printf("computed sum %Le\n", sum);

    return 0;
}
