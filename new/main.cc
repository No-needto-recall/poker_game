#include "Type.hpp"
#include "HandCards.hpp"
#include "PublicCards.hpp"
int main()
{
    DeckCards deck;
    HandCards hand1(deck);
    HandCards hand2(deck);
    HandCards hand3(deck);
    HandCards hand4(deck);
    PublicCards pub(deck);
    deck.SetDeckCards();
    deck.ShuffleDeck();
    for(int i=0;i<2;++i){
        hand1.AutoGet();
        hand2.AutoGet();
        hand3.AutoGet();
        hand4.AutoGet();
    }
    deck.SendCard();
    deck.SendCard();
    pub.AutoGetSafe();
    pub.show();
    pub.AutoGetSafe();
    pub.show();
    pub.AutoGetSafe();
    pub.show();
    hand1.show();
    hand2.show();
    hand3.show();
    hand4.show();


    return 0;
}

