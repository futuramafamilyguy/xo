#include <stdlib.h>
#include <stdio.h>
#include "stringmanip.h"

char** str_split(char *str, char splitBy) {

    int strLength = str_length(str);
    int posCurrentStr, splitCharCount = 0;
    posCurrentStr = 0;

    for (int i = 0; i < strLength; i++) {
        
        if (str[i] == splitBy) {
            
            splitCharCount++;
        }
    }

    char **strs = malloc((splitCharCount + 2) * sizeof(char*));
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
        
            strs[currentStrCount++][i - posCurrentStr + 1] = '\0';
            strs[currentStrCount] = malloc(sizeof(char));
            strs[currentStrCount] = NULL;
        }
    }

    return strs;
}

int str_length(const char *str) {
    
    int length = 0;
    while (str[length] != '\0' && str[length] != '\n') {
        
        length++;
    }

    return length;
}

int str_array_count(char **arr) {

    int count = 0;
    while (arr[count] != NULL) {

        count++;
    }

    return count;
}

int str_cmp(char *str, char *cmpStr) {

    int i = 0;
    while (str[i] != '\0' && cmpStr[i] != '\0') {

        if (str[i] != cmpStr[i++]) {

            return 0;
        }
    }

    return 1;
}

int str_to_int(char *str, int *result) {

    int sum, i = 0;

    while (str[i] != '\0') {

        if (str[i] < '0' || str[i] > '9') {

            (void)fprintf(stderr, "invalid char. should be between 0 - 9\n");

            return 0;
        }

        sum += (str[i] - '0') * (i + 1);
        i++;
    }

    *result = sum;

    return 1;
}
