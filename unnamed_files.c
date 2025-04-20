#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    char str[20], str1[20], str2[] = "Hello";
    int fd[2];
    
    pipe(fd);
    
    if (fork() == 0) {
        close(fd[1]);  // Close write end in child
        while (1) {
            read(fd[0], str1, 20);
            printf("Child received: %s\n", str1);
        }
    } else {
        close(fd[0]);  // Close read end in parent
        while (1) {
            write(fd[1], str2, strlen(str2) + 1);
            sleep(1);
        }
    }

    return 0;
}
