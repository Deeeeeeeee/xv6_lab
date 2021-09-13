#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

void prime(int fd);

int
main(int argc, char *argv[])
{
    int p[2];                           // 0 读 1 写
    pipe(p);

    int pid = fork();
    if (pid == 0) {                     // 子进程
        close(p[1]);
        prime(p[0]);
        close(p[0]);
    } else {                            // 父进程写数字
        close(p[0]);
        for (int i = 2; i <= 35; i++)   // 从2写到35
            write(p[1], &i, 4);
        close(p[1]);
        wait(0);
    }
    
    exit(0);
}

void prime(int fd) {
    int base;
    if(read(fd, &base, 4) == 0)
        exit(0);
    printf("prime %d\n", base);     // 读出来的第一个数一定是素数

    int p[2];
    pipe(p);                        // 0 读 1 写
    if (fork() == 0) {              // 子进程
        close(p[1]);
        prime(p[0]);
        close(p[0]);
    } else {
        close(p[0]);
        int n;
        while(read(fd, &n, 4)) {    // 继续读数据
            if (n % base != 0)
                write(p[1], &n, 4);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}

