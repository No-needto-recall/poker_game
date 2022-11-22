#ifndef _CTL_LEVEL_HPP_
#define _CTL_LEVEL_HPP_

#include "GroupCards.hpp"
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

using std::cerr;
using std::cin;
using std::string;
using std::unordered_map;
using std::map;

using LevelType=unsigned short;

namespace LEVEL{
    string CardsToString(const Cards cards);
    Cards StringToCards(const string strcard);
}//end of LEVEL


//考虑设计为单例
//可以考虑将_cardsmap和_imagemap磁盘化
class Level
{
public:
    Level() {}
    ~Level() {}
    void CreatMapRoyalFlush();//1-2
    void CreatMapStraightFlush();//3-12
    void CreatMapFourOfAKind();//13-168
    void CreatMapFullHouse();//169-324
    void CreatMapFlush();//325-1601
    void CreatMapStraight();//1602-1611
    void CreatMapThreeOfAKind();//1612-2469
    void CreatMapTwoPair();//2470-3327
    void CreatMapOnePair();//3328-6187
    void CreatMapHighCard();//6188-7464
    void CreatMap();
    void ImageMap();

    void ShowMap();
    LevelType GetLevel(const Cards keycards);
private:
    unordered_map<string,LevelType> _cardsmap;
    map<LevelType,vector<string> > _imagemap;

};

#endif


