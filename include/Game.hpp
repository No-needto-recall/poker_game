#ifndef _CTL_GAME_HPP_
#define _CTL_GAME_HPP_

#include "Table.hpp"
#include "BotPlayerLevel0.hpp"
#include <memory>
#include <cstdio>

using std::shared_ptr;
using std::cin;

using PlayerPtr=shared_ptr<Player>;
using Players=vector<PlayerPtr>;

namespace GAME{
    bool GameGoEnd();
}//end of GAME

class Game
{
public:
    Game(int playsnum=3,int smallblind=10)//默认玩家三人，小盲注10
    :_players()
    ,_table(smallblind)
    ,_playersnum(playsnum)
    ,_alivenum(_playersnum)
    ,_dealerpos(0)
    {}
    ~Game() {}
    void GameStart();

protected:
    void CreatPlayers();//创建玩家
    void SetAllPlayerType();//设置所有玩家的牌力
    bool CircleOfPreflop();//发牌圈
    bool CircleOfFlop();//翻牌圈
    bool CircleOfTurn();//转牌圈
    bool CircleOfRiver();//河牌圈
    void ShowHand();
    void GameSettle();
    void GameOver();
    void GameHaveWiner();
    bool IsAllPlayerCall();
    void SetAllPlayerCallOut();
    void SetLessPlayerCallOut();
    int GetAlivePlayerNum();

private:
    Players _players;
    Table _table;
    int _playersnum;
    int _alivenum;
    int _dealerpos;
};

#endif
