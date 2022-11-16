#include "Game.hpp"

#if 0 
template<>
PlayerPtr& Players::operator[](size_t x){
    x=x%size();
    return *(begin()+x);
}
#endif

void Game::CreatPlayers(){
    _players.reserve(_playersnum);
    string name="玩家 ";
    for(int i=0;i<_playersnum;++i){
        name.append(std::to_string(i));
        DeckCards* deckptr=_table.ReturnDeckPtr();
        PlayerPtr tmp(new Player(name,*deckptr));
        _players.push_back(tmp);
    }
}
void Game::CircleOfDealing(){}
void Game::CircleOfFlop(){}
void Game::CircleOfTurn(){}
void Game::CircleOfRiver(){}


void Game::GameStart(){
    CreatPlayers();
    cout<<">>创建玩家 "<<_playersnum<<"名"<<endl;
    int times=0;
    while(1){
        ++times;
         int ShuffleTimes=1;
        _table.ShuffleDeck(ShuffleTimes);
        cout<<">>洗牌 "<<ShuffleTimes<<"次"<<endl;
        cout<<">>Start Game "<<times<<endl;
        for(auto &rc:_players){
            rc.get()->AutoGetCardsSafe();
            cout<<">>发牌给 "<<rc.get()->GetName()<<endl;
        }
        for(auto &rc:_players){
            rc.get()->AutoGetCardsSafe();
            cout<<">>发牌给 "<<rc.get()->GetName()<<endl;
        }
        //发牌圈
        CircleOfDealing();

        //翻牌圈
        _table.AutoSendToPublicCards();    
        _table.ShowPublicCards(); 
        SetAllPlayerType();
        CircleOfFlop();

        //转牌圈
        _table.AutoSendToPublicCards();
        _table.ShowPublicCards();
        SetAllPlayerType();
        CircleOfTurn();
        
        //河牌圈
        _table.AutoSendToPublicCards();
        _table.ShowPublicCards();
        SetAllPlayerType();
        CircleOfRiver();

        for(auto &rp:_players){
            rp.get()->ShowHandCards();
            rp.get()->ShowType();
        }

        int TmpCin;
        cin>>TmpCin;
        if(TmpCin==1){break;}
    }
}



//将所有玩家的手牌和桌上的公共牌组合
//设置所有玩家的Type
void Game::SetAllPlayerType(){
    if(_table.ReturnPublicCardsPtr()->GetSize()<3){
        cerr<<"Game::SetAllPlayerType PublicCards.size()<3 \n";
        exit(1);
    }
    for(auto &rp:_players){
        Cards Ltmp=rp.get()->ReturnHandCards();
        Cards Rtmp=_table.ReturnPublicCards();
        Cards type=GROUP_CARDS::CardsAddCards(Ltmp,Rtmp);
        rp.get()->_type=TYPE::GainType(type);
    }
}

