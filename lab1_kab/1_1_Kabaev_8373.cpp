/*
* Выполнил: Кабаев Роман, 8373
* Задание: 1_1. «Поставщик – Потребитель» (v.3.1)
* Дата выполнения: 23.02.2022
* Скрипт для компиляции и запуска программы:
* g++ -pthread 1_1_Kabaev_8373.сpp
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 *      Эта программа синхронизует потребителя и поставщика семфорами.
 *      Буфер заполняется при значении 3, считается пустым при значении 0.
 */
// ------------------------------------------- //
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <iostream>


#define EXIT_SUCCESS 0
#define TIME_1 3
#define TIME_2 1



sem_t semaphore;
time_t tm;

int Buffer = 0;

void* Consumer(void* args) 
{
    while(true) 
    { 
        if(Buffer <= 0) //Проверяем буффер на пустоту
        { 
            sem_wait(&semaphore); 
            while(true) 
            { 
                if(Buffer > 0) 
                {
                    sem_post(&semaphore);
                    break; // Если буффер больше не пустой, можем выходить из ожидания 
                }
            };
        }
        sem_wait(&semaphore);
        time(&tm);
        std::cout << "Время в начале потребления " << ctime(&tm);
        Buffer--;
        std::cout << "Значение буффера " << Buffer << std::endl;
        std::cout << "Время в конце потребления " << ctime(&tm) << std::endl;
        sem_post(&semaphore);
        sleep(TIME_1);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) 
{
    while(true) 
    {
        if(Buffer >= 3)  //Проверяем буффер на полноту
        { 
            sem_wait(&semaphore);
            while(true) 
            { 
                if(Buffer < 3) 
                {
                    sem_post(&semaphore);
                    break; // Если буффер больше не полон, можем выходить из ожидания 
                }
            };
        }        
        sem_wait(&semaphore);   
        time(&tm);     
        std::cout << "Время в начале поступления " << ctime(&tm);
        Buffer++;
        std::cout << "Значение буффера " << Buffer << std::endl;
        std::cout << "Время в конце поступления " << ctime(&tm) << std::endl;
        sem_post(&semaphore);
        sleep(TIME_2);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) 
{
    sem_init(&semaphore, NULL, 2);
    pthread_t thread_Cons, thread_Sup;
    pthread_create(&thread_Cons, NULL, &Consumer, NULL);
    pthread_create(&thread_Sup, NULL, &Supplier, NULL);
    pthread_join(thread_Cons, NULL);
    pthread_join(thread_Sup, NULL);
    return EXIT_SUCCESS;
}
// ------------------------------------------- //
/*
Время в начале поступления Wed Feb 23 22:59:18 2022
Значение буффера 1
Время в конце поступления Wed Feb 23 22:59:18 2022

Время в начале поступления Wed Feb 23 22:59:19 2022
Значение буффера 2
Время в конце поступления Wed Feb 23 22:59:19 2022

Время в начале потребления Wed Feb 23 22:59:20 2022
Значение буффера 1
Время в конце потребления Wed Feb 23 22:59:20 2022

Время в начале поступления Wed Feb 23 22:59:20 2022
Значение буффера 2
Время в конце поступления Wed Feb 23 22:59:20 2022

Время в начале поступления Wed Feb 23 22:59:21 2022
Значение буффера 3
Время в конце поступления Wed Feb 23 22:59:21 2022

Время в начале потребления Wed Feb 23 22:59:23 2022
Значение буффера 2
Время в конце потребления Время в начале поступления Wed Feb 23 22:59:23 2022

Wed Feb 23 22:59:23 2022
Значение буффера 3
Время в конце поступления Wed Feb 23 22:59:23 2022
*/