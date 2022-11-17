#ifndef __CTL_POKER_HPP__
#define __CTL_POKER_HPP__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <cstdint>  

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::sort;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;

enum Suits{
    SUITS_SPADE,//♠
    SUITS_HEARTS,//♥
    SUITS_DIAMONDS,//♣
    SUITS_CLUBS//♦
};

enum TypeCards:int{
    HIGH_CARD=1,
    ONE_PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

class Card
{
public:
    int _num;//点数(1-13:2-A)
    int _colour;//花色
   
public:
    Card(int num=0,int colour=0)
    :_num(num)
    ,_colour(colour){}
    ~Card(){}
    Card& operator=(const Card&);
    void Print_Card()const;
};

class Deck
{
public:
    /* data */
    vector<Card> _Deck;
    int _used;
    int _surplus;
public:
    Deck()
    :_used(0)
    ,_surplus(52)
    ,_Deck()
    {}
    ~Deck(){}
    void Creat_Deck();//新建一个52张的卡组
    void Print_Deck()const;//打印整个卡组
    void Shuffle_Deck(int times=1);//洗牌
    void Reset_Deck();//重置发牌位
    Card Send_Card();//发牌
};

class Player
{
public:
    vector<Card> _hands;//手牌
    vector<Card> _level;//目前最大牌型的组合
    string _name;//玩家名字
    int _type;//_level的牌型
    int _table_num;//座次
    int _chips;//所剩的筹码
    int _bet;//已下注的筹码数
    bool _alive;//是否存活
public:
    Player(string name="玩家",int table_num=0,int chips=2000)
    :_hands()
    ,_level()
    ,_name(name)
    ,_type(0)
    ,_table_num(table_num)
    ,_chips(chips)
    ,_bet(0)
    ,_alive(true)
    {}
    ~Player(){}
    void Reset_Hands(){_hands.clear();}//清空手牌；
    void Reset_Level(){_level.clear();_type=0;}//清空缓存的最大牌型
    void Reset_Alive(){_alive=true;}//置活
    void Reset_Bet(){_bet=0;}//清空下注
    void Reset_Chips(int chips=2000){_chips=chips;}//重新获得筹码
    void Out(){_alive=false;}//出局（置死）
    void Print_Player(int n=2);//展示玩家手牌

    int Add_Bet(int add,int max);//加注
    int Raise_Bet(int bet=10);//加注、返回_bet
    int Call_Bet(int max);//跟注，返回_bet
    int Check_Bet(){cout<<_name<<": 过\n";return _bet;}//跟注、返回_bet
    int Allin_Bet();//全压、返回_bet
    void Fold(){cout<<_name<<": 弃牌\n";Reset_Hands();Out();Reset_Bet();}//弃牌
    
    void Change_Name(string name){_name=name;}//更改名字
};

class Table{
public:
    vector<Card> _public_card;//公共牌
    int _max_bet;//桌上最大下注
    int _jackpot;//底池
    int _big_blind;//大盲注
    int _small_blind;//小盲注
public:
    Table(int maxbet=20,int bigblind=20,int smallblind=10)
    :_public_card()
    ,_max_bet(maxbet)
    ,_jackpot(0)
    ,_big_blind(bigblind)
    ,_small_blind(smallblind)
    {}
    ~Table(){}
    //清空，公共牌，底池，重置最大下注（默认大盲）
    void Reset_Table_All(){Reset_Table_Cards();Reset_Table_Jackpot();Reset_Table_MaxBet();}
    void Reset_Table_Cards(){_public_card.clear();}//清空公共牌
    void Reset_Table_Jackpot(){_jackpot=0;}//清空底池
    void Reset_Table_MaxBet(){_max_bet=_big_blind;}//重置最大下注（默认大盲）
    void Set_small_blind(int small){_small_blind=small;_big_blind=2*small;}//设置小盲,同时将大盲设置为两倍
    void Print_Table(int n=5);//展示公共牌

};

class Game{
private:
    vector<Player> _players;//玩家容器
    vector<Player> _winers;//获胜玩家
    Table _table;//牌桌
    Deck _deck;//牌堆
    int _players_num;//玩家总人数
    int _alive_num;//存活玩家数
    int _pos_dealer;//庄位的玩家所处容器的位置
public:
    Game(int player_num=2)
    :_players()
    ,_winers()
    ,_table()
    ,_deck()
    ,_players_num(player_num)
    ,_alive_num(player_num)
    ,_pos_dealer(0)
    {}
    ~Game(){}
    void Set_Players(int chips=2000,int pos=0);//初始化玩家
    void Get_Players_Leave();//为所有玩家获取当前的牌力
    void Game_Stand_Alone();
    void Game_Start();//开始游戏 
    void Window();
    bool Can_Bet(Player &player);

    void Reset_Game_Winer(){_winers.clear();}
    void Next_Game();//下一场对局
    
    void Send_Hands();//发手牌
    
    void Show_All_Players_Chips();
    void Show_Flop();//展示翻牌
    void Show_Turn();//展示转牌
    void Show_River();//展示河牌
    void Print_Game();//打印对局信息
    int Safe_Pos(int pos);//避免轮询越界


    void Test();//测试代码
};



void Window_Go_On();

void Print_Colour(const int colour);
void Print_Num(const int num);
void Print_Cards(const vector<Card> & cards,int Line_num=4);
void Print_Type(int Type);

vector<Card>  Type_for_Cards(vector<Card> pb_cards,vector<Card> hd_cards);
int  Type_for_5Cards(vector<Card> cards);
int  Type_for_Kind(const vector<Card>& cards);
bool Type_Straight(const vector<Card> &cards);
bool Type_Straight_min(const vector<Card> &cards);
bool Type_Flush(const vector<Card> & cards);


bool Compare_Num(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type(vector<Card> cardsA,vector<Card> cardsB,int type);
bool Compare_Type_HIGH_CARD(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_ONE_PAIR(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_TWO_PAIRS(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_THREE_OF_A_KIND(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_STRAIGHT(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_FLUSH(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_FULL_HOUSE(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_FOUR_OF_A_KIND(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_STRAIGHT_FLUSH(vector<Card> cardsA,vector<Card> cardsB);
bool Compare_Type_ROYAL_FLUSH(vector<Card> cardsA,vector<Card> cardsB);

void Sort_Cards_Num(vector<Card> & cards);
void Sort_Cards_Colour(vector<Card> & cards);

std::ostream & operator <<(std::ostream & os,TypeCards t);
#endif