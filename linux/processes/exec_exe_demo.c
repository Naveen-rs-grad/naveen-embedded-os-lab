
/*
Used by fork_exe_mem_demo.c
*/

#include <stdio.h>
#include <unistd.h>

int global = 999;

int main(int argc, char *argv[])
{
    int local = 888;

    printf("NEW PROGRAM STARTED\n");
    printf("PID    = %d\n", getpid());
    printf("global = %d\n", global);
    printf("local  = %d\n", local);

    if (argc > 1) {
        printf("Argument received: %s\n", argv[1]);
    }

    return 0;
}
