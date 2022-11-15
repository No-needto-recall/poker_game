#ifndef _CTL_HANDCARDS_HPP_
#define _CTL_HANDCARDS_HPP_

#include "DeckCards.hpp"

class HandCards
:public GroupCards
{
public:
    HandCards(DeckCards& deck)
    :GroupCards(2)
    ,_deck(&deck)
    {}
    ~HandCards() {}
    void show()const;
    void GetCard(Card card);
    void AutoGet();
    void CleanCards(){_cards.clear();}
    void RebindDeck(DeckCards& deck){_deck=&deck;}
private:
    DeckCards* _deck;
};
void HandCards::AutoGet(){
    _cards.push_back((*_deck).SendCard());
}


void HandCards::show()const{
    GROUP_CARDS::PrintCards(*this,1,2);
}

void HandCards::GetCard(Card card){
    _cards.push_back(card);
}
#endif
