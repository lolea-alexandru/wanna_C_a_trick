/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) if command did not include &, parent will invoke wait()
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE_LGTH 90

int main(void) {
    char *args[MAX_LINE_LGTH/2 + 1];
    int should_run = 1;

    while (should_run) {
        memset(args, 0, (MAX_LINE_LGTH/2 + 1) * sizeof(char*));
        char *line = readline("osh>");

        // Check if an EOF has been provided
        if (line == NULL) {
            free(line);
            should_run = 0;
            continue;
        }

        int arg_index = 0;
        bool command_in_foreground = false;

        // Split the line into individual tokens
        char* token = strtok(line, " ");
        while(token != NULL) {
            // Check if the terminal character "&" has been found
            if(strcmp(token, "&") == 0) {
                command_in_foreground = true;
                break;
            }

            args[arg_index++] = token;
            token = strtok(NULL, " "); 
        }

        for(int i=0; i<arg_index; i++) {
            printf("%s\n", args[i]);
        }
        

        // Check if the command "exit" has been used
        //! The "exit" command can't be called with the execvp() because it's not a program, but a default Shell command.
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }

        // Check if the command "cd" has been used
        //! The "cd" command can't be called with the execvp() because it's not a program, but a default Shell command.
        if (strcmp(args[0], "cd") == 0) {
            chdir(args[1]);
            continue;
        }
        
        // Start a new process that will execute the command    
        pid_t child_process_id = fork();
        
        // Child process => execute command
        if(child_process_id == 0) {
            if (execvp(args[0], args) < 0) {
                perror("Command exe error");
                exit(1);
            };
        } else {
            if(!command_in_foreground) {
                waitpid(child_process_id, NULL, 0);
            }
        }
    }

    return 0;
}