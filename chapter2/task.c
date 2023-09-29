#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd[3];
    const char *filename = "hello.txt";
    const char *copy_file = "cpy_hello.txt";
    char buffer[100];
    ssize_t sz;
    
    // Open the file for reading
    fd[0] = open(filename, O_RDONLY);

    printf("fd %d\n", fd[0]);
    if (fd[0] == -1) {
        // printf("Error Number % d\n", errno);
        // printf("Error Message %d\n", errno);
        int error = errno;
        if (error == 2){
            printf("No such file or directory. ");
        }
        //perror("Error opening file");
        return 1;
    }

    // Read data from the file
    ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer));

    if (bytes_read == -1) {
    perror("Error reading from file");
    close(fd[0]);  // Close the file before returning on error
    return 1;
    }

    fd[1] = open(copy_file, O_APPEND | O_RDWR);
    printf("Error Message %d\n", errno);
    printf("Copy  file descriptor: %d \n", fd[1]);
    
    // Writing in console without Printf
    sz = write(fd[1], buffer, bytes_read);
    write(1, "writing without printf: \n", sizeof("writing without printf: \n"));
    write(1, buffer, bytes_read);


    // Close the file
    if (close(fd[0]) == -1) {
        perror("Error closing file");
        return 1;
    }

    close(fd[0]);
    close(fd[1]);

    // Print the read data
    printf("Read %zd bytes: %.*s\n", bytes_read, (int)bytes_read, buffer);

    return 0;
    }


//Link: https://medium.com/@joshuaudayagiri/linux-system-calls-read-a9ce7ed33827#:~:text=The%20read%20function%20is%20a%20system%20call%20in%20Linux%20used,pipes%2C%20and%20other%20input%20sources.
//https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
//errno_values: https://www.geeksforgeeks.org/error-handling-in-c/