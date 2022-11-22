#ifndef _CTL_LEVEL_HPP_
#define _CTL_LEVEL_HPP_

#include "GroupCards.hpp"
#include <map>
#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

using LevelType=unsigned int;

namespace LEVEL{
    LevelType GetLevel(Cards keycards);
    string CardsToString(Cards cards);
}//end of LEVEL

class Level
{
public:
    Level() {}
    ~Level() {}
    void CreatMap();
    void ShowMap();
private:
    unordered_map<string,int> _cardsmap;

};

#endif


