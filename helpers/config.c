#include "config.h"
#include "stringmanip.h"
#include <stdio.h>

#define BUFFER_SIZE 100

int load_config(FILE *configfp, int *numOfPlayers) {
    
    char line[BUFFER_SIZE];

    while (!feof(configfp)) {
        
        char **configKeyValue = str_split(fgets(line, BUFFER_SIZE, configfp), '=');

        if (str_array_count(configKeyValue) != 2) {

            (void)fprintf(stderr, "all lines in config value should be key value pairs.\n");
            
            return 0;
        }

        if (str_cmp(configKeyValue[0], "num_of_players")) {

            if (!str_to_int(configKeyValue[1], numOfPlayers)) {
                
                return 0;
            }

            if (*numOfPlayers < 1 || *numOfPlayers > 2) {

                (void)fprintf(stderr, "invalid number of players. should be 1 or 2\n");

                return 0;
            }
        } else {

            (void)fprintf(stderr, "invalid config setting: %s\n", configKeyValue[0]);

            return 0;            
        }
    }

    return 1;
}