#ifndef _CTL_PUBLICCARDS_HPP_
#define _CTL_PUBLICCARDS_HPP_

#include "DeckCards.hpp"

class PublicCards
:public GroupCards
{
public:
    PublicCards(DeckCards& deck)
    :GroupCards(5)
    ,_deck(&deck)
    {}
    ~PublicCards() {}
    void show()const;
    void AutoGetSafe();
    void AutoGet();
    void CleanCards(){_cards.clear();}
    void RebindDeck(DeckCards & deck){_deck=&deck;}
private:
    DeckCards* _deck;
};


inline void PublicCards::AutoGetSafe(){
    if(GetSize()==0){
        _cards.push_back((*_deck).SendCard());
        _cards.push_back((*_deck).SendCard());
        _cards.push_back((*_deck).SendCard());
        (*_deck).SendCard();
        return;
    }else if (GetSize()==3){
        _cards.push_back((*_deck).SendCard());
        (*_deck).SendCard();
        return;
    }else if(GetSize()==4){
        _cards.push_back((*_deck).SendCard());
        return;
    }else{}
}

inline void PublicCards::AutoGet(){
    _cards.push_back((*_deck).SendCard());
}


#endif
