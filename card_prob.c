/*
This program calculates the probability of
drawing at least one copy of a specific card
by a given turn, a given number of cards to
mulligan, a given number of the specific card
that are in the deck, the deck size, and the
initial hand size
*/

#include <stdio.h>

double Calc_Prob_Not_Init_Draw(int deck_size, int initial_hand_size, int num_copies);
double Calc_Prob_Not_Mulligan(int deck_size, int initial_hand_size, int num_copies, int numMulligan);
double Calc_Prob_Not_Turn_Draw(int deck_size, int initial_hand_size, int num_copies, int turnAmount);
double Calc_Prob_Draw_Card(int deck_size, int initial_hand_size, int num_copies, int numMulligan, int turnAmount);

/*
This function calculates the probability of drawing the
specific card the user wants
@int deck_size: the total number of cards in the deck
@int initial_hand_size: the starting number of cards
that must be in the user's hand
@int num_copies: the number of copies of the specific
card the user wants that are in the deck
@int numMulligan: the number of cards the user wants
to mulligan
@int turnAmount: the turn the user wants to draw the
specific card by
@return: the probability of drawing the specific
card the user wants
*/
double Calc_Prob_Draw_Card(int deck_size, int initial_hand_size, int num_copies, int numMulligan, int turnAmount) {
    double prob_draw_card;

    prob_draw_card = 1 - (Calc_Prob_Not_Init_Draw(deck_size, initial_hand_size, num_copies) * Calc_Prob_Not_Mulligan(deck_size, initial_hand_size, num_copies, numMulligan) * Calc_Prob_Not_Turn_Draw(deck_size, initial_hand_size, num_copies, turnAmount));

    return prob_draw_card;
}

/*
This function calculates the probability of not
drawing the specific card the user wants during the
card drawing phase each turn
@int deck_size: the total number of cards in the deck
@int initial_hand_size: the starting number of cards
that must be in the user's hand
@int num_copies: the number of copies of the specific
card the user wants that are in the deck
@int turnAmount: the turn the user wants to draw the
specific card by
@return: the probability of not drawing the specific
card during the card drawing phase each turn
*/
double Calc_Prob_Not_Turn_Draw(int deck_size, int initial_hand_size, int num_copies, int turnAmount) {
    double prob_not_turn_draw;

    prob_not_turn_draw = ((double) (deck_size - num_copies - initial_hand_size)) / ((double) deck_size - initial_hand_size);

    for (int i = 1; i < turnAmount; ++i) {
        --deck_size;
       prob_not_turn_draw *= ((double) (deck_size - num_copies - initial_hand_size)) / ((double) deck_size - initial_hand_size);
    }

    if (turnAmount == 0) {
        prob_not_turn_draw = 1;
    }

    return prob_not_turn_draw;
}

/*
This function calculates the probability of not
drawing the specific card the user wants in the
mulliganing phase
@int deck_size: the total number of cards in the deck
@int initial_hand_size: the starting number of cards
that must be in the user's hand
@int num_copies: the number of copies of the specific
card the user wants that are in the deck
@int numMulligan: the number of cards the user wants
to mulligan
@return: the probability of not drawing the specific
card during the mulliganing phase
*/
double Calc_Prob_Not_Mulligan(int deck_size, int initial_hand_size, int num_copies, int numMulligan) {
    double prob_not_mulligan;

    prob_not_mulligan = ((double) (deck_size - num_copies - initial_hand_size)) / ((double) deck_size - initial_hand_size);

    for (int i = 1; i < numMulligan; ++i) {
        --deck_size;
       prob_not_mulligan *= ((double) (deck_size - num_copies - initial_hand_size)) / ((double) deck_size - initial_hand_size);
    }

    if (numMulligan == 0) {
        prob_not_mulligan = 1;
    }

    return prob_not_mulligan;
}

/*
This function calculates the probability of not
drawing the specific card the user wants in the
initial draw phase
@int deck_size: the total number of cards in the deck
@int initial_hand_size: the starting number of cards
that must be in the user's hand
@int num_copies: the number of copies of the specific
card the user wants that are in the deck
@return: the probability of not drawing the specific
card during the initial draw phase
*/
double Calc_Prob_Not_Init_Draw(int deck_size, int initial_hand_size, int num_copies) {
    double prob_not_init_draw;

    prob_not_init_draw = ((double) (deck_size - num_copies)) / ((double) deck_size);
    
    for (int i = 1; i < initial_hand_size; ++i) {
        --deck_size;
        prob_not_init_draw *= ((double) (deck_size - num_copies)) / ((double) deck_size);
    }

    return prob_not_init_draw;
}

int main(void) {
    int deckSize, numCopies, init_hand_size, num_mulligan, turnSize;
    
    printf("Enter how many total cards there are in the deck: ");
    scanf("%d", &deckSize);
    printf("\n");

    printf("Enter how many copies of the card that you are looking for are in the deck: ");
    scanf("%d", &numCopies);
    printf("\n");

    printf("Enter your initial hand size: ");
    scanf("%d", &init_hand_size);
    printf("\n");

    printf("Enter how many cards you are mulliganing: ");
    scanf("%d", &num_mulligan);
    printf("\n");

    printf("Enter what turn you want to draw the card by: ");
    scanf("%d", &turnSize);
    printf("\n");

    printf("The probability of drawing at least one of the cards by turn %d given you mulliganed %d cards is %.2lf\n\n", turnSize, num_mulligan, Calc_Prob_Draw_Card(deckSize, init_hand_size, numCopies, num_mulligan, turnSize));

    return 0;
}
