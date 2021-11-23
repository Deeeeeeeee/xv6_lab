#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argc, char *argv[])
{
    char **new_argv = (char **)malloc((argc-1) * sizeof(char*));
    for (int i = 2; i < argc; ++i) {
        printf("---%s\n", argv[i]);
        strcpy(argv[i], new_argv[i-2]);
        printf("=====");
    }
    // 最后一个参数为 | 传过来的字符串，以 \n 为一行
    for (int i = 0; i < argc - 1; ++i) {
        printf("%s aa", new_argv[i]);
    }

    /** exec(argv[1], new_argv);  */

    free(new_argv);
    exit(0);
}
