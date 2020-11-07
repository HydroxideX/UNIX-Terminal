#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <signal.h>
#include "logger.h"
#include "stringProcessor.h"

//function to read a single line from console
char* readLine(){
    printf("Enter your Command: ");
    char *buffer;
    size_t bufsize = 1;
    size_t characters;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL) {
        perror("Unable to allocate buffer");
        exit(1);
    }
    characters = getline(&buffer,&bufsize,stdin);
    buffer[(int)characters - 1] = ' ';
    return buffer;
}

void invoke(char* arguments[], int dontwait){
    //fork the child with the new process
    pid_t pid = fork();

    if(pid<0){
        //error in forking
        fprintf(stderr, "Fork Failed");
        exit(1);
    } else if(pid == 0){
        //child executes here after forking
        execvp(arguments[0],arguments);
        exit(0);
    } else {
        //parent waits for the child to finish if not supplied with & at the end
        if(!dontwait)
        {
            wait(NULL);
        }
        dontwait = 1;
    }
}

int main() {
    int end = 0;
    while(!end) {
        //read command
        char* command = readLine();
        //count number of arguments in a command
        int wordsCount = countWords(command);
        char* arguments[wordsCount +1];
        //break the command into arguments
        breakStringIntoArgs(arguments, command);
        //check if the program recieved a termination signal so it goes to the logger
        signal(SIGCHLD, log);
        //check if user typed exit
        if(checkForExit(arguments)){
            end = 1;
            continue;
        }
        //set the last element of arguments to null
        arguments[wordsCount] = NULL;
        //set dont wait to 1 if the user inputted & at the end of the command and remove & from arguments
        int dontwait = 0;
        if(wordsCount > 1 && arguments[wordsCount-1][0] == '&' && arguments[wordsCount-1][1] =='\0'){
            dontwait = 1;
            free(arguments[wordsCount-1]);
            arguments[wordsCount-1] = NULL;
        }

        invoke(arguments, dontwait);
        //free allocated space
        for(int i = 0;i < wordsCount;i++){
            if(arguments[i] != NULL) free(arguments[i]);
        }
    }
    return 0;
}