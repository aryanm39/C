#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    char ch;
    int position = 99; // 100th char

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    printf("Reading every 100th character:\n");
    while (lseek(fd, position, SEEK_SET) >= 0 && read(fd, &ch, 1) == 1) {
        printf("%c", ch);
        position += 100;
    }

    printf("\n");
    close(fd);
    return 0;
}
