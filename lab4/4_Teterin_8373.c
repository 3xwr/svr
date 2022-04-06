/*
* Выполнил: Тетерин Дмитрий, 8373
* Задание: 4. «Модель циклической системы управления »
* Дата выполнения: 06.04.2022
* Скрипт для компиляции и запуска программы:
* gcc 4_Teterin_8373.с -lrt
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 * Данная программа реализует модель циклической системы управления с помощью таймеров и сигналов.
 */
// ------------------------------------------- //
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#define MY_SIGNAL 48
#define MY_SIGNAL2 49
#define MY_SIGNAL3 50

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

void doControl_2() {
    if (t2_prev.tv_sec == -1) {
        gettimeofday(&t2_prev, NULL);
    }
    long long prev_ms = t2_prev.tv_sec*1000LL + t2_prev.tv_usec/1000;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long curr_ms = current_time.tv_sec*1000LL + current_time.tv_usec/1000;
    long long diff = curr_ms-prev_ms;
    if (diff == 0) {
        printf("Procedure #2 call time: %lld ms, called for the first time\n", curr_ms);
    } else {
        printf("Procedure #2 call time: %lld ms, time since last call: %lld ms\n", curr_ms, diff);
    }

    gettimeofday(&t2_prev, NULL);
}

void doControl_3() {
    if (t3_prev.tv_sec == -1) {
        gettimeofday(&t3_prev, NULL);
    }
    long long prev_ms = t3_prev.tv_sec*1000LL + t3_prev.tv_usec/1000;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long curr_ms = current_time.tv_sec*1000LL + current_time.tv_usec/1000;
    long long diff = curr_ms-prev_ms;
    if (diff == 0) {
        printf("Procedure #3 call time: %lld ms, called for the first time\n", curr_ms);
    } else {
        printf("Procedure #3 call time: %lld ms, time since last call: %lld ms\n", curr_ms, diff);
    }

    gettimeofday(&t3_prev, NULL);
}

int main(int argc, char *argv[])
{
    printf("Start\n");
    t1_prev.tv_sec = -1;
    t2_prev.tv_sec = -1;
    t3_prev.tv_sec = -1;
    
    struct sigevent event;
    struct sigevent event2;
    struct sigevent event3;

    struct itimerspec itime;
    struct itimerspec itime2;
    struct itimerspec itime3;

    timer_t timer_id;
    timer_t timer_id2;
    timer_t timer_id3;

    struct sigaction act;
    struct sigaction act2;
    struct sigaction act3;

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = doControl_1;

    act2.sa_flags = SA_SIGINFO;
    act2.sa_sigaction = doControl_2;

    act3.sa_flags = SA_SIGINFO;
    act3.sa_sigaction = doControl_3;

    sigemptyset(&act.sa_mask);
    sigemptyset(&act2.sa_mask);
    sigemptyset(&act3.sa_mask);

    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = MY_SIGNAL;

    event2.sigev_notify = SIGEV_SIGNAL;
    event2.sigev_signo = MY_SIGNAL2;

    event3.sigev_notify = SIGEV_SIGNAL;
    event3.sigev_signo = MY_SIGNAL3;

    timer_create(CLOCK_REALTIME, &event, &timer_id);
    timer_create(CLOCK_REALTIME, &event2, &timer_id2);
    timer_create(CLOCK_REALTIME, &event3, &timer_id3);
    

    itime.it_value.tv_sec = 0;
    itime.it_value.tv_nsec = 500000000;
    itime.it_interval.tv_sec = 0;
    itime.it_interval.tv_nsec = 500000000;

    itime2.it_value.tv_sec = 0;
    itime2.it_value.tv_nsec = 750000000;
    itime2.it_interval.tv_sec = 0;
    itime2.it_interval.tv_nsec = 750000000;

    itime3.it_value.tv_sec = 1;
    itime3.it_value.tv_nsec = 0;
    itime3.it_interval.tv_sec = 1;
    itime3.it_interval.tv_nsec = 0;

    sigaction(MY_SIGNAL, &act, NULL);
    sigaction(MY_SIGNAL2, &act2, NULL);
    sigaction(MY_SIGNAL3, &act3, NULL);

    timer_settime(timer_id, 0, &itime, NULL);
    timer_settime(timer_id2, 0, &itime2, NULL);
    timer_settime(timer_id3, 0, &itime3, NULL);

    while(1){}

    printf("Finish\n");
    return EXIT_SUCCESS;
}

// ------------------------------------------- //
/*
Start
Procedure #1 call time: 1649266022619 ms, called for the first time
Procedure #2 call time: 1649266022869 ms, called for the first time
Procedure #3 call time: 1649266023119 ms, called for the first time
Procedure #1 call time: 1649266023119 ms, time since last call: 500 ms
Procedure #2 call time: 1649266023619 ms, time since last call: 750 ms
Procedure #1 call time: 1649266023619 ms, time since last call: 500 ms
Procedure #3 call time: 1649266024119 ms, time since last call: 1000 ms
Procedure #1 call time: 1649266024119 ms, time since last call: 500 ms
Procedure #2 call time: 1649266024369 ms, time since last call: 750 ms
Procedure #1 call time: 1649266024619 ms, time since last call: 500 ms
Procedure #3 call time: 1649266025119 ms, time since last call: 1000 ms
Procedure #2 call time: 1649266025119 ms, time since last call: 750 ms
Procedure #1 call time: 1649266025119 ms, time since last call: 500 ms
Procedure #1 call time: 1649266025619 ms, time since last call: 500 ms
Procedure #2 call time: 1649266025869 ms, time since last call: 750 ms
Procedure #3 call time: 1649266026119 ms, time since last call: 1000 ms
Procedure #1 call time: 1649266026119 ms, time since last call: 500 ms
Procedure #2 call time: 1649266026619 ms, time since last call: 750 ms
Procedure #1 call time: 1649266026619 ms, time since last call: 500 ms
*/