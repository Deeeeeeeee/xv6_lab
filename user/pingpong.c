#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int
main(int argc, char *argv[])
{
    int ppfd[2];         // 父进程 0 读，1 写
    int cpfd[2];         // 子进程 0 读，1 写
    char buf[1];

    pipe(ppfd);
    pipe(cpfd);
    if (fork() == 0) {  // 子进程
        close(ppfd[0]);
        close(cpfd[1]);

        read(cpfd[0], &buf, 1);
        int pid = getpid();
        printf("%d: received ping\n", pid);
        write(ppfd[1], "o", 1);

        close(ppfd[1]);
        close(cpfd[0]);
        exit(0);
    } else {
        close(ppfd[1]);
        close(cpfd[0]);

        write(cpfd[1], "i", 1);
        read(ppfd[0], &buf, 1);
        int pid = getpid();
        printf("%d: received pong\n", pid);

        close(ppfd[0]);
        close(cpfd[1]);
    }
    
    exit(0);
}
