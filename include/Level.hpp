#ifndef _CTL_LEVEL_HPP_
#define _CTL_LEVEL_HPP_

#include "HashMap.hpp"
#include "GroupCards.hpp"
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
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
    LV_ROYAL_FLUSH=1,
    LV_STRAIGHT_FLUSH=2,
    LV_FOUR_OF_A_KIND=11,
    LV_FULL_HOUSE=167,
    LV_FLUSH=323,
    LV_STRAIGHT=1600,
    LV_THREE_OF_A_KIND=1610,
    LV_TWO_PAIR=2468,
    LV_ONE_PAIR=3326,
    LV_HIGH_CARD=6186,
    LV_MAX=7463
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
    void CreatMapRoyalFlush();//1-1
    void CreatMapStraightFlush();//2-10
    void CreatMapFourOfAKind();//11-166
    void CreatMapFullHouse();//167-322
    void CreatMapFlush();//323-1599
    void CreatMapStraight();//1600-1609
    void CreatMapThreeOfAKind();//1610-2467
    void CreatMapTwoPair();//2468-3325
    void CreatMapOnePair();//3326-6185
    void CreatMapHighCard();//6186-7462
    void CreatMap();
    void ImageMap();
    void LoadMapFromFile();
    void WriteMapToFile();
    void ShowMap();
    bool Full();
    LevelType GetLevel(const Cards keycards);
    //删除赋值语句，拷贝构造、赋值运算符
    Level(const Level &rhs) = delete;
    Level &operator=(const Level &rhs) = delete;

private:
    //构造函数私有化
    Level() 
    :_HashMap(MathFunc::Group_M_To_K(52,5))
    {
        cout<<"size"<<_HashMap._valmap.size()<<endl;
    }
    //析构私有化
    ~Level() {}
    HashMap _HashMap;
    //定义一个该类型的静态指针
    static Level* _plevel;
};


//初始化静态成员
// Level* Level::_plevel=GetPlevel();//饿汉模式，开始就初始化

#endif


