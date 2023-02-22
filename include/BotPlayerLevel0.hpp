#ifndef _CTL_BOTPLAYERLEVEL0_HPP_
#define _CTL_BOTPLAYERLEVEL0_HPP_

#include "Player.hpp"

class BotPlayerLevel0
{
public:
    BotPlayerLevel0() {}
    ~BotPlayerLevel0() {}

private:

};
class BotPlayer
:public Player
{
public:
    BotPlayer(string name,DeckCards &deck)
    :Player(name,deck){}
    ~BotPlayer(){}
    bool PlayerAction(Table&table,int & alivenum) override;
    //自动喊话逻辑
    //为真说明可以下注：返回usetmp（需要用多少筹码）
    //为假说明弃牌
    bool AutoAction(Jackpot & Jackpot,ChipType &usetmp);
    bool CanBet(Jackpot & Jackpot,ChipType &usetmp);
    bool CanCall(Jackpot & Jackpot,ChipType &usetmp);
    bool CanRaise(Jackpot & Jackpot,ChipType &usetmp);
};


#endif
