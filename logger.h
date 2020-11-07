#ifndef TERMINAL_LOGGER_H
#define TERMINAL_LOGGER_H
#include <time.h>

//log child termination at log file using time
void log(int sig) {
    FILE *pFile;
    //open file to append
    pFile=fopen("log.txt", "a");
    if(pFile==NULL) {
        perror("Error opening file.");
    }
    else {
        //get current time
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        //write to file the child termination and time
        fprintf(pFile, "Child Process was Terminated at Time %s", asctime(timeinfo));
        fflush(stdout);
    }
    fclose(pFile);
}

#endif
