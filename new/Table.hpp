#ifndef _CTL_TABLE_HPP_
#define _CTL_TABLE_HPP_

#include "PublicCards.hpp"
#include "Chip.hpp"
class Table
{
public:
    Table(int smallblind=10); 
    ~Table() {}
    //洗牌
    void ShuffleDeck(int times=1);
    //重置卡组发牌位
    void ResetSend(){_deck.ResetSend();}
    //重置公共牌
    void ResetPublicCards(){_publiccards.CleanCards();}
    DeckCards* ReturnDeckPtr(){return &_deck;}
    PublicCards* ReturnPublicCardsPtr(){return &_publiccards;}
    Cards ReturnPublicCards(){return _publiccards.ReturnCards();}
    //安全的给公共牌发牌
    void AutoSendToPublicCards(){_publiccards.AutoGetSafe();}
    //展示公共牌
    void ShowPublicCards();
private:
    //使用的卡组
    DeckCards _deck;
    //公共牌
    PublicCards _publiccards;
public:
    //奖池
    Jackpot _jackpot;
    int _smallblind;
};





#endif
