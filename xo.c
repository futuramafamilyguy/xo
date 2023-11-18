#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_SQUARES 9
#define BOARD_DIM 3

typedef struct {
    int id;
    char symbol;
}Player;

typedef struct {
    int x, y, id;
    Player *player;
}Sq;

Sq* init_squares();

void print_grid(Sq *squares);

char get_square_value(Sq* square);

int main() {
    
    // instantiate sq
    Sq *squares = init_squares();
    print_grid(squares);
    // instantiate players

    // do
    //     print board

    //     determine player turn

    //     player move

    // while (check if game over)

    // clean up
    free(squares);

    return 0;
}

Sq* init_squares() {
    Sq *squares = malloc(NUM_OF_SQUARES * sizeof(Sq));

    for (int i = 0; i < BOARD_DIM; i++) {
        for (int j = 0; j < BOARD_DIM; j++) {
            int count = i * BOARD_DIM + j;
            squares[count].x = i;
            squares[count].y = j;
            squares[count].id = count + 1;
        }
    }

    return squares;
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
    return square->id + '0';
}
