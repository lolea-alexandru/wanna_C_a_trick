#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    // Create the process
    pid_t process_id = fork();

    // Check if child process was created succesfully
    if(process_id < 0) {
        perror("Creating the child process failed");
        exit(1); // 
    }

    // Check in which process the program is currently
    if (process_id == 0) {
        printf("Hello from the child!\n");
    } else {
        printf("Hello from the parent! Child id is: %d\n", process_id);
    }

    return 0;
}