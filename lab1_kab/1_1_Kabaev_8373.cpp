/*
* Выполнил: Тетерин Дмитрий, 8373
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

#define TIME_1 2
#define TIME_2 1

#define EXIT_SUCCESS 0

int Buffer = 0;

sem_t s;
time_t t;

void* Consumer(void* args) {
    while(true) { 
        if(Buffer <= 0) { /* Здесь происходит проверка пустого буффера */
            sem_wait(&s); 
            while(true) { /* В бесконечном цикле проверяем условие */
                if(Buffer > 0) {
                    sem_post(&s);
                    break; /* Если оно изменилось выходим из цикла и постим семафор */
                }
            };
        }
        sem_wait(&s);
        time(&t);
        printf("time at consume start: %ld\n", t);
        Buffer--;
        printf("Buffer = %d\n", Buffer);
        printf("time at consume end: %ld\n", t);
        sem_post(&s);
        sleep(TIME_1);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) {
    while(true) {
        if(Buffer >= 10) { /* Здесь происходит проверка полного буффера */
            sem_wait(&s);
            while(true) { /* В бесконечном цикле проверяем условие */
                if(Buffer < 10) {
                    sem_post(&s);
                    break; /* Если оно изменилось выходим из цикла и постим семафор */
                }
            };
        }        
        sem_wait(&s);   
        time(&t);     
        printf("time at supply start: %ld\n", t);
        Buffer++;
        printf("Buffer = %d\n", Buffer);
        printf("time at supply end: %ld\n", t);
        sem_post(&s);
        sleep(TIME_2);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    sem_init(&s, NULL, 2);
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
Buffer = 1
time at supply end: 1645643308
time at consume start: 1645643308
Buffer = 0
time at consume end: 1645643308
time at supply start: 1645643309
Buffer = 1
time at supply end: 1645643309
time at consume start: 1645643310
Buffer = 0
time at consume end: 1645643310
time at supply start: 1645643310
Buffer = 1
time at supply end: 1645643310
time at supply start: 1645643311
Buffer = 2
time at supply end: 1645643311
time at consume start: 1645643312
Buffer = 1
time at consume end: 1645643312
time at supply start: 1645643312
Buffer = 2
time at supply end: 1645643312
time at supply start: 1645643313
Buffer = 3
time at supply end: 1645643313
time at consume start: 1645643314
Buffer = 2
time at consume end: 1645643314
time at supply start: 1645643314
Buffer = 3
time at supply end: 1645643314
time at supply start: 1645643315
Buffer = 4
time at supply end: 1645643315
time at consume start: 1645643316
Buffer = 3
time at consume end: 1645643316
time at supply start: 1645643316
Buffer = 4
time at supply end: 1645643316
time at supply start: 1645643317
Buffer = 5
time at supply end: 1645643317
time at consume start: 1645643318
Buffer = 4
time at consume end: 1645643318
time at supply start: 1645643318
Buffer = 5
time at supply end: 1645643318
time at supply start: 1645643319
Buffer = 6
time at supply end: 1645643319
time at consume start: 1645643320
Buffer = 5
time at consume end: 1645643320
time at supply start: 1645643320
Buffer = 6
time at supply end: 1645643320
time at supply start: 1645643321
Buffer = 7
time at supply end: 1645643321
time at consume start: 1645643322
Buffer = 6
time at consume end: 1645643322
time at supply start: 1645643322
Buffer = 7
time at supply end: 1645643322
time at supply start: 1645643323
Buffer = 8
time at supply end: 1645643323
time at consume start: 1645643324
Buffer = 7
time at consume end: 1645643324
time at supply start: 1645643324
Buffer = 8
time at supply end: 1645643324
time at supply start: 1645643325
Buffer = 9
time at supply end: 1645643325
time at consume start: 1645643326
Buffer = 8
time at consume end: 1645643326
time at supply start: 1645643326
Buffer = 9
time at supply end: 1645643326
time at supply start: 1645643327
Buffer = 10
time at supply end: 1645643327
time at consume start: 1645643328
Buffer = 9
time at consume end: 1645643328
time at supply start: 1645643328
Buffer = 10
time at supply end: 1645643328
time at consume start: 1645643330
Buffer = 9
time at consume end: 1645643330
time at supply start: 1645643330
Buffer = 10
time at supply end: 1645643330
*/