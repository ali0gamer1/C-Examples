#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>


#define COUNT_TO 100000
#define MAX_THREADS 4

static pthread_mutex_t mutex;

long long  counter = 0;
void count()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        if (counter >= COUNT_TO)
        {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }


        counter++;

        printf("%d\n",counter);

        pthread_mutex_unlock(&mutex);

        for (volatile long long i = 0;i<counter;i++){
                sqrt(i);


        }



}
}



int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t *thread_group = malloc(sizeof(pthread_t) * MAX_THREADS);


    int i;
    for (i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&thread_group[i], NULL, &count, NULL);
    }

    // wait for all threads to finish
    for (i = 0; i < MAX_THREADS; ++i) {
        pthread_join(thread_group[i], NULL);
    }



    return 0;
}
