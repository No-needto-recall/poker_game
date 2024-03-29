#ifndef _CTL_TYPE_HPP_
#define _CTL_TYPE_HPP_

#include "GroupCards.hpp"
#include "Level.hpp"
#include <map>
#include <functional>

using std::map;
using std::function;
using std::cerr;

using TypeType=unsigned short;
enum TypeCards:TypeType{
    HIGH_CARD=1,ONE_PAIR,TWO_PAIRS,THREE_OF_A_KIND,STRAIGHT,
    FLUSH,FULL_HOUSE,FOUR_OF_A_KIND,STRAIGHT_FLUSH,ROYAL_FLUSH
};

class Type;
using Compare =function<bool(const Type &,const Type&)>;
namespace GREADER{
    /* bool KindCard(const Type&,const Type &); */
    // bool HighCard(const Type&,const Type &);
    // bool RoyalFlush(const Type&,const Type &);
}//end of GREADER

namespace EQUA{
    /* bool Equa(const Type&,const Type &); */
}//end of EQUA

namespace TYPE{
    /* bool IsStraight(const Cards &cards); */
    /* bool IsRoyalFlush(const Cards &cards); */
    /* TypeType GetType(const Cards&cards5); */
    LevelType GetLevelFromMap(const Cards&card5);
    void PrintType(TypeType type);

    // Compare SetGreadter(const TypeType type);
    Type GainType(Cards cards);
    LevelType GainLevel(Cards cards);
    //根据公共牌返回对应的插入Cards排序
    void SwapCards(const Cards& pubcards,Cards& target);
    //查找contrust是否在pubcards中，如果是返回pos，不是返回-1；
    int FindCardInCards(const Cards& pubcards,const Card& contrust);

    
    
}//end of TYPE



class Type
:public GroupCards
{
public:
    Type()
    :GroupCards(5)
    // ,_greadter(nullptr)
    ,_level(0)
    {}
    Type(Cards cards5);
    Type(const Type &rhs)
        : GroupCards(5)
        , _level(rhs._level)
    {_cards = rhs._cards;}
    Type(Type &&rhs)
        : GroupCards(5)
        , _level(rhs._level)
    {_cards=rhs._cards;}

    Type &operator=(const Type &rhs){
        if(this!=&rhs){
            this->_cards = rhs._cards;
            // this->_greadter=rhs._greadter;
            this->_level=rhs._level;
        }
        return *this;
   }
   Type &operator=(Type &&rhs)
   {
       if (this != &rhs)
       {
           this->_cards = rhs._cards;
        //    this->_greadter = rhs._greadter;
           this->_level= rhs._level;
       }
       return *this;
   }

    ~Type() {}
    bool operator >(const Type &)const;
    bool operator <(const Type &)const;
    bool operator ==(const Type &)const;
    bool operator !=(const Type &)const;
    bool operator >=(const Type &)const;
    bool operator <=(const Type &)const;
     
    void Show()const;
    void ResetType(){
        _level=0;
        _cards.clear();
    }
    void SetCards(Cards cards);
    void SetLevel(LevelType lv);
    TypeType GetType()const{return LevelToType(_level);}
    TypeType LevelToType(const LevelType)const;
private:
    // Compare _greadter;
    LevelType _level;
};


inline void Type::SetLevel(LevelType lv){
    _level=lv;
}


#endif
