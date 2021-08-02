#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: xargs command para... \n");
        exit(0);
    }
    const int LINELENTH = 10;

    char *para[MAXARG];
    char line[LINELENTH];
    for (int i = 1; i < argc; i++)
        para[i - 1] = argv[i];
    int cnt = 0;
    while (gets(line, LINELENTH) && strlen(line) != 0)
    {
        cnt++;
        para[argc - 1] = line;
        para[argc] = 0;

        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
            
        if (fork() == 0)
        {
            exec(para[0], para);
            fprintf(2, "error: line %d exec failed\n", cnt);
        }
        else
        {
            wait(0);
        }
    }
    exit(0);
}
