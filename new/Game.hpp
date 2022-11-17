#ifndef _CTL_GAME_HPP_
#define _CTL_GAME_HPP_

#include "Table.hpp"
#include "Player.hpp"
#include <memory>

using std::shared_ptr;
using std::cin;

using PlayerPtr=shared_ptr<Player>;
using Players=vector<PlayerPtr>;

namespace GAME{
    
}//end of GAME

class Game
{
public:
    Game(int playsnum=3,int smallblind=10)
    :_players()
    ,_table(smallblind)
    ,_playersnum(playsnum)
    ,_alivenum(_playersnum)
    ,_dealerpos(0)
    {}
    ~Game() {}
    void GameStart();

protected:
    void CreatPlayers();
    void SetAllPlayerType();
    bool CircleOfPreflop();
    bool CircleOfFlop();
    bool CircleOfTurn();
    bool CircleOfRiver();
    void ShowHand();
    void GameOver();
    bool IsAllPlayerCall();
    void SetAllPlayerCallOut();
    int GetAlivePlayerNum();

private:
    Players _players;
    Table _table;
    int _playersnum;
    int _alivenum;
    int _dealerpos;
};

#endif
