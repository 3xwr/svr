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
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread_Cons, NULL, &Consumer, NULL);
    pthread_create(&thread_Sup, NULL, &Supplier, NULL);
    pthread_join(thread_Cons, NULL);
    pthread_join(thread_Sup, NULL);
    return EXIT_SUCCESS;
}
// ------------------------------------------- //
/*
time at supply start: 1645644930
Buffer = 1
time at supply end: 1645644930
time at consume start: 1645644930
Buffer = 0
time at consume end: 1645644930
time at supply start: 1645644931
Buffer = 1
time at supply end: 1645644931
time at consume start: 1645644932
Buffer = 0
time at consume end: 1645644932
time at supply start: 1645644932
Buffer = 1
time at supply end: 1645644932
time at supply start: 1645644933
Buffer = 2
time at supply end: 1645644933
time at consume start: 1645644934
Buffer = 1
time at consume end: 1645644934
time at supply start: 1645644934
Buffer = 2
time at supply end: 1645644934
time at supply start: 1645644935
Buffer = 3
time at supply end: 1645644935
time at consume start: 1645644936
Buffer = 2
time at consume end: 1645644936
time at supply start: 1645644936
Buffer = 3
time at supply end: 1645644936
time at supply start: 1645644937
Buffer = 4
time at supply end: 1645644937
time at consume start: 1645644938
Buffer = 3
time at consume end: 1645644938
time at supply start: 1645644938
Buffer = 4
time at supply end: 1645644938
time at supply start: 1645644939
Buffer = 5
time at supply end: 1645644939
time at consume start: 1645644940
Buffer = 4
time at consume end: 1645644940
time at supply start: 1645644940
Buffer = 5
time at supply end: 1645644940
time at supply start: 1645644941
Buffer = 6
time at supply end: 1645644941
time at consume start: 1645644942
Buffer = 5
time at consume end: 1645644942
time at supply start: 1645644942
Buffer = 6
time at supply end: 1645644942
time at supply start: 1645644943
Buffer = 7
time at supply end: 1645644943
time at consume start: 1645644944
Buffer = 6
time at consume end: 1645644944
time at supply start: 1645644944
Buffer = 7
time at supply end: 1645644944
time at supply start: 1645644945
Buffer = 8
time at supply end: 1645644945
time at consume start: 1645644946
Buffer = 7
time at consume end: 1645644946
time at supply start: 1645644946
Buffer = 8
time at supply end: 1645644946
time at supply start: 1645644947
Buffer = 9
time at supply end: 1645644947
time at consume start: 1645644948
Buffer = 8
time at consume end: 1645644948
time at supply start: 1645644948
Buffer = 9
time at supply end: 1645644948
time at supply start: 1645644949
Buffer = 10
time at supply end: 1645644949
time at consume start: 1645644950
Buffer = 9
time at consume end: 1645644950
time at supply start: 1645644950
Buffer = 10
time at supply end: 1645644950
time at consume start: 1645644952
Buffer = 9
time at consume end: 1645644952
time at supply start: 1645644952
Buffer = 10
time at supply end: 1645644952
*/