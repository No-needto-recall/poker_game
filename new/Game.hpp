#ifndef _CTL_GAME_HPP_
#define _CTL_GAME_HPP_

#include "Table.hpp"
#include "Player.hpp"
#include <memory>

using std::shared_ptr;

using PlayerPtr=shared_ptr<Player>;
using Players=vector<PlayerPtr>;

template<>
PlayerPtr& vector<PlayerPtr>::operator[](size_t pos){
    pos=pos%size();
    return *(begin()+pos);
}


namespace GAME{
    Cards HandCardsAddPublicCards();
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


private:
    Players _players;
    Table _table;
    int _playersnum;

};

#endif
