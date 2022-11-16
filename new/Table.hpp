#ifndef _CTL_TABLE_HPP_
#define _CTL_TABLE_HPP_

#include "PublicCards.hpp"

class Table
{
public:
    Table(); 
    ~Table() {}
    void ShuffleDeck(int times=1);
    void ResetSend(){_deck.ResetSend();}
    DeckCards* ReturnDeckPtr(){return &_deck;}
    PublicCards* ReturnPublicCardsPtr(){return &_publiccards;}
private:
    DeckCards _deck;
    PublicCards _publiccards;
};

Table::Table()
:_deck()
,_publiccards(_deck)
{
    _deck.SetDeckCards();
}

void Table::ShuffleDeck(int times){
    _deck.ShuffleDeck(times);
}

#endif
