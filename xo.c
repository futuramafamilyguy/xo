#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_OF_PLAYERS 2
#define NUM_OF_SQUARES 9
#define BOARD_DIM 3

typedef struct {
    int id, isAi;
    char symbol;
}Player;

typedef struct {
    int x, y, pos;
    Player *player;
}Sq;

Sq* init_squares();

Player* init_players(int numOfHumanPlayers);

void print_grid(Sq *squares);

char get_square_value(Sq *square);

int execute_move(Player *currentPlayer, Sq *squares, int pos);

int check_game_ended(Sq *squares, int turnNumber, int lastInputPos, int *draw);

int check_horizontal(Sq *squares, int lastInputPos);

int check_vertical(Sq *squares, int lastInputPos);

int check_diagonal(Sq *squares, int lastInputPos);

int prompt_single_digit_within_range(int *num, int low, int high);

void ai_select_pos(int *inputPos, Sq* squares);

int main() {

    srand(time(NULL));
    
    printf("xoxo the game^tm\n");

    int numOfHumanPlayers;
    do {
        printf("enter number of players (1 or 2): ");

    } while (!prompt_single_digit_within_range(&numOfHumanPlayers, 1, 2));

    Sq *squares = init_squares();

    Player *players = init_players(numOfHumanPlayers);

    int turnNumber = 0;
    int inputPos;
    int draw;

    do {
        print_grid(squares);

        if (!players[turnNumber % 2].isAi) {

            printf("player %d's turn. enter square to place mark (1-9): ", players[turnNumber % 2].id);

            if (!prompt_single_digit_within_range(&inputPos, 1, 9)) {
                
                continue;
            }
        } else {

            printf("ai is thinking...\n");
            sleep(2);
            ai_select_pos(&inputPos, squares);
            printf("ai placed mark at square %d\n", inputPos);
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

Player* init_players(int numOfHumanPlayers) {

    Player *players = malloc(NUM_OF_PLAYERS * sizeof(Player));
    players[0].id = 1;
    players[0].symbol = 'X';
    players[0].isAi = 0;
    players[1].id = 2;
    players[1].symbol = 'O';
    players[1].isAi = (numOfHumanPlayers == 1);

    return players;
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

int prompt_single_digit_within_range(int *num, int low, int high) {
    
    char input, first;
    int count = 0;

    first = fgetc(stdin);
    while (((input = fgetc(stdin)) != '\n') && (input != EOF)) {
        count++;
    }

    if (count > 0 || (first < low + '0') || (first > high + '0')) {
        printf("invalid input. try again.\n");

        return 0;
    }                                       

    *num = first - '0';

    return 1;
}

void ai_select_pos(int *inputPos, Sq* squares) {
    
    int freeSquares[NUM_OF_SQUARES];
    int freeSquareCount = 0;

    for (int i = 0; i < NUM_OF_SQUARES; i++) {

        if (!squares[i].player) {

            freeSquares[freeSquareCount++] = squares[i].pos;
        }
    }

    *inputPos = freeSquares[rand() % 9]; 
}
