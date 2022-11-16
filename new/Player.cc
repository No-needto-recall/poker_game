#include "Player.hpp"

//展示手牌
void Player::ShowHandCards(){
    _handcards.show();
}

//展示最大组合
void Player::ShowType(){
    _type.Show();
}
