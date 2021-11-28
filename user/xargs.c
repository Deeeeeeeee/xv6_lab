#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/param.h"
#include "../user/user.h"

int readline(char *buf);

int main(int argc, char *argv[])
{
    char *buf = malloc(MAXARG);
    int pid, child_status;
    char **new_argv = (char **)malloc((argc) * sizeof(char*));
    // 开头要多一个，结尾要为 null
    for (int i = 1; i < argc; ++i) {
        new_argv[i-1] = (char *)malloc(strlen(argv[i]));
        strcpy(new_argv[i-1], argv[i]);
    }
    // 最后一个参数为 | 传过来的字符串，以 \n 为一行
    /** for (int i = 0; i < argc - 2; ++i) { */
    /**     printf("%s aa", new_argv[i]); */
    /** } */

    for (int i = 0; i <= argc; ++i) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    while (readline(buf) == 0) {

    }

    pid = fork();
    if (pid == 0) {
        /** for (int i = 0; i < argc - 1; ++i) { */
        /**     printf("%s ", new_argv[i]); */
        /** } */
        /** printf("\n"); */

        /** for (int i = 0; i <= argc; ++i) { */
        /**     printf("%s ", argv[i]); */
        /** } */
        /** printf("\n"); */

        exec(new_argv[0], new_argv);
        /** exec("echo", argv+1); */
        free(new_argv);
        exit(0);
    } else {
        wait(&child_status);
    }

    free(new_argv);
    exit(0);
}

int readline(char *buf) {
    char *p = buf;
    while (read(0, p, 1) != 0) {
        if (*p == '\n' || *p == '\0') {
            *p = '\0';
            return 0;
        }
        p++;
    }
    return -1;
}

char **split(char *buf, char **dest) {
    int cnt = 0;
    char *p = buf;
    while (*p != ' ')

  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}
