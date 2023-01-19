#include <unistd.h>

int main(int ac, char **av,char **env) {
    (void)ac;
    (void)av;
    char *argv[] = {"ls","-la", NULL};
    char *envp[] = {NULL};
    execve("/bin/ls", argv, envp);
    return 0;
}
