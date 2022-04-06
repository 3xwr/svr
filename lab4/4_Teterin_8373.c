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
#include <sys/time.h>

#define DEADLINE 52000
#define SOFT_DT 54000
#define MY_SIGNAL 48

#define UNUSED(x) (void)(x)

struct timeval t1_prev;
struct timeval t2_prev;
struct timeval t3_prev;


void doControl_1() {
    if (t1_prev.tv_sec == -1) {
        gettimeofday(&t1_prev, NULL);
    }
    long long prev_ms = t1_prev.tv_sec*1000LL + t1_prev.tv_usec/1000;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long curr_ms = current_time.tv_sec*1000LL + current_time.tv_usec/1000;
    long long diff = curr_ms-prev_ms;
    if (diff == 0) {
        printf("Procedure #1 call time: %lld ms, called for the first time\n", curr_ms);
    } else {
        printf("Procedure #1 call time: %lld ms, time since last call: %lld ms\n", curr_ms, diff);
    }

    gettimeofday(&t1_prev, NULL);
}

void alarmHandler() {
}

void *doStuff() {
}

int main(int argc, char *argv[])
{
    t1_prev.tv_sec = -1;
    t2_prev.tv_sec = -1;
    t3_prev.tv_sec = -1;
    
    struct sigevent event;
    struct itimerspec itime;
    timer_t timer_id;

    struct sigaction act;

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = doControl_1;

    sigemptyset(&act.sa_mask);

    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = MY_SIGNAL;

    int ret = timer_create(CLOCK_REALTIME, &event, &timer_id);

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