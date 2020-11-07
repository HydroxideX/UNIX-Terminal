//
// Created by hydroxide on ٦‏/١١‏/٢٠٢٠.
//
#ifndef TERMINAL_STRINGPROCESSOR_H
#define TERMINAL_STRINGPROCESSOR_H
#include <string.h>


void breakStringIntoArgs(char * strArray[], char str[]){
    int currWordToFill = 0;
    int space = 1;
    int i = 0;
    //loop with double pointers i pointing at start of the word and j at its end
    for(int j = 0; j < strlen(str); j++) {
        if(str[j] == ' '){
            if(!space){
                //allocate space for the word to add it into
                char* s2 = (char*)calloc(j-i+1, sizeof(char));
                for(int k = 0;k < j-i; k++){
                    s2[k] = str[i+k];
                }
                s2[j-i] = '\0';
                //add argument to array
                strArray[currWordToFill] = s2;
                currWordToFill++;
            }
            space = 1;
        } else if(space == 1) {
            //new letter is encountered set i to the beginning letter
            space = 0;
            i = j;
        }
    }
}


int countWords(char str[]) {
    int nw = 0;
    int space = 1;
    for(int i = 0; i < strlen(str); i++) {
        //if enncounter space set boolean to one
        if(str[i] == ' ') {
            space = 1;
        } else if(space == 1) {
            //if a new space is encountered after a word increment the word count
            space = 0;
            nw++;
        }
    }
    return nw;
}

int checkForExit(char* arguments[]) {
    //check if first argument is equal to "exit"
    char* str = arguments[0];
    if(str[0] == 'e' && str[1] == 'x' && str[2] == 'i' && str[3] == 't'){
       return 1;
    }
    return 0;
}

#endif //TERMINAL_STRINGPROCESSOR_H
