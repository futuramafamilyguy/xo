#include "config.h"
#include "stringmanip.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

void free_config(char **config);

int load_config(FILE *configfp, int *numOfPlayers, char *player1Name, char *player2Name) {
    
    char line[BUFFER_SIZE];

    while (!feof(configfp)) {
        
        char **configKeyValue = str_split(fgets(line, BUFFER_SIZE, configfp), '=');

        if (str_array_count(configKeyValue) != 2) {

            (void)fprintf(stderr, "all lines in config value should be key value pairs.\n");
            
            free_config(configKeyValue);

            return 0;
        }

        if (str_cmp(configKeyValue[0], "num_of_players")) {
            
            if (!str_to_int(configKeyValue[1], numOfPlayers)) {
                
                free_config(configKeyValue);

                return 0;
            }

            if (*numOfPlayers < 1 || *numOfPlayers > 2) {

                (void)fprintf(stderr, "invalid number of players. should be 1 or 2\n");

                free_config(configKeyValue);

                return 0;
            }
        } else if (str_cmp(configKeyValue[0], "player_1_name")) {

            player1Name = configKeyValue[1];
        } else if (str_cmp(configKeyValue[0], "player_2_name")) {

            player2Name = configKeyValue[1];
        } else {

            (void)fprintf(stderr, "invalid config setting: %s\n", configKeyValue[0]);

            free_config(configKeyValue);

            return 0;            
        }

        free_config(configKeyValue);
    }

    return 1;
}

void free_config(char **config) {

    int strCount = str_array_count(config);

    for (int i = 0; i < strCount; i++) {

        free(config[i]);
    }

    free(config);
}
