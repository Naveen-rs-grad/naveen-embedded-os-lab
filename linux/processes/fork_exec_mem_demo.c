/*
We have two operations:
- fork() creates a new process with an initially equivalent memory state.
- exec() replaces the program running inside an existing process.

Important: The child does not continue executing the C instructions after execlp() succeeds. The OS loads the new executable and prepares its initial execution state.

Compile: 
gcc -Wall -Wextra -g new_program.c -o new_program
gcc -Wall -Wextra -g exec_demo.c -o exec_demo
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global = 100;

int main(void)
{
    int local = 200;

    printf("PARENT: PID=%d\n", getpid());
    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("CHILD BEFORE EXEC: PID=%d\n", getpid());
        printf("global=%d, local=%d\n", global, local);
        fflush(stdout);

        execl("./new_program",
              "new_program",
              "hello",
              (char *)NULL);

        perror("exec failed");
        return 1;
    }

    waitpid(pid, NULL, 0);
    printf("PARENT: Child has finished\n");

    return 0;
}
