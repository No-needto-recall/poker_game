#ifndef _CTL_CARD_HPP_
#define _CTL_CARD_HPP_

#include <iostream>

using std::cout;
using std::endl;
using NumType=int;
using ColourType=int;
//0,1,2,3
//♠,♥,♣,♦
enum Suits:ColourType{
    SUITS_SPADE,//♠
    SUITS_HEARTS,//♥
    SUITS_DIAMONDS,//♣
    SUITS_CLUBS//♦
};
//点数2,3,4,5,6,7,8,9,10,J ,Q ,K ,A
//对应2,3,4,5,6,7,8,9,10,11,12,13,14
enum Nums:NumType{
    NUM_2=2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    NUM_10,
    NUM_J,
    NUM_Q,
    NUM_K,
    NUM_A
};

class Card
{
    
public:
    Card()
    :_num(3)
    ,_colour(0){}

    Card(NumType num,ColourType colour) 
    :_num(num)
    ,_colour(colour){}
    
    ~Card() {}
    Card &operator=(const Card &card){
        this->_num=card._num;
        this->_colour=card._colour;
        return *this;
    }
    Card(const Card&& card)
    :_num(card._num)
    ,_colour(card._colour)
    {}
    Card(const Card& card)
    :_num(card._num)
    ,_colour(card._colour)
    {}

    NumType GetNum()const{return _num;}
    ColourType GetColour()const{return _colour;}
protected:
    //用char一个字节来表示卡牌的点数和花色
    NumType _num;
    ColourType _colour;
};

//公共函数
namespace CARD{

inline void PrintNum(const NumType&);
inline void PrintColour(const ColourType&);

}//end of CARD

namespace CARD{

inline void PrintColour(const NumType&colour){
        if(colour==SUITS_SPADE){
            cout<<"\033[34m♠\033[0m";
        }else if(colour==SUITS_CLUBS){
            cout<<"\033[31m♦\033[0m";
        }else if(colour==SUITS_HEARTS){
            cout<<"\033[31m♥\033[0m";
        }else if(colour==SUITS_DIAMONDS){
            cout<<"\033[34m♣\033[0m";
        }
    }

inline void PrintNum(const ColourType&num){
     if(num==11){cout<<"J";}
    else if(num==12){cout<<"Q";}
    else if(num==13){cout<<"K";}
    else if(num==14){cout<<"A";}
    else {cout<<static_cast<int>(num);}
}    

}//end of CARD





#endif
