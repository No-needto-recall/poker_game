#include "DeckCards.hpp"
#include "Type.hpp"
#include "HandCards.hpp"

int main()
{
    DeckCards deck;
    HandCards hand1(deck);
    HandCards hand2(deck);
    HandCards hand3(deck);
    HandCards hand4(deck);
    deck.SetDeckCards();
    deck.Shuffle_Deck();
    deck.PrintDeckCards(4,13);
    for(int i=0;i<2;++i){
        hand1.AutoGet();
        hand2.AutoGet();
        hand3.AutoGet();
        hand4.AutoGet();
    }
    hand1.show();
    hand2.show();
    hand3.show();
    hand4.show();


    return 0;
}

