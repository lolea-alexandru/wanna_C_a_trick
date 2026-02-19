#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct dirent d_entry;


void list_files_from_dir(DIR *directory) {
    d_entry *entry = readdir(directory);
    while(entry) {
        printf("Entry: %s\n", entry->d_name);
        entry = readdir(directory);
    }

    return;
}


int main() {
    //* =============================== METHOD 1 =============================== *//
    // ! This code doesn't check if the folder is alreay exitent. If it is, 
    // ! then the compiler will throw an error.
    int status = system("ls");

    if (status == 0) {
        printf("The command executed successfully!");
    } else {
        perror("The command failed");
        return 1;
    }

    //* =============================== METHOD 2 =============================== *//
    DIR *current_dir = opendir(".");

    // Check if opening the directory failed
    if (current_dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Check all the directories
    list_files_from_dir(current_dir);

    closedir(current_dir);
    
    return 0;
}
