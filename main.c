#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <signal.h>
#include "logger.h"
#include "stringProcessor.h"

char* readLine(){
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

int main() {
    int end = 0;
    while(!end) {
        char* command = readLine();
        int wordsCount = countWords(command);
        char* arguments[wordsCount +1];
        breakStringIntoArgs(arguments, command);
        signal(SIGCHLD, log);
        if(checkForExit(arguments)){
            end = 1;
            continue;
        }
        arguments[wordsCount] = NULL;
        int dontwait = 0;
        if(wordsCount > 1 && arguments[wordsCount-1][0] == '&' && arguments[wordsCount-1][1] =='\0'){
            dontwait = 1;
            free(arguments[wordsCount-1]);
            arguments[wordsCount-1] = NULL;
        }
        pid_t pid = fork();
        if(pid<0){
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if(pid == 0){
            execvp(arguments[0],arguments);
            return 0;
        } else {
            if(!dontwait)
            {
                wait(NULL);
            }
            dontwait = 1;
        }
    }
    return 0;
}