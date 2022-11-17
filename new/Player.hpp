#ifndef _CTL_PLAYER_HPP_
#define _CTL_PLAYER_HPP_

#include "HandCards.hpp"
#include "Type.hpp"
#include <string>

using std::string;

class Player
{
public:
    Player(string name,DeckCards & deck) 
    :_name(name)
    ,_handcards(deck)
    ,_type()
    {}
    ~Player() {}
    void AutoGetCardsSafe(){_handcards.AutoGetSafe();}
    void CleanHandCards(){_handcards.CleanCards();}
    void RebindDeck(DeckCards & deck){_handcards.RebindDeck(deck);}
    void ShowHandCards();
    void ShowType();
    void ShowName();
    //将喊话设为虚函数，方便派生出不同类型玩家
    virtual void Call()=0;
    //用于分析手牌与公共牌
    Cards ReturnHandCards()const{return  _handcards.ReturnCards();}
    string GetName(){return _name;}
protected:
    string _name;
    HandCards _handcards;
public:
    Type _type;
};

class BotPlayer
:public Player
{
public:
    BotPlayer(string name,DeckCards &deck)
    :Player(name,deck){}


};



#endif
