#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// a) What is the role of pipe c?
//* Pipe c acts as a guard that prevents the child process to read what he wrote in the pipe a

// b) What will be displayed in the console?
//* As x is not changing its value and only val is incrementing for each pass in the for loop of the parent,
//* the result will be:
//* 0
//* 3
//* in any order, depending on who finishes first (the child or the parent(before wait(NULL)) )

// c) What will happen if lines 11 and 12 are swapped?
//* Undefined behavior, as the child will read from itself and values of val will be lost between communications

// d) How is the process execution if line 7 is moved between lines 14-15 and line 19 is moved between lines 26-27?
//* Undefined behavior, as both files denoted by those descriptors will be opened in both child and parent,
//* potentially leading to deadlocks and unintented reads/writes

// e) What happens if line 17 is eliminated?
//* If line 17 is eliminated, the child process will continue to execute the parent code, closing the already closed file descriptors AGAIN,
//* close resulting in error. All calls to read, write will result in error, being that the file descriptors are closed.s

int main(int argc, char **argv)
{
    int a[2], b[2], c[2], i;
    // x acts as a guard variable for helping c gatekeep the child from reading what he wrote in a
    char val = 0, x = 0;

    pipe(a);
    pipe(b);
    pipe(c);

    if (fork() == 0)
    {
        // in child
        // the child writes in b, reads from c and can read/write from a
        close(b[0]);
        close(c[1]);
        for (i = 0; i < 3; i++)
        {
            write(a[1], &val, 1);
            write(b[1], &x, 1);
            read(c[0], &x, 1); // PREVENTS THE CHILD FROM READING WHAT HE WROTE IN pipe a
            read(a[0], &val, 1);
        }

        printf("%d\n", val);
        close(a[0]);
        close(a[1]);
        close(b[1]);
        close(c[0]);
        exit(0);
    }

    // in parent
    // the parent reads from b, writes to c and can read/write from a
    close(b[1]);
    close(c[0]);
    for (i = 0; i < 3; i++)
    {
        read(b[0], &x, 1);
        read(a[0], &val, 1);
        val++;
        write(a[1], &val, 1);
        write(c[1], &x, 1);
    }

    close(a[0]);
    close(a[1]);
    close(b[0]);
    close(c[1]);
    printf("%d\n", x);

    wait(NULL);
    return 0;
}