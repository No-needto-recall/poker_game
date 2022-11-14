#include "DeckCards.hpp"

void DeckCards::PrintDeckCards(int row,int cow)const{
    const GroupCards& pgc=*this;
    GROUP_CARDS::PrintCards(pgc,row,cow);
}

void DeckCards::SetDeckCards(){
    for(int i=0;i<13;++i){
        for(int j=0;j<4;++j){
            _cards.push_back(Card(i+2,j));
        }
    }
}
