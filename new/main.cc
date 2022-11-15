#include "DeckCards.hpp"



int main()
{
    DeckCards deck;
    deck.SetDeckCards();
    deck.Shuffle_Deck();
    deck.PrintDeckCards(4,13);
    return 0;
}

