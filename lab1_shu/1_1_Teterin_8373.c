/*
* Выполнил: Шурганов Юрий, 8373
* Задание: 1_1. «Поставщик – Потребитель» (v.3.1)
* Дата выполнения: 23.02.2022
* Скрипт для компиляции и запуска программы:
* gcc -pthread 1_1_Teterin_8373.с 
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 *      Данная программа реализует паттерн Поставщик – Потребитель с использованием двух потоков.
 *      Для синхронизации между потребителем и поставщиком используются семафоры.
 *      Полный буфер здесь - буфер со значением 10.
 *      Для ограничения записи/доступа к полному/пустому буфферу используются семафоры.
 *      Одновременная работа в критической области не допускатеся.
 */
// ------------------------------------------- //
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define TIME_CONSUME 200
#define TIME_SUPPLY 100

#define EXIT_SUCCESS 0

int buf = 0;

sem_t sem;
time_t t;

void* Consumer(void* args) 
{
    for(;;) 
    { 
        if(buf <= 0) 
        { /* Здесь происходит проверка пустого буффера */
            sem_wait(&sem); 
            for(;;) 
            { /* В бесконечном цикле проверяем условие */
                if(buf > 0) 
                {
                    sem_post(&sem);
                    break; /* Если оно изменилось выходим из цикла и постим семафор */
                }
            };
        }
        sem_wait(&sem);
        time(&t);
        printf("CONSUMER START %ld\n", ctime(&t));
        buf--;
        printf("BUFFER %d\n", buf);
        printf("CONSUMER END %ld\n", ctime(&t));
        sem_post(&sem);
        usleep(TIME_CONSUME);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) 
{
    for(;;) 
    {
        if(buf >= 10) 
        { /* Здесь происходит проверка полного буффера */
            sem_wait(&sem);
            for(;;) 
            { /* В бесконечном цикле проверяем условие */
                if(buf < 10) 
                {
                    sem_post(&sem);
                    break; /* Если оно изменилось выходим из цикла и постим семафор */
                }
            };
        }        
        sem_wait(&sem);   
        time(&t);     
        printf("SUPPLIER START %ld\n", ctime(&t));
        buf++;
        printf("BUFFER %d\n", buf);
        printf("SUPPLIER END %ld\n", ctime(&t));
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
time at supply start: 1645643308
buf = 1
time at supply end: 1645643308
time at consume start: 1645643308
buf = 0
time at consume end: 1645643308
time at supply start: 1645643309
buf = 1
time at supply end: 1645643309
time at consume start: 1645643310
buf = 0
time at consume end: 1645643310
time at supply start: 1645643310
buf = 1
time at supply end: 1645643310
time at supply start: 1645643311
buf = 2
time at supply end: 1645643311
time at consume start: 1645643312
buf = 1
time at consume end: 1645643312
time at supply start: 1645643312
buf = 2
time at supply end: 1645643312
time at supply start: 1645643313
buf = 3
time at supply end: 1645643313
time at consume start: 1645643314
buf = 2
time at consume end: 1645643314
time at supply start: 1645643314
buf = 3
time at supply end: 1645643314
time at supply start: 1645643315
buf = 4
time at supply end: 1645643315
time at consume start: 1645643316
buf = 3
time at consume end: 1645643316
time at supply start: 1645643316
buf = 4
time at supply end: 1645643316
time at supply start: 1645643317
buf = 5
time at supply end: 1645643317
time at consume start: 1645643318
buf = 4
time at consume end: 1645643318
time at supply start: 1645643318
buf = 5
time at supply end: 1645643318
time at supply start: 1645643319
buf = 6
time at supply end: 1645643319
time at consume start: 1645643320
buf = 5
time at consume end: 1645643320
time at supply start: 1645643320
buf = 6
time at supply end: 1645643320
time at supply start: 1645643321
buf = 7
time at supply end: 1645643321
time at consume start: 1645643322
buf = 6
time at consume end: 1645643322
time at supply start: 1645643322
buf = 7
time at supply end: 1645643322
time at supply start: 1645643323
buf = 8
time at supply end: 1645643323
time at consume start: 1645643324
buf = 7
time at consume end: 1645643324
time at supply start: 1645643324
buf = 8
time at supply end: 1645643324
time at supply start: 1645643325
buf = 9
time at supply end: 1645643325
time at consume start: 1645643326
buf = 8
time at consume end: 1645643326
time at supply start: 1645643326
buf = 9
time at supply end: 1645643326
time at supply start: 1645643327
buf = 10
time at supply end: 1645643327
time at consume start: 1645643328
buf = 9
time at consume end: 1645643328
time at supply start: 1645643328
buf = 10
time at supply end: 1645643328
time at consume start: 1645643330
buf = 9
time at consume end: 1645643330
time at supply start: 1645643330
buf = 10
time at supply end: 1645643330
*/