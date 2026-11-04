/*
exec() does not create another process. It replaces the child process's program while retaining its PID.

Compilation command: gcc -Wall -Wextra -g exec_demo.c -o exec_demo


Parent program
      |
      | fork()
      |
      +-----------------------+
      |                       |
      v                       v
 Parent process          Child process
 (original program)      (original program)
      |                       |
      |                       | execlp("ls",...)
      |                       v
      |                    ls program
      |                       |
      |                       v
      |                     exits
      |                       |
      v                       |
   waitpid() <----------------+
      |
      v
 Parent continues
*/

#include <stdio.h>
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
        printf("CHILD: PID=%d, before exec\n", getpid());
        fflush(stdout);

        //execlp(file, arg0, arg1, ..., NULL);
        //ls - is an executable, NULL end of argument
        //exec + lp, l - list, p - path
        execlp("ls", "ls", "-l", NULL); //execlp() is a POSIX function used to execute another program within the current process.


        perror("exec failed");
        return 1;
    }
    else {
        waitpid(pid, NULL, 0);
        printf("PARENT: Child finished\n");
    }

    return 0;
}
