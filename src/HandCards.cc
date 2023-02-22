#include "HandCards.hpp"

void HandCards::show()const{
    GROUP_CARDS::PrintCards(*this,1,GetSize());
}
