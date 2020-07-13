#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


pthread_mutex_t mutex_lock;

int g_count = 0;

void *t_function(void *data){
    

    int i;
    char* name = (char*)data;

    pthread_mutex_lock(&mutex_lock);

    g_count = 0;
    for(i = 0; i < 3; i++){
	printf("%s count %d\n", name , g_count);
	g_count++;
	sleep(1);
    }
    

    pthread_mutex_unlock(&mutex_lock);
}


int main(){
    
    pthread_t p_thread1, p_thread2;
    int status;

    pthread_create(&p_thread1, NULL, t_function, (void * )"Thread1");
    pthread_create(&p_thread2, NULL, t_function, (void * )"Thread2");
    
    pthread_join(p_thread1, (void*)&status);
    pthread_join(p_thread2, (void*)&status);


    return 0;



}

