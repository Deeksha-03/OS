#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t chopstick[5];

void * philosopher(void *);
void eat(int);
int main()
{
    int i,philno[5];
    pthread_t tid[5];

    sem_init(&mutex,0,4);

    for(i=0;i<5;i++)
    sem_init(&chopstick[i],0,1);

    for(i=0;i<5;i++)
    {
        philno[i]=i;
        pthread_create(&tid[i],NULL,philosopher,(void *)&philno[i]);
    }
    for(i=0;i<5;i++)
    pthread_join(tid[i],NULL);
}

void * philosopher(void * num)
{
    int phil=*(int *)num;

    sem_wait(&mutex);
    printf("\nPhilosopher %d is hungry",phil);
    sem_wait(&chopstick[phil]);
    sem_wait(&chopstick[(phil+1)%5]);

    eat(phil);
    sleep(2);
    printf("\nPhilosopher %d is thinking",phil);

    sem_post(&chopstick[(phil+1)%5]);
    sem_post(&chopstick[phil]);
    sem_post(&mutex);
}

void eat(int phil)
{
    printf("\nPhilosopher %d is eating",phil);
}
