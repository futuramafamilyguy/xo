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

int check_game_ended(Sq *squares, int turnNumber, int lastInputPos, int *draw);

int check_horizontal(Sq *squares, int lastInputPos);

int check_vertical(Sq *squares, int lastInputPos);

int check_diagonal(Sq *squares, int lastInputPos);

int main() {
    
    Sq *squares = init_squares();

    Player *players = init_players();

    int turnNumber = 0;
    int inputPos;
    int draw;

    do {
        print_grid(squares);

        if (!prompt_user(&players[turnNumber % 2], &inputPos)) {
            
            continue;
        }

        if (!execute_move(&players[turnNumber % 2], squares, inputPos)) {

            continue;
        }
        
        turnNumber++;

    } while (!check_game_ended(squares, turnNumber, inputPos, &draw));

    print_grid(squares);

    if (draw) {
        printf("draw\n");
    } else {
        printf("player %d wins\n", players[(turnNumber - 1) % 2].id);
    }

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

int check_game_ended(Sq *squares, int turnNumber, int lastInputPos, int *draw) {
    
    if (turnNumber < 4) {
        
        return 0;
    }

    lastInputPos--;

    if (!check_horizontal(squares, lastInputPos)
        && !check_vertical(squares, lastInputPos)
        && !check_diagonal(squares, lastInputPos)) {
        
        if (turnNumber < NUM_OF_SQUARES) {
            
            return 0;
        }

        *draw = 1;

        return 1;
    }

    *draw = 0;

    return 1;
}

int check_horizontal(Sq *squares, int pos) {
    
    int squaresPos[3];
    
    int quotient = pos / BOARD_DIM;

    switch (quotient) {

        case 0:
        squaresPos[0] = 0;
        squaresPos[1] = 1;
        squaresPos[2] = 2;
        break;

        case 1:
        squaresPos[0] = 3;
        squaresPos[1] = 4;
        squaresPos[2] = 5;
        break;

        case 2:
        squaresPos[0] = 6;
        squaresPos[1] = 7;
        squaresPos[2] = 8;
        break;
    }
    
    return squares[squaresPos[0]].player == squares[squaresPos[1]].player && squares[squaresPos[0]].player == squares[squaresPos[2]].player;
}

int check_vertical(Sq *squares, int pos) {
    
    int squaresPos[3];
    
    int remainder = pos / BOARD_DIM;

    switch (remainder) {

        case 0:
        squaresPos[0] = 0;
        squaresPos[1] = 3;
        squaresPos[2] = 6;
        break;

        case 1:
        squaresPos[0] = 1;
        squaresPos[1] = 4;
        squaresPos[2] = 7;
        break;

        case 2:
        squaresPos[0] = 2;
        squaresPos[1] = 4;
        squaresPos[2] = 8;
        break;
    }
    
    return squares[squaresPos[0]].player == squares[squaresPos[1]].player && squares[squaresPos[0]].player == squares[squaresPos[2]].player;
}

int check_diagonal(Sq *squares, int pos) {

    if (pos % 2 == 1) {
        
        return 0;
    }

    if (pos != 4 && pos % 4 == 0) {
        
        return squares[0].player == squares[4].player && squares[0].player == squares[8].player;
    } else if (pos != 4 && pos % 7 == 1) {

        return squares[2].player == squares[4].player && squares[2].player == squares[6].player;
    }

    return squares[0].player == squares[4].player && squares[0].player == squares[8].player
        || squares[2].player == squares[4].player && squares[2].player == squares[6].player;
}
