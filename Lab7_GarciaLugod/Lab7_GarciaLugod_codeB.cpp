#include <pthread.h>
#include <iostream>
#include <math.h>
#include <unistd.h>
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

    // Check if threads run in parallel
    // sleep(1);
    // printf("%Le\n", sums[*(int *)id]);

    delete (int *)id;
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "N not provided" << endl;
        return 1;
    }
    else if (argc == 2)
    {
        cout << "X not provided" << endl;
        return 1;
    }
    N = atoi(argv[1]);
    if (N <= 0)
    {
        cout << "N must be 1 or greater." << endl;
        return 1;
    }
    X = strtold(argv[2], NULL);

    sums = (long double *)malloc(sizeof(long double) * N);
    pthread_t *sin_ts = (pthread_t *)malloc(sizeof(pthread_t) * N);
    if (!sin_ts)
    {
        cout << "Too many pthreads." << endl;
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        int *index = new int(i);
        pthread_create(&sin_ts[i], NULL, sin_threads, (void *)index);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(sin_ts[i], NULL);
    }
    free(sin_ts);

    // calculate final sum of the series
    long double sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += sums[i];
    }

    printf("Sinl(): %Le\n", sinl(X));
    printf("Sum of pthreads: %Le\n", sum);
    free(sums);

    return 0;
}
