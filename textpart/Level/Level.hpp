#ifndef _CTL_LEVEL_HPP_
#define _CTL_LEVEL_HPP_

#include "GroupCards.hpp"
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

using std::cin;
using std::string;
using std::unordered_map;
using std::map;

using LevelType=unsigned int;

namespace LEVEL{
    LevelType GetLevel(Cards keycards);
    string CardsToString(Cards cards);
    Cards StringToCards(string strcard);
}//end of LEVEL

class Level
{
public:
    Level() {}
    ~Level() {}
    void CreatMap();
    void ImageMap();

    void ShowMap();
private:
    unordered_map<string,int> _cardsmap;
    map<int,vector<string> > _imagemap;

};

#endif


