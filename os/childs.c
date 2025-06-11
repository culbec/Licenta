#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>

/********* PROCESS HIERARCHY **********
        ---- C1     ---- C11  ---- C111
                    ---- C12
     P  ---- C2     ---- C21

        ---- C3
    
*/

void f1() {
    int i;
    for (i = 0; i < 3; i++) {
        if (fork() == 0) {}
        // wait is done by both parent and child
        // the child doesn't end, so it will continue without waiting, because it cannot wait for anyone
        // the parent will wait for its child to finish
        // results linear hierarchy
        printf("[i=%d] I'm process %d | Parent: %d\n", i, getpid(), getppid());
        wait(0);
    }
}

/********* PROCESS HIERARCHY **********
       
       P  ---- C1     ---- C11  ---- C111

*/

void f2() {
    int i, p = 0;
    for (i = 0; i < 3; i++) {
        if (p == 0) {
            p = fork(); 
	    // p == 0 when the executed process is a child;
            // only children will be able to create processes
        }
        // wait is done by both parent and child
        // the child doesn't end, so it will continue without waiting, because it cannot wait for anyone
        // the parent will wait for its child to finish
        printf("[i=%d] I'm process %d | Parent: %d\n", i, getpid(), getppid());
        wait(0);
    }
}

int main() {
    //printf("##### f1 #####\n");
    //f1();
    //printf("\n");

    printf("##### f2 #####\n");
    f2();
    printf("\n");

    return 0;
}
