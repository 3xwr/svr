/*
* Выполнил: Тетерин Дмитрий, 8373
* Задание: 2. «Вызов лифта»
* Дата выполнения: 09.03.2022
* Скрипт для компиляции и запуска программы:
* gcc -pthread 2_Teterin_8373.с 
* ./a.out
*/
// ------------------------------------------- // 
/*
 * Общее описание программы:
 * Данная программа реализует модель работы автомата, управляющим лифтом
 * при его вызове с некоторого этажа. Для функционирования модели используются сигналы.
 */
// ------------------------------------------- //
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define TOP 0
#define BOTTOM 1
#define THIS_FLOOR 2

#define Up 48
#define Down 49

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int state = THIS_FLOOR;

struct arg_struct
{
    sigset_t set;
};

void move(int direction)
{
    if (direction == Up)
    {
        int n = 3;
        for (int i = 1; i <= n; i++)
        {
            printf("*** GO UP\n");
            usleep(500000);
        }
        state = TOP;
        printf("state %d\n", state);
    }
    if (direction == Down)
    {
        int n = 3;
        for (int i = 1; i <= n; i++)
        {
            printf("*** GO DOWN\n");
            usleep(500000);
        }
        state = Down;
        printf("state %d\n", state);
    }
}

void lift_control(int signo, siginfo_t *info, void *nk)
{
    switch (state)
    {
    case THIS_FLOOR:
        if (signo == Up)
        {
            printf("This Floor, door is opened \n");
            sleep(1);
            move(Up);
            state = TOP;
        }
        if (signo == Down)
        {
            printf("This Floor, door is opened \n");
            sleep(1);
            move(Down);
            state = BOTTOM;
        }
        break;
    case TOP:
        if (signo == Up)
        {
            move(Down);
            printf("This Floor, door is opened \n");
            sleep(1);
            move(Up);
            state = TOP;
        }
        if (signo == Down)
        {
            move(Down);
            printf("This Floor, door is opened \n");
            sleep(1);
            move(Down);
            state = BOTTOM;
        }
        break;
    case BOTTOM:
        if (signo == Up)
        {
            move(Up);
            printf("This Floor, door is opened \n");
            sleep(1);
            move(Up);
            state = TOP;
        }
        if (signo == Down)
        {
            move(Up);
            printf("This Floor, door is opened \n");
            sleep(1);
            move(Down);
            state = BOTTOM;
        }
        break;
    }
    return;
}

void *push_button(void *args)
{
    struct arg_struct *set = (struct arg_struct *)args;
    char ch;
    struct sigaction act;
    act.sa_sigaction = &lift_control;
    act.sa_flags = SA_SIGINFO;
    act.sa_mask = set->set;
    sigaction(Up, &act, NULL);
    sigaction(Down, &act, NULL);

    pid_t pid = getpid();
    while (ch != 'q')
    {
        ch = getchar();
        switch (ch)
        {
        case 'u':
        {
            siginfo_t info;
            info.si_value.sival_int = 222;
            sigqueue(pid, Up, info.si_value);
            break;
        }
        case 'd':
        {
            siginfo_t info;
            info.si_value.sival_int = 223;
            sigqueue(pid, Down, info.si_value);
            break;
        }
        case 'q':
        {
            break;
        }
        };
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    sigset_t set;
    struct arg_struct args;
    args.set = set;
    pthread_t t;
    printf("Start\n");
    sigemptyset(&set);
    sigaddset(&set, Up);
    sigaddset(&set, Down);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);
    pthread_create(&t, NULL, &push_button, (void *)&args);
    pthread_join(t, NULL);
    printf("Finish\n");
    return EXIT_SUCCESS;
}
// ------------------------------------------- //
/*
Start
u
This Floor, door is opened 
*** GO UP
*** GO UP
*** GO UP
state 0
d
*** GO DOWN
*** GO DOWN
*** GO DOWN
state 49
This Floor, door is opened 
*** GO DOWN
*** GO DOWN
*** GO DOWN
state 49
u
*** GO UP
*** GO UP
*** GO UP
state 0
This Floor, door is opened 
*** GO UP
*** GO UP
*** GO UP
state 0
u
*** GO DOWN
*** GO DOWN
*** GO DOWN
state 49
This Floor, door is opened 
*** GO UP
*** GO UP
*** GO UP
state 0
q
Finish
*/