#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>



/*
 *  int sem_init(sem_t *sem, int pshared, unsigned int value);
 *  
 *  sem  : init 할 semaphore 객체
 *  pshred : 0/ !0 ,  0-> process 간 , !0 => inner only 
 *  value : init value
 *
 */


#define MAX_THREAD_NUM 2

int g_count = 0;
sem_t mysem; // semaphore declare


void *t_function(void *data){
    

    int i;
    int* name = (int*)data;

    g_count = 0;
    for(i = 0; i < 3; i++){
	printf("%d count %d\n", *name , g_count);
	g_count++;
	sleep(1);
    }
    

}

int main(){

    pthread_t threads[MAX_THREAD_NUM];
    int thr_id;
    int status;
    int i =0;
    if(sem_init(&mysem, 0, 1) == -1){
	perror("Error");
	exit(0);
    }
    
    for(i = 0; i < MAX_THREAD_NUM; i++){
	thr_id  = pthread_create(&threads[i], NULL, t_function, (void*)&i);
	
    }
    

    for(i = 0; i < MAX_THREAD_NUM; i++){
	pthread_join(threads[i], NULL);
	
    }

    return 0;

}


