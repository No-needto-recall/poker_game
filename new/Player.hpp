#ifndef _CTL_PLAYER_HPP_
#define _CTL_PLAYER_HPP_

#include "HandCards.hpp"
#include "Table.hpp"
#include "Type.hpp"
#include "Chip.hpp"
#include <string>

using std::string;

class Player
{
public:
    Player(string name,DeckCards & deck) 
    :_name(name)
    ,_handcards(deck)
    ,_type()
    ,_chips()
    ,_alive(true)
    ,_call(false)
    {}
    ~Player() {}
    //安全的从卡组获得手牌
    void AutoGetCardsSafe(){_handcards.AutoGetSafe();}
    //清空手牌
    void CleanHandCards(){_handcards.CleanCards();}
    //重新为手牌绑定卡组
    void RebindDeck(DeckCards & deck){_handcards.RebindDeck(deck);}
    //展示手牌
    void ShowHandCards();
    //展示牌型
    void ShowType();
    //展示玩家名
    void ShowName();
    //获取玩家名
    string GetName(){return _name;}

    //将喊话设为虚函数，方便派生出不同类型玩家
    virtual void PlayerAction(Table& table)=0;

    //用于分析手牌与公共牌
    Cards ReturnHandCards()const{return  _handcards.ReturnCards();}

    //重置玩家标志位
    void ResetPlayerBool(){_alive=true;_call=false;}

    //玩家是否存活
    void SetPlayerIn(){_alive=true;}
    void SetPlayerOut(){_alive=false;}
    bool IsAlive(){return _alive;}
    //玩家是否喊话
    void SetCallIn(){_call=true;}
    void SetCallOut(){_call=false;}
    bool IsCall(){return _call;}

protected:
    string _name;
    HandCards _handcards;
    bool _alive;
    bool _call;
public:
    Chips _chips;
    Type _type;
};

class BotPlayer
:public Player
{
public:
    BotPlayer(string name,DeckCards &deck)
    :Player(name,deck){}
    ~BotPlayer(){}
    void PlayerAction(Table&table) override;
    //自动喊话逻辑
    //为真说明可以下注：返回usetmp（需要用多少筹码）
    //为假说明弃牌
    bool AutoAction(Jackpot & Jackpot,ChipType &usetmp);
    bool CanBet(Jackpot & Jackpot,ChipType &usetmp);
    bool CanCall(Jackpot & Jackpot,ChipType &usetmp);
    bool CanRaise(Jackpot & Jackpot,ChipType &usetmp);
};



#endif
