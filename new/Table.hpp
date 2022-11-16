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
    Cards ReturnPublicCards(){return _publiccards.ReturnCards();}
    void AutoSendToPublicCards(){_publiccards.AutoGetSafe();}
    void ShowPublicCards();
private:
    DeckCards _deck;
    PublicCards _publiccards;
};

//Table的默认构造函数将会设置好卡组和公共牌
inline
Table::Table()
:_deck()
,_publiccards(_deck)
{
    _deck.SetDeckCards();
}



#endif
