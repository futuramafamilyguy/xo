#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_PLAYERS 2
#define NUM_OF_SQUARES 9
#define BOARD_DIM 3

typedef struct {
    int id;
    char symbol;
}Player;

typedef struct {
    int x, y, pos;
    Player *player;
}Sq;

Sq* init_squares();

Player* init_players();

void print_grid(Sq *squares);

char get_square_value(Sq *square);

int prompt_user(Player *currentPlayer, int *pos);

int execute_move(Player *currentPlayer, Sq *squares, int pos);

int main() {
    
    // instantiate sq
    Sq *squares = init_squares();

    // instantiate players
    Player *players = init_players();

    int turnCounter = 0;
    int inputPos;

    do {
        print_grid(squares);

        if (!prompt_user(&players[turnCounter], &inputPos)) {
            
            continue;
        }

        if (!execute_move(&players[turnCounter], squares, inputPos)) {

            continue;
        }

        turnCounter = 1 - turnCounter;
        
    } while (1);

    // clean up
    free(squares);
    free(players);

    return 0;
}

Sq* init_squares() {

    Sq *squares = malloc(NUM_OF_SQUARES * sizeof(Sq));

    for (int i = 0; i < BOARD_DIM; i++) {
        for (int j = 0; j < BOARD_DIM; j++) {
            int count = i * BOARD_DIM + j;
            squares[count].x = i;
            squares[count].y = j;
            squares[count].pos = count + 1;
        }
    }

    return squares;
}

Player* init_players() {

    Player *players = malloc(NUM_OF_PLAYERS * sizeof(Player));
    players[0].id = 1;
    players[0].symbol = 'X';
    players[1].id = 2;
    players[1].symbol = 'O';

    return players;
}

int prompt_user(Player *currentPlayer, int *pos) {

    printf("player %d's turn. enter square to place mark (1-9): ", currentPlayer->id);

    char input, first;
    int count = 0;

    first = fgetc(stdin);
    while (((input = fgetc(stdin)) != '\n') && (input != EOF)) {
        count++;
    }

    if (count > 0 || (first < '1') || (first > '9')) {
        printf("invalid input. try again.\n");

        return 0;
    }

    *pos = first - '0';
    
    return 1;
}

int execute_move(Player *currentPlayer, Sq *squares, int pos) {

    if (squares[pos - 1].player) {
        
        printf("square %d is already marked. try again\n", pos);

        return 0;
    }

    squares[pos - 1].player = currentPlayer;

    return 1;
}

void print_grid(Sq *squares) {

    char values[NUM_OF_SQUARES];

    for (int i = 0; i < NUM_OF_SQUARES; i++) {
        values[i] = get_square_value(&squares[i]);
    }

    printf("  |   |   |   |  \n");
    printf("--|---|---|---|--\n");
    printf("  | %c | %c | %c |  \n", values[0], values[1], values[2]);
    printf("--|---|---|---|--\n");
    printf("  | %c | %c | %c |  \n", values[3], values[4], values[5]);
    printf("--|---|---|---|--\n");
    printf("  | %c | %c | %c |  \n", values[6], values[7], values[8]);
    printf("--|---|---|---|--\n");
    printf("  |   |   |   |  \n");
}

char get_square_value(Sq* square) {

    if (square->player) {

        return square->player->symbol;
    }

    return square->pos + '0';
}
