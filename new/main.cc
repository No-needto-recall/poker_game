#include "DeckCards.hpp"



int main()
{
    DeckCards deck;
    deck.SetDeckCards();
    GROUP_CARDS::SortCardsColour(deck.RuturnCards());
    deck.PrintDeckCards(4,13);
    return 0;
}

