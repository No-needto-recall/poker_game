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

void DeckCards::Shuffle_Deck(int times){
    srand(time(NULL));
    Card tmp;
    for(int j=0;j<times;++j){
        for(int i=52-1;i>=0;--i){
            tmp=_cards[i];
            int ch=rand()%(i+1);
            _cards[i]=_cards[ch];
            _cards[ch]=tmp;
        }
    }
}