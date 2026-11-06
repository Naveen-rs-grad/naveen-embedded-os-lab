//Compile:  gcc -Wall -Wextra -g exit_demo.c -o exit_demo

/*
Output:
PARENT: Waiting for child...
CHILD: PID=5046
CHILD: Performing some work...
PARENT: Child exited with status 5
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("CHILD: PID=%d\n", getpid());
        printf("CHILD: Performing some work...\n");

        exit(5);
    }
    else {
        int status;

        printf("PARENT: Waiting for child...\n");
        fflush(stdout);

        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }

        //The status returned by the child process will be encoded , so we linux provides macro to extract info
        if (WIFEXITED(status)) { //checks if the child process is exited?
            printf("PARENT: Child exited with status %d\n",
                   WEXITSTATUS(status)); //if exited, what is the exit code?
        }
    }

    return 0;
}
