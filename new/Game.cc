#include "Game.hpp"

#if 1 
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
        PlayerPtr tmp(new BotPlayer(name,*deckptr));
        _players.push_back(tmp);
    }
}

bool Game::IsAllPlayerCall(){
    for(auto &rp:_players){
        if(rp.get()->IsCall()){continue;}
        else{return false;}
    }
    return true;
}
void Game::SetAllPlayerCallOut(){
    for(auto &rp:_players){
        rp.get()->SetCallOut();
    }
}

int Game::GetAlivePlayerNum(){
    int ret=0;
    for(auto &rp:_players){
        if(rp.get()->IsAlive()){
            ++ret;
        }
    }
    return  ret;
}

bool Game::CircleOfPreflop(){
    int tmppos=_dealerpos+1;
    _players[tmppos].get()->PlayerBlindBet(_table);
    ++tmppos;
    _players[tmppos].get()->PlayerBlindBet(_table);
    ++tmppos;
    while(1){
      auto & rp=  _players[tmppos];
      //存活且没有操作过
      //并且还有筹码（ALL IN 无需喊话）
      if (!(rp.get()->_chips.IsEmpty())&&rp.get()->IsAlive() && !(rp.get()->IsCall()))
      {
          if(1==_alivenum){return true;}
          if(rp.get()->PlayerAction(_table,_alivenum)){
              SetAllPlayerCallOut();
              rp.get()->SetCallIn();
          }
      }
      ++tmppos;
      if(IsAllPlayerCall()){break;}
    }
    SetAllPlayerCallOut();
    return false;
}
bool Game::CircleOfFlop(){
    //庄家的下一位开始喊话
    int tmppos=_dealerpos+1;
    while(1){
      auto & rp=  _players[tmppos];
      //存活且没有操作过
      //并且还有筹码（ALL IN 无需喊话）
      if (!(rp.get()->_chips.IsEmpty())&&rp.get()->IsAlive() && !(rp.get()->IsCall()))
      {
          if(1==_alivenum){return true;}
          if(rp.get()->PlayerAction(_table,_alivenum)){
              SetAllPlayerCallOut();
              rp.get()->SetCallIn();
          }
      }
      ++tmppos;
      if(IsAllPlayerCall()){break;}
    }
    SetAllPlayerCallOut();
    return false;
}
bool Game::CircleOfTurn(){
    return CircleOfFlop();
}
bool Game::CircleOfRiver(){
    return CircleOfFlop();
}


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
        CircleOfPreflop();

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
        rp.get()->SetCallOut();
        rp.get()->SetPlayerIn();
    }
    _alivenum=_playersnum;
    ++_dealerpos;
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
        TYPE::SwapCards(Rtmp,rp.get()->_type.ReturnCards());
    }

}

