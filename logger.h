#ifndef TERMINAL_LOGGER_H
#define TERMINAL_LOGGER_H
#include <time.h>

void log(int sig) {
    FILE *pFile;
    pFile=fopen("log.txt", "a");
    if(pFile==NULL) {
        perror("Error opening file.");
    }
    else {
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        fprintf(pFile, "Child Process was Terminated at Time %s", asctime(timeinfo));
        fflush(stdout);
    }
    fclose(pFile);
}

#endif
