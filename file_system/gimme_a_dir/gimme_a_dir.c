#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    //* =============================== METHOD 1 =============================== *//
    // ! This code doesn't check if the folder is alreay exitent. If it is, 
    // ! then the compiler will throw an error.
    // Create a subsirectory
    int status = system("mkdir new_folder");

    if (status == 0) {
        printf("The command executed successfully!");
    } else {
        perror("The command failed");
        return 1;
    }
    
    //* =============================== METHOD 2 =============================== *//
    mkdir("new_folder_but_cooler", S_IRWXU);
    return 0;
}