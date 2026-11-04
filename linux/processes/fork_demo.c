#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global = 100;

int main(void) //this is a parent process
{
    int local = 200;

    printf("Before fork: PID=%d\n", getpid()); //getpid() - It returns the process ID assigned by Linux
    fflush(stdout);

    pid_t pid = fork(); //The running process requests the operating system to create a child process.
    //The child inherits a copy of the parent's virtual address-space contents.
    //Both processes resume execution immediately after the fork() call.
    //fork() duplicates the current execution state, not just the program code.
    //fork() doesn't mean the child automatically runs before or after the parent. The OS scheduler determines their execution order.

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { //for child process this is true and for parent it is false
        global = 500;
        local = 600;

        printf("CHILD: PID=%d, global=%d, local=%d\n",
               getpid(), global, local);
    } else { //parent comes here
        waitpid(pid, NULL, 0); //Parent, wait until this particular child process terminates.

        printf("PARENT: PID=%d, global=%d, local=%d\n",
               getpid(), global, local);
    }

    return 0;
}


//compilation command: gcc -Wall -Wextra -g fork_demo.c -o fork_demo