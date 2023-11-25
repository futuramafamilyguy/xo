#include <stdio.h>

#ifndef CONFIG_H
#define CONFIG_H

int load_config(FILE *configfp,int *numOfPlayers, char **player1Name, char **player2Name);

#endif
