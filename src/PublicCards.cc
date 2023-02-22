#include "PublicCards.hpp"

void PublicCards::show()const{
    GROUP_CARDS::PrintCards(*this,1,GetSize());
}
