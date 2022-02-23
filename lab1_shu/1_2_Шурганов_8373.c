/*
* Выполнил: Шурганов Юрий, 8373
* Задание: 1_2. «Поставщик – Потребитель» (v.3.1)
* Дата выполнения: 23.02.2022
* Скрипт для компиляции и запуска программы:
* gcc -pthread 1_2_Шурганов_8373.с 
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 *      Эта программа для многопоточной работы с поставщиком и потребителем, использует условные переменные для разделения критических участков.
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

pthread_cond_t cond;
pthread_mutex_t mutex;
time_t t;

void* Consumer(void* args) 
{
    for(;;) 
    { 
        pthread_mutex_lock(&mutex);
        time(&t);
        if(buf <= MIN_BUF) {
            pthread_cond_wait(&cond, &mutex); 
        }
        printf("CONSUMER START %s", ctime(&t));
        buf--;
        printf("BUFFER %d\n", buf);
        printf("CONSUMER END %s", ctime(&t));
        pthread_cond_signal(&cond); 
        pthread_mutex_unlock(&mutex);
        usleep(TIME_CONSUME);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) 
{
    for(;;) 
    {
        pthread_mutex_lock(&mutex);
        time(&t);
        if(buf >= MAX_BUF) {
            pthread_cond_wait(&cond, &mutex); 
        } 
        printf("SUPPLIER START %s", ctime(&t));
        buf++;
        printf("BUFFER %d\n", buf);
        printf("SUPPLIER END %s", ctime(&t));
        pthread_cond_signal(&cond); 
        pthread_mutex_unlock(&mutex);
        usleep(TIME_SUPPLY);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread_Cons, thread_Sup;
    pthread_create(&thread_Cons, NULL, &Consumer, NULL);
    pthread_create(&thread_Sup, NULL, &Supplier, NULL);
    pthread_join(thread_Cons, NULL);
    pthread_join(thread_Sup, NULL);
    return EXIT_SUCCESS;
}
// ------------------------------------------- //
/*
SUPPLIER START Wed Feb 23 19:36:47 2022
BUFFER 1
SUPPLIER END Wed Feb 23 19:36:47 2022
CONSUMER START Wed Feb 23 19:36:47 2022
BUFFER 0
CONSUMER END Wed Feb 23 19:36:47 2022
SUPPLIER START Wed Feb 23 19:36:48 2022
BUFFER 1
SUPPLIER END Wed Feb 23 19:36:48 2022
CONSUMER START Wed Feb 23 19:36:49 2022
BUFFER 0
CONSUMER END Wed Feb 23 19:36:49 2022
SUPPLIER START Wed Feb 23 19:36:49 2022
BUFFER 1
SUPPLIER END Wed Feb 23 19:36:49 2022
SUPPLIER START Wed Feb 23 19:36:50 2022
BUFFER 2
SUPPLIER END Wed Feb 23 19:36:50 2022
CONSUMER START Wed Feb 23 19:36:51 2022
BUFFER 1
CONSUMER END Wed Feb 23 19:36:51 2022
SUPPLIER START Wed Feb 23 19:36:51 2022
BUFFER 2
SUPPLIER END Wed Feb 23 19:36:51 2022
SUPPLIER START Wed Feb 23 19:36:52 2022
BUFFER 3
SUPPLIER END Wed Feb 23 19:36:52 2022
CONSUMER START Wed Feb 23 19:36:53 2022
BUFFER 2
CONSUMER END Wed Feb 23 19:36:53 2022
SUPPLIER START Wed Feb 23 19:36:53 2022
BUFFER 3
SUPPLIER END Wed Feb 23 19:36:53 2022
SUPPLIER START Wed Feb 23 19:36:54 2022
BUFFER 4
SUPPLIER END Wed Feb 23 19:36:54 2022
CONSUMER START Wed Feb 23 19:36:55 2022
BUFFER 3
CONSUMER END Wed Feb 23 19:36:55 2022
SUPPLIER START Wed Feb 23 19:36:55 2022
BUFFER 4
SUPPLIER END Wed Feb 23 19:36:55 2022
SUPPLIER START Wed Feb 23 19:36:56 2022
BUFFER 5
SUPPLIER END Wed Feb 23 19:36:56 2022
CONSUMER START Wed Feb 23 19:36:57 2022
BUFFER 4
CONSUMER END Wed Feb 23 19:36:57 2022
SUPPLIER START Wed Feb 23 19:36:57 2022
BUFFER 5
SUPPLIER END Wed Feb 23 19:36:57 2022
CONSUMER START Wed Feb 23 19:36:59 2022
BUFFER 4
CONSUMER END Wed Feb 23 19:36:59 2022
SUPPLIER START Wed Feb 23 19:36:59 2022
BUFFER 5
SUPPLIER END Wed Feb 23 19:36:59 2022
*/