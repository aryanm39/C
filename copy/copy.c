#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd1, fd2;
    char str[1024];
    int bytesRead, bytesWritten;

    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return -1;
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening source file");
        return -1;
    }

    fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd2 == -1) {
        perror("Error opening destination file");
        close(fd1);
        return -1;
    }

    while ((bytesRead = read(fd1, str, sizeof(str))) > 0) {
        bytesWritten = write(fd2, str, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(fd1);
            close(fd2);
            return -1;
        }
    }

    close(fd1);
    close(fd2);
    printf("File has been copied successfully.\n");

    return 0;
}
