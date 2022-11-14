#ifndef _CTL_DECKCARDS_HPP_
#define _CTL_DECKCARDS_HPP_

#include "GroupCards.hpp"


class DeckCards
:public GroupCards
{
public:
    DeckCards(int nums=52)
    :GroupCards(nums)
    ,_used(0)
    {}
    ~DeckCards() {}
    void PrintDeckCards(int row=13,int cow=4)const; 
    void SetDeckCards();

private:
    size_t _used;
};

#endif
