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

