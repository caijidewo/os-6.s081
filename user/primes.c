#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    const int size = 35;
    int primes[size];
    primes[0] = size - 1;
    for(int i = 1; i < size; i++) {
        primes[i] = i + 1;
    }
    write(p[1], primes, (primes[0] + 1) * 4);
    while(primes[0] != 0) {
        if(fork() == 0) {
            int n = read(p[0], primes, (primes[0] + 1) * 4);
            printf("prime %d\n", primes[1]);
            int temp[n / 4];
            int cnt = 1;
            for(int i = 2; i < n / 4; i++) {
                if (primes[i] % primes[1] != 0) {
                    temp[cnt++] = primes[i];
                }
            }
            temp[0] = cnt - 1;

            write(p[1], temp, (temp[0] + 1) * 4);
            close(p[1]);
            close(p[0]);
            exit(0);
            
        } else{
            wait(0);
            read(p[0], primes, size * 4);
            write(p[1], primes, (primes[0] + 1) * 4);
        }
    }
    close(p[0]);
    close(p[1]);
    exit(0);
}
