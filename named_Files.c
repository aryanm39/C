#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <fifo_name>\n", argv[0]);
        return 1;
    }

    // Create a named pipe (FIFO)
    mkfifo(argv[1], 0666);

    // Open the FIFO for writing
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO");
        return 1;
    }

    char str[] = "Hello, FIFO!";
    
    while (1) {
        write(fd, str, strlen(str) + 1); // Send message
        sleep(1); // Delay for readability
    }

    close(fd);
    return 0;
}
