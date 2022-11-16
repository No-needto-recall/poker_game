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
    //用于分析手牌与公共牌
    Cards ReturnHandCards()const{return  _handcards.ReturnCards();}
    string GetName(){return _name;}
private:
    string _name;
    HandCards _handcards;
public:
    Type _type;
};





#endif
