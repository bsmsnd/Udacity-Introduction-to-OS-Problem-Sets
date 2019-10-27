//
//  main.c
//  OS_problemset1
//
//  Created by 陈东 on 9/5/19.
//  Copyright © 2019 Charlie Chen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_READERS 5
#define N_WRITERS 5

#define OPERATIONS 20

void *reader(void *param);
void *writer(void *param);

int value = 0;
int write_times = 0;
int resource_counter = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_readers = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_writers = PTHREAD_COND_INITIALIZER;


int main(int argc, const char * argv[]) {    
    pthread_t t_readers[N_READERS], t_writers[N_WRITERS];
    
    for (int i = 0;i < N_READERS; i++){
        if (pthread_create(&t_readers[i], NULL, reader, NULL) != 0)
        {
            printf("Reader %d creation failed\n", i);
            exit(1);
        }
    }
    for (int i = 0;i < N_WRITERS; i++)
    {
        if (pthread_create(&t_writers[i], NULL, writer, NULL) != 0)
        {
            printf("Writer %d creation failed\n", i);
            exit(1);
        }
    }
    for (int i = 0;i < N_READERS; i++)
        pthread_join(t_readers[i], NULL);
    for (int i = 0;i < N_WRITERS; i++)
        pthread_join(t_writers[i], NULL);
    
    printf("Parent quiting\n");
    return 0;
};

void *reader(void *param){
    int read_value, read_write_time;
    int i;
    for (i = 0;i < OPERATIONS; i++)
    {
        struct timespec sleep_time;
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = rand()% 30000000 + 1e7;  // sleep for 0.01 to 0.04 second
        nanosleep(&sleep_time, NULL);
        
        pthread_mutex_lock(&m); // lock the mutex
        
        while(resource_counter == -1 || write_times == 0)  // writer is using the resource, wait for the writer, or that writer has not yet written
            pthread_cond_wait(&c_readers, &m);
        resource_counter++;
        
        pthread_mutex_unlock(&m);  // unlock the mutex, allow multiple readers
        
        read_value = value;
        read_write_time = write_times;
        
        pthread_mutex_lock(&m); // lock the mutex to modify resource_counter
        resource_counter--;
        if (resource_counter == 0)
            pthread_cond_signal(&c_writers);  // signal the writer if no reader is working
        pthread_mutex_unlock(&m);
        
        printf("Reader: Value %d, read time %d, write time %d\n", value, i, write_times); fflush(stdout);
    }
    return 0;
}

void *writer(void *param){
    int prev_value, prev_write_time;
    int i;
    for (i = 0;i < OPERATIONS; i++)
    {
        struct timespec sleep_time;
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = rand() % 35000000 + 1e7;  // sleep for 0.01 to 0.035 second
        nanosleep(&sleep_time, NULL);
        
        pthread_mutex_lock(&m); // lock the mutex
        while(resource_counter != 0)  // reader is working
            pthread_cond_wait(&c_writers, &m);
        resource_counter = -1;  // writer is working
        pthread_mutex_unlock(&m);  // unlock the mutex
        
        // generate some random number
        value = rand() % 1000;  // range between 0 to 999
        prev_value = value;
        prev_write_time = ++write_times;
        
        pthread_mutex_lock(&m); // lock the mutex
        resource_counter = 0;
        pthread_mutex_unlock(&m);  // unlock the mutex
        
        // notify readers & writers
        pthread_cond_broadcast(&c_readers);
        pthread_cond_signal(&c_writers);
        printf("Writer: Value %d, write time: %d\n", prev_value, prev_write_time);
        fflush(stdout);
    }
    return 0;
}
