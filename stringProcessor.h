//
// Created by hydroxide on ٦‏/١١‏/٢٠٢٠.
//

#ifndef TERMINAL_STRINGPROCESSOR_H
#define TERMINAL_STRINGPROCESSOR_H

breakStringIntoArgs(char * strArray[], char str[]){

}

int countWords(char str[]) {
    int i = 0;
    int nw = 0;
    int space = 1;
    while (str[i] != '\0'){
        if(str[i] == ' '){
            space = 1;
        } else if(space == 1) {
            nw++;
        }
        i++;
    }
    return nw;
}

int checkForExit(char str[]) {

}

#endif //TERMINAL_STRINGPROCESSOR_H
