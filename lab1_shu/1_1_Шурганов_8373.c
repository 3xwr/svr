/*
* Выполнил: Шурганов Юрий, 8373
* Задание: 1_1. «Поставщик – Потребитель» (v.3.1)
* Дата выполнения: 23.02.2022
* Скрипт для компиляции и запуска программы:
* gcc -pthread 1_1_Шурганов_8373.с 
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 *      Эта программа для многопоточной работы с поставщиком и потребителем, использует семафоры для разделения критических участков.
 */
// ------------------------------------------- //
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define TIME_CONSUME 2000000
#define TIME_SUPPLY 1000000

#define EXIT_SUCCESS 0

#define MAX_BUF 5
#define MIN_BUF 0

int buf = 0;

sem_t sem;
time_t t;

void* Consumer(void* args) 
{
    for(;;) 
    { 
        if(buf <= MIN_BUF) 
        {
            sem_wait(&sem); 
            for(;;) 
            { 
                if(buf > MIN_BUF) 
                {
                    sem_post(&sem);
                    break; 
                }
            };
        }
        sem_wait(&sem);
        time(&t);
        printf("CONSUMER START %s", ctime(&t));
        buf--;
        printf("BUFFER %d\n", buf);
        printf("CONSUMER END %s", ctime(&t));
        sem_post(&sem);
        usleep(TIME_CONSUME);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) 
{
    for(;;) 
    {
        if(buf >= MAX_BUF) 
        { 
            sem_wait(&sem);
            for(;;) 
            {
                if(buf < MAX_BUF) 
                {
                    sem_post(&sem);
                    break;
                }
            };
        }        
        sem_wait(&sem);   
        time(&t);     
        printf("SUPPLIER START %s", ctime(&t));
        buf++;
        printf("BUFFER %d\n", buf);
        printf("SUPPLIER END %s", ctime(&t));
        sem_post(&sem);
        usleep(TIME_SUPPLY);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    sem_init(&sem, NULL, 2);
    pthread_t thread_Cons, thread_Sup;
    pthread_create(&thread_Cons, NULL, &Consumer, NULL);
    pthread_create(&thread_Sup, NULL, &Supplier, NULL);
    pthread_join(thread_Cons, NULL);
    pthread_join(thread_Sup, NULL);
    return EXIT_SUCCESS;
}
// ------------------------------------------- //
/*
SUPPLIER START Wed Feb 23 19:31:05 2022
BUFFER 1
SUPPLIER END Wed Feb 23 19:31:05 2022
CONSUMER START Wed Feb 23 19:31:06 2022
BUFFER 0
CONSUMER END Wed Feb 23 19:31:06 2022
SUPPLIER START Wed Feb 23 19:31:06 2022
BUFFER 1
SUPPLIER END Wed Feb 23 19:31:06 2022
SUPPLIER START Wed Feb 23 19:31:07 2022
BUFFER 2
SUPPLIER END Wed Feb 23 19:31:07 2022
CONSUMER START Wed Feb 23 19:31:08 2022
BUFFER 1
CONSUMER END Wed Feb 23 19:31:08 2022
SUPPLIER START Wed Feb 23 19:31:08 2022
BUFFER 2
SUPPLIER END Wed Feb 23 19:31:08 2022
SUPPLIER START Wed Feb 23 19:31:09 2022
BUFFER 3
SUPPLIER END Wed Feb 23 19:31:09 2022
CONSUMER START Wed Feb 23 19:31:10 2022
BUFFER 2
CONSUMER END Wed Feb 23 19:31:10 2022
SUPPLIER START Wed Feb 23 19:31:10 2022
BUFFER 3
SUPPLIER END Wed Feb 23 19:31:10 2022
SUPPLIER START Wed Feb 23 19:31:11 2022
BUFFER 4
SUPPLIER END Wed Feb 23 19:31:11 2022
CONSUMER START Wed Feb 23 19:31:12 2022
BUFFER 3
CONSUMER END Wed Feb 23 19:31:12 2022
SUPPLIER START Wed Feb 23 19:31:12 2022
BUFFER 4
SUPPLIER END Wed Feb 23 19:31:12 2022
SUPPLIER START Wed Feb 23 19:31:13 2022
BUFFER 5
SUPPLIER END Wed Feb 23 19:31:13 2022
CONSUMER START Wed Feb 23 19:31:14 2022
BUFFER 4
CONSUMER END Wed Feb 23 19:31:14 2022
SUPPLIER START Wed Feb 23 19:31:14 2022
BUFFER 5
SUPPLIER END Wed Feb 23 19:31:14 2022
CONSUMER START Wed Feb 23 19:31:16 2022
BUFFER 4
CONSUMER END Wed Feb 23 19:31:16 2022
SUPPLIER START Wed Feb 23 19:31:16 2022
BUFFER 5
SUPPLIER END Wed Feb 23 19:31:16 2022
*/