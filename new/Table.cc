#include "Table.hpp"

//展示桌上的公共牌
void Table::ShowPublicCards(){
    _publiccards.show();
}
void Table::ShuffleDeck(int times){
    _deck.ShuffleDeck(times);
}