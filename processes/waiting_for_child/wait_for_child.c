#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    pid_t process_id = fork();

    // Check if process creation worked successfully.
    if(process_id < 0) {
        perror("Process creation");
        return 1;
    }

    // Check which process is active
    if (process_id == 0) {
        printf("Hello from child, I'll execute ls now thank u bye\n");
        DIR *current_dir = opendir(".");
        list_files_from_dir(current_dir);
        closedir(current_dir);
        exit(0);
    } else {
        printf("Hello from parent, I need to wait for the child -_-\n");
        wait(NULL);
        printf("Child is done, finally...\n");
    }

    return 0;
}