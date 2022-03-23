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
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define DEADLINE 52000
#define SOFT_DT 54000
#define DEADLINE_EXCEEDED 48

void doControl() {
    int time;
    int dt=0, x=1;
    dt = rand() % 4000;
    time = 50000 + dt;
    printf("########## %d \n", time);
    int changeX = rand() % 10;
    if (changeX == 8) {
        x = 0;
    }
    if (x==0) while(1);

    usleep(time);
}

void deadlineHandler() {
    printf("#### Deadline exceeded ####\n");
}

void alarmHandler() {
    printf("####-- Restart required! --####\n");
    pid_t pid = getpid();
    siginfo_t info;
    info.si_value.sival_int = 222;
    sigqueue(pid, SIGUSR1, info.si_value);
}

void *doStuff() {
    pid_t pid = getpid();
    while (1)
    {
        alarm(0);
        int time = SOFT_DT/10000;
        alarm(time);

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        doControl();
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        int delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        if (delta_us > DEADLINE) {
            siginfo_t info;
            info.si_value.sival_int = 222;
            sigqueue(pid, DEADLINE_EXCEEDED, info.si_value);
        }
        sleep(3);
    }
}

int main(int argc, char *argv[])
{
    printf("Start\n");
    srand(time(NULL));
    
    sigset_t set;
    pthread_t t;

    sigemptyset(&set);
    sigaddset(&set,DEADLINE_EXCEEDED);
    sigaddset(&set, SIGALRM);
    sigaddset(&set, SIGUSR1);

    struct sigaction act;
    act.sa_handler = &deadlineHandler;
    act.sa_flags = SA_SIGINFO;
    act.sa_mask = set;
    sigaction(DEADLINE_EXCEEDED, &act, NULL);

    struct sigaction act_alarm;
    act_alarm.sa_handler = &alarmHandler;
    act_alarm.sa_flags = SA_SIGINFO;
    sigaction(SIGALRM, &act_alarm, NULL);

    struct sigaction act_usr1;
    act_usr1.sa_handler = &exit;
    act_usr1.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act_usr1, NULL);

    pthread_sigmask(SIG_UNBLOCK, &set, NULL);
    pthread_create(&t, NULL, &doStuff, NULL);
    pthread_join(t, NULL);
    printf("Finish\n");
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