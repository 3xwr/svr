#include <stdio.h>
#include <stdbool.h>
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

struct arg_struct{
    sigset_t set;
};

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
    struct arg_struct *set = (struct arg_struct*)args;
    char ch;
    //sigaction init here . . .
    struct sigaction act;
    struct sigaction actdown;
    act.sa_sigaction = &catch;
    act.sa_flags = SA_SIGINFO;
    act.sa_mask = set->set;
    sigaction(Up, &act, NULL);
    sigprocmask(SIG_UNBLOCK, &set->set, NULL);
    actdown.sa_handler = &catch_down;
    actdown.sa_flags = 0;
    actdown.sa_mask = set->set;
    sigaction(Down, &actdown, NULL);
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
            printf("%d",errno);
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
    sigset_t set;
    struct arg_struct args;
    args.set = set;
    pthread_t t;
    printf("Start\n");
    sigemptyset(&set);
    sigaddset(&set, Up);
    sigaddset(&set, Down);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);
    pthread_create(&t, NULL, &push_button, (void*)&args);
    pthread_join(t, NULL);
    printf("Finish\n");
    return EXIT_SUCCESS;
}