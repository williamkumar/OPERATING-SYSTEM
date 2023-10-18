#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // File creation
    int fd = creat("example.txt", 0644);  // Create a new file or truncate if it exists
    if (fd == -1) {
        perror("Error creating the file");
        return 1;
    }
    
    // File opening
    fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Writing to the file
    char data[] = "This is some data written to the file using UNIX system calls.";
    int bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to the file");
        close(fd);
        return 1;
    }

    // Reading from the file
    char buffer[100];
    lseek(fd, 0, SEEK_SET);  // Move the file pointer to the beginning
    int bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading from the file");
        close(fd);
        return 1;
    }
    
    // Display the read data
    buffer[bytes_read] = '\0';
    printf("Read data from the file: %s\n", buffer);

    // File closing
    close(fd);
    
    return 0;
}

