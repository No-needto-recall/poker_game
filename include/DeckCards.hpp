#ifndef _CTL_DECKCARDS_HPP_
#define _CTL_DECKCARDS_HPP_

#include "GroupCards.hpp"
#include <random>

using UseType=unsigned int;

class DeckCards
:public GroupCards
{
public:
    DeckCards(NumsType nums=52)
    :GroupCards(nums)
    ,_used(0)
    {}
    ~DeckCards() {}
    void PrintDeckCards(int row=13,int cow=4)const; 
    void SetDeckCards();

    Card SendCard(){
        _used=_used%_nums;
        return _cards[_used++];}
    void ResetSend(){_used=0;}

    void ShuffleDeck(int times=1);
private:
    UseType _used;
};

#endif
