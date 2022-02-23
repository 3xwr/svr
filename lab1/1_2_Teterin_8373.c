/*
* Выполнил: Тетерин Дмитрий, 8373
* Задание: 1_2. «Поставщик – Потребитель» (v.3.1)
* Дата выполнения: 23.02.2022
* Скрипт для компиляции и запуска программы:
* gcc -pthread 1_2_Teterin_8373.с 
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 *      Данная программа реализует паттерн Поставщик – Потребитель с использованием двух потоков.
 *      Для синхронизации между потребителем и поставщиком используются условные переменные и мьютексы..
 *      Полный буфер здесь - буфер со значением 10.
 *      Для ограничения записи/доступа к полному/пустому буфферу используются условные переменные.
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

pthread_cond_t cond;
pthread_mutex_t mutex;
time_t t;

void* Consumer(void* args) {
    while(true) {
        pthread_mutex_lock(&mutex);
        time(&t);
        if(Buffer <= 0) {
            pthread_cond_wait(&cond, &mutex); /* Проверяем условие и ожидаем условную переменную */
        }
        printf("time at consume start: %ld\n", t);
        Buffer--;
        printf("Buffer = %d\n", Buffer);
        printf("time at consume end: %ld\n", t);
        pthread_cond_signal(&cond); /* Даем сигнал условной переменной после критического участка */
        pthread_mutex_unlock(&mutex);
        sleep(TIME_1);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) {
    while(true) {  
        pthread_mutex_lock(&mutex);
        time(&t); 
        if(Buffer >= 10) {
            pthread_cond_wait(&cond, &mutex); /* Проверяем условие и ожидаем условную переменную */
        } 
        printf("time at supply start: %ld\n", t);
        Buffer++;
        printf("Buffer = %d\n", Buffer);
        printf("time at supply end: %ld\n", t);
        pthread_cond_signal(&cond); /* Даем сигнал условной переменной после критического участка */
        pthread_mutex_unlock(&mutex);
        sleep(TIME_2);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    pthread_t thread_Cons, thread_Sup;
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&cond, NULL);
    pthread_create(&thread_Cons, NULL, &Consumer, NULL);
    pthread_create(&thread_Sup, NULL, &Supplier, NULL);
    pthread_join(thread_Cons, NULL);
    pthread_join(thread_Sup, NULL);
    return EXIT_SUCCESS;
}
// ------------------------------------------- //
/*
time at supply start: 1645643517
Buffer = 1
time at supply end: 1645643517
time at consume start: 1645643517
Buffer = 0
time at consume end: 1645643517
time at supply start: 1645643518
Buffer = 1
time at supply end: 1645643518
time at consume start: 1645643519
Buffer = 0
time at consume end: 1645643519
time at supply start: 1645643519
Buffer = 1
time at supply end: 1645643519
time at supply start: 1645643520
Buffer = 2
time at supply end: 1645643520
time at consume start: 1645643521
Buffer = 1
time at consume end: 1645643521
time at supply start: 1645643521
Buffer = 2
time at supply end: 1645643521
time at supply start: 1645643522
Buffer = 3
time at supply end: 1645643522
time at consume start: 1645643523
Buffer = 2
time at consume end: 1645643523
time at supply start: 1645643523
Buffer = 3
time at supply end: 1645643523
time at supply start: 1645643524
Buffer = 4
time at supply end: 1645643524
time at consume start: 1645643525
Buffer = 3
time at consume end: 1645643525
time at supply start: 1645643525
Buffer = 4
time at supply end: 1645643525
time at supply start: 1645643526
Buffer = 5
time at supply end: 1645643526
time at consume start: 1645643527
Buffer = 4
time at consume end: 1645643527
time at supply start: 1645643527
Buffer = 5
time at supply end: 1645643527
time at supply start: 1645643528
Buffer = 6
time at supply end: 1645643528
time at consume start: 1645643529
Buffer = 5
time at consume end: 1645643529
time at supply start: 1645643529
Buffer = 6
time at supply end: 1645643529
time at supply start: 1645643530
Buffer = 7
time at supply end: 1645643530
time at consume start: 1645643531
Buffer = 6
time at consume end: 1645643531
time at supply start: 1645643531
Buffer = 7
time at supply end: 1645643531
time at supply start: 1645643532
Buffer = 8
time at supply end: 1645643532
time at consume start: 1645643533
Buffer = 7
time at consume end: 1645643533
time at supply start: 1645643533
Buffer = 8
time at supply end: 1645643533
time at supply start: 1645643534
Buffer = 9
time at supply end: 1645643534
time at consume start: 1645643535
Buffer = 8
time at consume end: 1645643535
time at supply start: 1645643535
Buffer = 9
time at supply end: 1645643535
time at supply start: 1645643536
Buffer = 10
time at supply end: 1645643536
time at consume start: 1645643537
Buffer = 9
time at consume end: 1645643537
time at supply start: 1645643537
Buffer = 10
time at supply end: 1645643537
time at consume start: 1645643539
Buffer = 9
time at consume end: 1645643539
time at supply start: 1645643539
Buffer = 10
time at supply end: 1645643539
time at consume start: 1645643541
Buffer = 9
time at consume end: 1645643541
time at supply start: 1645643541
Buffer = 10
time at supply end: 1645643541
time at consume start: 1645643543
Buffer = 9
time at consume end: 1645643543
time at supply start: 1645643543
Buffer = 10
time at supply end: 1645643543
time at consume start: 1645643545
Buffer = 9
time at consume end: 1645643545
time at supply start: 1645643545
Buffer = 10
*/