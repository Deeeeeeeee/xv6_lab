#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"
#include "../kernel/fs.h"

void find(char *path, char *target, int degree);
char* fmtname(char *path);

int main(int argc, char *argv[])
{
    find(argv[1], argv[2], 0);
    exit(0);
}

void find(char *path, char *target, int degree)
{
    char buf[512], *p, *filename;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
        // 如果是文件，则判断是否目标文件
        case T_FILE:
            filename = fmtname(path);
            if (strcmp(filename, target) == 0)
                printf("%s\n", path);
            break;
        // 如果是目录，则遍历目录，递归它
        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                printf("ls: path too long\n");
                break;
            }
            filename = fmtname(path);
            if (degree && (!strcmp(filename, ".") || !strcmp(filename, ".."))) break;
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
                filename = fmtname(buf);
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf, target, degree+1);
            }
            break;
    }
    close(fd);
}

// 找到path的文件名
char* fmtname(char *path)
{
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    return p;
}

