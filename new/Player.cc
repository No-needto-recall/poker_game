#include "Player.hpp"


void Player::ShowName(){
    cout<<GetName()<<endl;
}

//展示手牌
void Player::ShowHandCards(){
    _handcards.show();
}

//展示最大组合
void Player::ShowType(){
    _type.Show();
}

void Player::PlayerBlindBet(Table& table){

    Jackpot & jackpot=table._jackpot;
    ChipType OldJackpot = jackpot.PeekChip();
    ChipType OldMaxbet = jackpot.PeekMaxBet();
    ChipType Oldbet=_chips.PeekBet();
    ChipType smallblind=table._smallblind;
    string tmp=" : 压小盲注 ";
    ChipType usetmp=smallblind;
    if(OldMaxbet==smallblind){usetmp=2*smallblind;tmp=" : 压大盲注 ";}
    _chips.UseChip(usetmp);
    _chips.UpdateBet(usetmp);
    jackpot.GetChip(usetmp);
    jackpot.UpdateMaxBet(_chips.PeekBet());
    cout<<GetName()<<tmp<<Oldbet<<"->"<<usetmp
        <<" ("<<OldJackpot<<")-->("<<jackpot.PeekChip()<<")"<<endl;
}


bool BotPlayer::PlayerAction(Table& table,int & alivenum){
    bool retbool=true;
    SetCallIn();
    Jackpot & jackpot=table._jackpot;    
    Chips & chips=_chips;
    //Jackpot:底池,最大下注
    //Chips:筹码,当前下注
    ChipType usetmp(0);
    cout<<GetName()<<" : ";
    //判断是否下注
    if(AutoAction(jackpot,usetmp)){
        ChipType OldJackpot = jackpot.PeekChip();
        ChipType OldMaxbet = jackpot.PeekMaxBet();
        ChipType OldBet = chips.PeekBet();
        chips.UseChip(usetmp);
        chips.UpdateBet(usetmp);
        jackpot.GetChip(usetmp);
        jackpot.UpdateMaxBet(chips.PeekBet()); 
        if(OldMaxbet==jackpot.PeekMaxBet()){
            //跟注
            if(OldBet==chips.PeekBet()){
                cout<<" 过 (check) ";
                retbool=false;
            }else{
                if(chips.IsEmpty()){
                    cout<<"ALL IN ";
                }
                cout << "跟注 (Call) ";
                cout << OldBet << "->" << chips.PeekBet();
            }
        }else{
            if(chips.IsEmpty()){
                cout << "ALL IN ";
            }
            cout<<"加注 (Raise) ";
            cout << OldBet << "->" << chips.PeekBet();
        }
        cout<<" ("<<OldJackpot
            <<")-->("<<jackpot.PeekChip()
            <<")";
    }else{
        cout<<"弃牌 (Fold) ";
        SetPlayerOut();
        --alivenum;
    }
    cout << endl;
    return retbool;
}

bool BotPlayer::AutoAction(Jackpot & jackpot,ChipType &usetmp){
    //什么情况下可以下注
    if (CanBet( jackpot,usetmp))
    {
        //能否跟注
        if(CanCall( jackpot,usetmp)){return true;}
        //能否加注
        if(CanRaise( jackpot,usetmp)){return true;}
    }
    //弃牌
    return false;
}

bool BotPlayer::CanBet(Jackpot & jackpot,ChipType &usetmp){
    return !_chips.IsEmpty();
}
bool BotPlayer::CanCall(Jackpot & jackpot,ChipType &usetmp){
    if (1)
    {
        usetmp=jackpot.PeekMaxBet()-_chips.PeekBet();
    }
    if(usetmp>_chips.PeekChip()){
        usetmp=_chips.PeekChip();
    }
    return true;
    
}
bool BotPlayer::CanRaise(Jackpot & jackpot,ChipType &usetmp){
    return false;
}
