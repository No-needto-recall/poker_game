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
    void AutoGetSafe();
    void AutoGet();
    void CleanCards(){_cards.clear();}
    void RebindDeck(DeckCards& deck){_deck=&deck;}
private:
    DeckCards* _deck;
};

inline void HandCards::AutoGetSafe(){
    if(GetSize()==0||GetSize()==1){
        _cards.push_back((*_deck).SendCard());
    }else{}
}

inline void HandCards::AutoGet(){
    _cards.push_back((*_deck).SendCard());
}




#endif
