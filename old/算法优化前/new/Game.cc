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

void Game::SetLessPlayerCallOut(){
    for(auto &rp:_players){
        if(rp.get()->_chips.PeekBet()<_table._jackpot.PeekMaxBet()){
            rp.get()->SetCallOut();
        }
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
              SetLessPlayerCallOut();
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

void Game::GameHaveWiner(){
    ShowHand();
    GameSettle();
    GameOver();
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
        if(CircleOfPreflop()){
            GameHaveWiner();
           continue;
        }

        //翻牌圈
        cout<<">>翻牌圈"<<endl;
        _table.AutoSendToPublicCards();    
        _table.ShowPublicCards(); 
        SetAllPlayerType();
        if(CircleOfFlop()){
            GameHaveWiner();
            continue;
        }

        //转牌圈
        cout<<">>转牌圈"<<endl;
        _table.AutoSendToPublicCards();
        _table.ShowPublicCards();
        SetAllPlayerType();
        if(CircleOfTurn()){
            GameHaveWiner();
            continue;
        }
        
        //河牌圈
        cout<<">>河牌圈"<<endl;
        _table.AutoSendToPublicCards();
        _table.ShowPublicCards();
        SetAllPlayerType();
        if(CircleOfRiver()){
            GameHaveWiner();
            continue;
        }
        
        cout<<">>ShowHand"<<endl;
        ShowHand();
        GameSettle(); 
        GameOver();
        if(GAME::GameGoEnd()){
            break;
        }
    }
}

//展示所有存活玩家的手牌，同时将牌力较小的玩家Out
void Game::ShowHand(){
    Type tmp(_table.ReturnPublicCards());
    for(auto& rp:_players){
        if(rp.get()->IsAlive()){
            rp.get()->FinalShow();
            if(rp.get()->_type>=tmp){
                tmp=rp.get()->_type;
            }
        }
    }
    for(auto&rp:_players){
        if(rp.get()->IsAlive()){
            if(rp.get()->_type<tmp){
                rp.get()->SetPlayerOut();
                cout<<">>"<<rp.get()->GetName()<<" : Lose"<<endl;
                --_alivenum;
            }else{
                cout<<">>"<<rp.get()->GetName()<<" : Win"<<endl;
            }
        }
    }
}
//结算本局游戏
//所有存活的玩家平分奖池
void Game::GameSettle(){
    ChipType wintmp=_table._jackpot.PeekChip()/_alivenum;
    cout << ">>最终奖池 " << _table._jackpot.PeekChip() << endl;
    cout<<">>获胜玩家: "<<endl;
    for(auto&rp:_players){
        if(rp.get()->IsAlive()){
            rp.get()->FinalShow();
            rp.get()->_chips.GetChip(wintmp);
            _table._jackpot.UseChip(wintmp);
        }
    }
    cout<<">>结算游戏"<<endl;
    cout << ">>奖池剩余 " << _table._jackpot.PeekChip() << endl;
    for(auto&rp:_players){
        cout<<rp.get()->GetName()<<": ";
        if(rp.get()->IsAlive()){
            cout<<"+("<<wintmp<<") ";
        }
        cout<<rp.get()->_chips.PeekChip()<<endl;
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

bool GAME::GameGoEnd(){

    cout << ">>是否继续游戏(y/n):";
    while (1)
    {
        char tmp;
        system("stty -icanon");
        cin>>tmp;
        if(tmp=='y'||tmp=='Y'){
            system("stty icanon");
            cout<<endl;
            return false;
        }else if(tmp=='n'||tmp=='N'){
            system("stty icanon");
            cout<<endl;
            return true;}
        else{
            cout<<" 输入错误\b\b\b\b\b\b\b\b\b\b";
        }
    }
    
}