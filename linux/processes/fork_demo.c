#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global = 100;

int main(void)
{
    int local = 200;

    printf("Before fork: PID=%d\n", getpid());
    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        global = 500;
        local = 600;

        printf("CHILD: PID=%d, global=%d, local=%d\n",
               getpid(), global, local);
    } else {
        waitpid(pid, NULL, 0);

        printf("PARENT: PID=%d, global=%d, local=%d\n",
               getpid(), global, local);
    }

    return 0;
}
