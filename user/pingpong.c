#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    char byte[2];
    if(fork() == 0) {
        int n = read(p[0], byte, 1);
        close(p[0]);
        if(n == 1 && byte[0] == '1'){
            fprintf(1, "%d: received ping\n", getpid());
        }else{
            fprintf(2, "child process read error\n");
            exit(1);
        }
        write(p[1], "0", 1);
        close(p[1]);
    } else{
        write(p[1], "1", 1);
        close(p[1]);
        wait((int*) 0);
        int n = read(p[0], byte, 1);
        if(n == 1 && byte[0] ==  '0') {
            fprintf(1, "%d: received pong\n", getpid());
        } else{
            fprintf(2, "parent process read error\n");
            exit(1);
        }
        close(p[0]);
    }
    exit(0);
}
