#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "lab2.h"


/************************************************************\
 * get_arguments - returns the command line arguments not
 *                 including this file in an array with the
 *                 last element as null.  This is the format
 *                 that the execvp() function requires.
 * 
 * For example:  ./time ls -l
 * will return an array consisting of {"ls","-l", NULL}
 ************************************************************/
char** get_arguments(int argc, char** argv){
    int arg_length = argc;
    char**  cmd_args = NULL;

    if (arg_length > 0){
        cmd_args = (char**)malloc(sizeof(char*)*arg_length);
    }
    for(int i = 0; i < arg_length-1; i++){
        cmd_args[i] = argv[i+1];
    }
    cmd_args[arg_length-1] = NULL;
    return cmd_args;
}


int main(int argc, char** argv)
{
    pid_t pid;
    int status;
    char* command = NULL;
    char** command_args = NULL;
    char* ipc_ptr = NULL; // pointer to shared memory
    struct timeval start_time;
    struct timeval current_time;

    if (argc < 2){
        fprintf(stderr,"SYNOPSIS: %s <cmd> <cmd arguments>\n",argv[0]);
        return 1;
    }
    
    // TODO: call ipc_create to create shared memory region to which parent
    //       child have access.
    ipc_ptr = ipc_create(sizeof(start_time));
    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork failed!");
        return 2;
    }
    else if (pid == 0) { /*child process */
        gettimeofday(&start_time, NULL);

        memcpy(ipc_ptr,&start_time, sizeof(start_time));
        // TODO: get the list of arguments to be used in execvp() and 
        // execute execvp()
        command_args = get_arguments(argc, argv);
        execvp(command_args[0], command_args);

    }
    else { /* parent process */
        wait(NULL);
        
        gettimeofday(&current_time, NULL);

        memcpy(&start_time,ipc_ptr, sizeof(start_time));

        ipc_close;
        // NOTE: DO NOT ALTER THE LINE BELOW.
        printf("Elapsed time %.5f\n",elapsed_time(&start_time, &current_time));
    }
    
    return status;
}