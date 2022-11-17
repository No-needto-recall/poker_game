#include "Table.hpp"


//Table的默认构造函数将会设置好卡组和公共牌
Table::Table()
:_deck()
,_publiccards(_deck)
,_jackpot()
{
    _deck.SetDeckCards();
}

//展示桌上的公共牌
void Table::ShowPublicCards(){
    _publiccards.show();
}
void Table::ShuffleDeck(int times){
    _deck.ShuffleDeck(times);
}