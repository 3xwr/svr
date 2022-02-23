/*
* Выполнил: Кабаев Роман, 8373
* Задание: 1_2. «Поставщик – Потребитель» (v.3.1)
* Дата выполнения: 23.02.2022
* Скрипт для компиляции и запуска программы:
* g++ -pthread 1_2_Kabaev_8373.сpp
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 *      Эта программа синхронизует потребителя и поставщика с помощью условных переменных и мьютексов.
 *      Буфер заполняется при значении 3, считается пустым при значении 0.
 */
// ------------------------------------------- //
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <iostream>


#define EXIT_SUCCESS 0
#define TIME_1 3
#define TIME_2 1

int Buffer = 0;

time_t tm;

pthread_cond_t cond;
pthread_mutex_t mutex;

void* Consumer(void* args) 
{
    while(true) 
    {
        pthread_mutex_lock(&mutex);
        time(&tm);
        if(Buffer <= 0) 
        {
            pthread_cond_wait(&cond, &mutex); //Ожидаем не пустого буффера
        }
        std::cout << "Время в начале потребления " << ctime(&tm);
        Buffer--;
        std::cout << "Значение буффера " << Buffer << std::endl;
        std::cout << "Время в конце потребления " << ctime(&tm) << std::endl;
        pthread_cond_signal(&cond); //Даем сигнал переменной
        pthread_mutex_unlock(&mutex);
        sleep(TIME_1);
    };
    return EXIT_SUCCESS;
}

void* Supplier(void* args) 
{
    while(true) 
    {  
        pthread_mutex_lock(&mutex);
        time(&tm); 
        if(Buffer >= 3) 
        {
            pthread_cond_wait(&cond, &mutex); //Ожидаем не полного буффера
        } 
        std::cout << "Время в начале поступления " << ctime(&tm);
        Buffer++;
        std::cout << "Значение буффера " << Buffer << std::endl;
        std::cout << "Время в конце поступления " << ctime(&tm) << std::endl;
        pthread_cond_signal(&cond); //Даем сигнал переменной
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
Время в начале поступления Wed Feb 23 16:19:24 2022
Значение буффера 1
Время в конце поступления Wed Feb 23 16:19:24 2022

Время в начале потребления Wed Feb 23 16:19:24 2022
Значение буффера 0
Время в конце потребления Wed Feb 23 16:19:24 2022

Время в начале поступления Wed Feb 23 16:19:25 2022
Значение буффера 1
Время в конце поступления Wed Feb 23 16:19:25 2022

Время в начале поступления Wed Feb 23 16:19:26 2022
Значение буффера 2
Время в конце поступления Wed Feb 23 16:19:26 2022

Время в начале потребления Wed Feb 23 16:19:27 2022
Значение буффера 1
Время в конце потребления Wed Feb 23 16:19:27 2022

Время в начале поступления Wed Feb 23 16:19:27 2022
Значение буффера 2
Время в конце поступления Wed Feb 23 16:19:27 2022

Время в начале поступления Wed Feb 23 16:19:28 2022
Значение буффера 3
Время в конце поступления Wed Feb 23 16:19:28 2022

Время в начале потребления Wed Feb 23 16:19:30 2022
Значение буффера 2
Время в конце потребления Wed Feb 23 16:19:30 2022

Время в начале поступления Wed Feb 23 16:19:30 2022
Значение буффера 3
Время в конце поступления Wed Feb 23 16:19:30 2022
*/