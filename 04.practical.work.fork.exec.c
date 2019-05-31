#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
    int p1, p2;
    printf("I am parent before fork()\n");
    p1 = fork();
    if(p1 == 0){
        printf("I am the first child\nRunning ps -ef\n ");
        char* args[] = {"/bin/ps", "-ef", NULL};
        if(execvp("/bin/ps", args) < 0){
            printf("Failed\n");
        }
    }
    
        waitpid(p1, NULL, 0);
        printf("I am parent after fork, child is %d\nContinue to create another child\n", p1);
        p2 = fork();
        if(p2 == 0){
            printf("I am the second child\nRunning free -h\n");
            char* args[] = {"/usr/bin/free", "-h", NULL};
            if(execvp("/usr/bin/free", args) < 0){
                printf("Failed\n");
            }
        }
        else {
            printf("I am parent after 2 forks, second child is %d\n", p2);
            waitpid(p2, NULL, 0);
        }
    return 0;
}
