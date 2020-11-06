#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "logger.h"
#include "stringProcessor.h"

int main() {
    char str[50];
    int end = 0;
    while(!end){

        scanf("%s", str);
        int no = countWords(str);
        printf("%d\n", no);
    }

    return 0;
}


/*
 if(checkForExit(str)){
            end = 1;
            continue;
        }
 pid_t pid;
        pid = fork();
        if(pid<0){
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if(pid == 0){
            char *args[]={str,str,NULL};
            execvp(args[0],args);
        } else {
            wait(NULL);
            printf("Child Complete");
        }
 */