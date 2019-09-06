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

void *reader();
void *writer();

int value = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_readers = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_writers = PTHREAD_COND_INITIALIZER;


int main(int argc, const char * argv[]) {
    // insert code here...
    pthread_t t_readers[N_READERS], t_writers[N_WRITERS];
    
    for (int i = 0;i < N_READERS; i++){
        if (pthread_create(&t_readers[i], NULL, reader, NULL) != 0)
        {
            printf("Reader %d creation failed\n", i);
            exit(1);
        }
        pthread_join(t_readers[i], NULL);
    }
    for (int i = 0;i < N_WRITERS; i++)
    {
        if (pthread_create(&t_writers[i], NULL, writer, NULL) != 0)
        {
            printf("Writer %d creation failed\n", i);
            exit(1);
        }
        pthread_join(t_writers[i], NULL);
    }
    
    printf("Parent quiting\n");
    return 0;
};

void *reader(){
    for (int i = 0;i < OPERATIONS; i++)
    {
        while(
    }
    return 0;
}

void *writer(){
    
    return 0;
}
