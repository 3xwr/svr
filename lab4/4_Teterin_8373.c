/*
* Выполнил: Тетерин Дмитрий, 8373
* Задание: 3. «Обеспечение таймаута»
* Дата выполнения: 23.03.2022
* Скрипт для компиляции и запуска программы:
* gcc -pthread 3_Teterin_8373.с 
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 * Данная программа реализует обеспечение таймаута с помощью сигналов.
 */
// ------------------------------------------- //
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define DEADLINE 52000
#define SOFT_DT 54000
#define MY_SIGNAL 48

#define UNUSED(x) (void)(x)

// void doControl_500() {
//     printf("Procedure #1, call time %f ms, time since last call %f ms.");
// }

// void doControl_750() {
//     printf("Procedure #2, call time %f ms, time since last call %f ms.");
// }

// void doControl_1000() {
//     printf("Procedure #3, call time %f ms, time since last call %f ms.");
// }

void test() {
    printf("TEST");
}

void alarmHandler() {
}

void *doStuff() {
}

int main(int argc, char *argv[])
{
    struct sigevent event;
    struct itimerspec itime;
    timer_t timer_id;

    sigset_t set;
    pthread_t t;



    struct sigaction act;

    memset(&act,0,sizeof(struct sigaction));
    act.sa_handler = test;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = test;

    sigemptyset(&act.sa_mask);


    memset(&event, 0, sizeof(struct sigevent));
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = MY_SIGNAL;


    int ret = timer_create(CLOCK_REALTIME, &event, &timer_id);

    memset(&itime,0,sizeof(struct timespec));
    itime.it_value.tv_sec = 1;
    itime.it_value.tv_nsec = 0;
    itime.it_interval.tv_sec = 1;
    itime.it_interval.tv_nsec = 0;

    sigaction(MY_SIGNAL, &act, NULL);

    timer_settime(timer_id, 0, &itime, NULL);

    printf("Press ENTER to Exit\n");
    while(getchar()!='\n'){}

    return EXIT_SUCCESS;
}

// ------------------------------------------- //
/*
Start
########## 51109 
########## 51107 
########## 50572 
########## 51863 
########## 50869 
########## 50496 
########## 53364 
#### Deadline exceeded ####
########## 50685 
########## 50224 
########## 51376 
########## 50342 
########## 53790 
#### Deadline exceeded ####
########## 53160 
####-- Restart required! --####
*/