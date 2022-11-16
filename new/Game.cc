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
    for(int i=0;i<_playersnum;++i){
        string name = "玩家 ";
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
        cout<<">>发牌圈"<<endl;
        CircleOfDealing();

        //翻牌圈
        cout<<">>翻牌圈"<<endl;
        _table.AutoSendToPublicCards();    
        _table.ShowPublicCards(); 
        SetAllPlayerType();
        CircleOfFlop();

        //转牌圈
        cout<<">>转牌圈"<<endl;
        _table.AutoSendToPublicCards();
        _table.ShowPublicCards();
        SetAllPlayerType();
        CircleOfTurn();
        
        //河牌圈
        cout<<">>河牌圈"<<endl;
        _table.AutoSendToPublicCards();
        _table.ShowPublicCards();
        SetAllPlayerType();
        CircleOfRiver();
        
        cout<<"展示"<<endl;
        for(auto &rp:_players){
            rp.get()->ShowName();
            rp.get()->ShowType();
            rp.get()->ShowHandCards();
        }
        GameOver();
        int TmpCin;
        cin>>TmpCin;
        if(TmpCin==1){break;}
    }
}

void Game::GameOver(){
    //重置桌子
    _table.ResetSend();
    _table.ShuffleDeck();
    _table.ResetPublicCards();
    //重置玩家
    for(auto &rp:_players){
        rp.get()->CleanHandCards();
        rp.get()->_type.ResetType();
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

