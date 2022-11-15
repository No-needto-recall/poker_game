#ifndef _CTL_FIVECARDS_HPP_
#define _CTL_FIVECARDS_HPP_

#include "GroupCards.hpp"


using TypeType=unsigned int;

class FiveCards
:public GroupCards
{
public:
    FiveCards(int nums=5)
    :GroupCards(nums)
    {}
    ~FiveCards() {}

private:
    TypeType _type;
};


namespace TYPE{

    TypeType GetType(Cards );

}//end of TYPE


#endif
