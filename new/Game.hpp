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
    Game(int playsnum=2)
    :_players()
    ,_table()
    ,_playersnum(playsnum)
    {}
    ~Game() {}
    void GameStart();

protected:
    void CreatPlayers();
    void SetAllPlayerType();
    void CircleOfDealing();
    void CircleOfFlop();
    void CircleOfTurn();
    void CircleOfRiver();
    void GameOver();
private:
    Players _players;
    Table _table;
    int _playersnum;

};

#endif
