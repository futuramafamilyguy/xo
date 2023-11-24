#include <stdlib.h>
#include <stdio.h>
#include "stringmanip.h"

char** str_split(char *str, char splitBy) {

    int strLength = str_length(str);
    int posCurrentStr, splitCharCount = 0;

    for (int i = 0; i < strLength; i++) {
        
        if (str[i] == splitBy) {
            
            splitCharCount++;
        }
    }

    char **strs = malloc((splitCharCount + 1) * sizeof(char*));
    strs[0] = malloc((strLength + 1) * sizeof(char));
    int currentStrCount = 0;

    for (int i = 0; i < strLength; i++) {
        
        if (str[i] != splitBy) {

            strs[currentStrCount][i - posCurrentStr] = str[i];
        } else {

            if (i == posCurrentStr) {

                posCurrentStr++;

                continue;
            }

            strs[currentStrCount++][i - posCurrentStr + 1] = '\0';
            strs[currentStrCount] = malloc((strLength + 1) * sizeof(char));
            posCurrentStr = i + 1;
        }

        if (i == (strLength - 1)) {
        
            strs[currentStrCount][i - posCurrentStr + 1] = '\0';
        }
    }
    
    return strs;
}

int str_length(char *str) {
    
    int length = 0;
    while (str[length] != '\0') {
        
        length++;
    }

    return length;
}