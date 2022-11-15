#ifndef _CTL_GROUPCARDS_HPP_
#define _CTL_GROUPCARDS_HPP_

#include "Card.hpp"
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

using Cards=vector<Card>;
using NumsType=unsigned int;


class GroupCards 
{
public:
    GroupCards(NumsType nums)
    :_nums(nums)
    ,_cards()
    {
        _cards.reserve(_nums);
    }
    virtual~GroupCards() {}
    NumsType GetNums()const{return _nums;}
    Card& GetCards(){return _cards.front();}
    const Card*GetCards()const{return &_cards.front();}
    Cards& ReturnCards(){return _cards;}
    Cards ReturnCards()const{return _cards;}
protected:
    Cards _cards;
    NumsType _nums;

};


namespace GROUP_CARDS{
    //指定几行几列打印卡牌
    //row:行 cow:列
    void PrintCards(const GroupCards &cards, const int row=1,const int cow=5);
    void SortCardsNum(Cards& cards);
    void SortCardsColour(Cards& cards);
}//end of CARDS

#endif
