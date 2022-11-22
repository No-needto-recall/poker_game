#ifndef _CTL_LEVEL_HPP_
#define _CTL_LEVEL_HPP_

#include "GroupCards.hpp"
#include <cstdlib>
#include <cstdio>
#include <ctime>
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

enum LevelNum:LevelType{
    LV_MIN=1,
    LV_MAX=7464
};


//考虑设计为单例
//可以考虑将_cardsmap和_imagemap磁盘化
class Level
{
public:
    static Level* GetPlevel()
    {
        if(_plevel==nullptr)
        {
            atexit(Destroy);
            _plevel=new Level();
        }
        return _plevel;
    }
    static void Destroy(){
        if(_plevel){
            delete _plevel;
            _plevel=nullptr;
        }
    }
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
    void LoadMapFromFile();
    void WriteMapToFile();
    void ShowMap();
    LevelType GetLevel(const Cards keycards);
    //删除赋值语句，拷贝构造、赋值运算符
    Level(const Level &rhs) = delete;
    Level &operator=(const Level &rhs) = delete;

private:
    //构造函数私有化
    Level() {}
    //析构私有化
    ~Level() {}
    unordered_map<string,LevelType> _cardsmap;
    map<LevelType,vector<string> > _imagemap;
    //定义一个该类型的静态指针
    static Level* _plevel;
};

//初始化静态成员
// Level* Level::_plevel=GetPlevel();//饿汉模式，开始就初始化

#endif


