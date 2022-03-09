#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>

#define TOP 0
#define BOTTOM 1
#define THIS_FLOOR 2

#define Up 48
#define Down 49

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

sigset_t set;

void catch_up(int signo) {
    printf("up signal with #%d\n", signo);
}

void catch_down(int signo) {
    printf("down signal with #%d\n", signo);
}

void catch(int signo, siginfo_t* info, void* context) {
    printf("signal with #%d\n", signo);
}

void *push_button(void *args)
{
    char ch;
    //sigaction init here . . .
    struct sigaction act;
    act.sa_sigaction = &catch;
    act.sa_flags = SA_SIGINFO;
    act.sa_mask = set;
    sigaction(Up, &act, NULL);
    while (ch != 'q')
    {
        ch = getchar();
        switch (ch)
        {
        case 'u':
        {
            siginfo_t info;
            info.si_value.sival_int = 222;
            sigqueue(0,Up, info.si_value);
            printf("PUSH UP BUTTON\n");
        break;
        }
        case 'd':
        {
            raise(Down);
            printf("PUSH DOWN BUTTON\n");
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

void lift_control(int signo, siginfo_t *info, void *nk)
{
    int state;
    //TODO: REPLACE WITH REAL LIFT STATE
    switch (state)
    {
    case THIS_FLOOR:
        if (signo == Up)
        {
            //handle
        }
        if (signo == Down)
        {
            //handle
        }
        break;
    case TOP:
        //handle
        break;
    case BOTTOM:
        //handle
        break;
    }
    return;
}

int main(int argc, char *argv[])
{
    pthread_t t;
    printf("Start\n");
    sigemptyset(&set);
    sigaddset(&set, Up);
    sigaddset(&set, Down);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create(&t, NULL, &push_button, NULL);
    pthread_join(t, NULL);
    printf("Finish\n");
    return EXIT_SUCCESS;
}