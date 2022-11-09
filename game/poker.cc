#include "poker.hpp"

//Card``````````````````````````````````

//单张卡牌的打印
void Card::Print_Card()const{
    cout<<" ___ \n| ";
    Print_Colour(_colour);
    cout<<" |\n";
    if(_num==9)
    {
        cout<<"|1 0|"<<endl;
    }else{
    cout<<"| ";
    Print_Num(_num);
    cout<<" |\n|___|"<<endl;
    }
}

//卡牌的赋值构造函数
Card& Card::operator=(const Card& card){
    this->_num=card._num;
    this->_colour=card._colour;
    return *this;
}

//Deck`````````````````````````````````
//新建52张卡组
void Deck::Creat_Deck(){
   _Deck.reserve(52);
   for(int colour=0;colour<4;++colour){
    for(int num=1;num<14;++num){
        _Deck.push_back(Card(num,colour));
    }
   } 
}

//打印卡组
void Deck::Print_Deck()const{
    Print_Cards(_Deck,4);
}

//洗牌,times:次数
void Deck::Shuffle_Deck(int times){
    random_device r;
    default_random_engine er(r());
    uniform_int_distribution<int> uniform_dist(0,51);
    uniform_int_distribution<int> uniform_dist2(25,51);
    srand(time(NULL));

    Card tmp;
    for(int j=0;j<times;++j){
#if 0
    for(int i=0;i<52;++i){
        tmp=_Deck[0];
        int mean=uniform_dist(er);
        _Deck[0]=_Deck[mean];
        _Deck[mean]=tmp;
    }
#endif
#if 0
    for(int i=0;i<26;++i){
        tmp=_Deck[i];
        int mean=uniform_dist2(er);
        _Deck[i]=_Deck[mean];
        _Deck[mean]=tmp;
    }
#endif
#if 1
    for(int i=52-1;i>=0;--i){
        tmp=_Deck[i];
        int ch=rand()%(i+1);
        _Deck[i]=_Deck[ch];
        _Deck[ch]=tmp;
    }
#endif
    }
#if 0
    tmp=_Deck.back();
    _Deck.pop_back();
    _Deck.insert(_Deck.begin(),tmp);

#endif
}

//发牌
Card Deck::Send_Card(){
    --_surplus;
    return _Deck[_used++];
}

//重置发牌位，并未洗牌
void Deck::Reset_Deck(){
    _used=0;
    _surplus=52;
}


//Player `````````````````````````````````````````````

//打印玩家手牌
void Player::Print_Player(int n){
    Print_Cards(_hands,n);
}

//跟注，返回_bet
int Player::Call_Bet(int max){
    int add=max-_bet;
    _chips-=add;
    if(add!=0){
        cout << _name << ": 跟注 "
             << "(" << max << ")  "
             << _bet << "+" << add << endl;
    }else{
        cout << _name << ": 过(" << max << ")" << endl;
    }
    _bet=max;
    return add;
}

//加注,需确保0<=add<=chips
int Player::Add_Bet(int add,int max){
    if (add == 0)
    {
        cout << _name << ": 过(" << _bet << ")" << endl;
    }
    else
    {
        //说明有下注
        if (add == _chips)
        {
            cout << _name << ": ALL IN (" << _bet << ")" << endl;
        }
        else
        {
            if (_bet + add == max)
            {
                cout << _name << ": 跟注"<< "(" << max << ")  "<< _bet << "+" << add << endl;
            }
            else
            {
                cout << _name << ": 加注" << add << "至" << _bet + add << endl;
            }
        }
    }
    _bet += add;
    _chips -= add;
    return _bet;
}

//加注、返回已下注的筹码
int Player::Raise_Bet(int bet){
    _bet+=bet;
    _chips-=bet;
    cout<<_name<<": 加注至"<<_bet
               <<"(+"<<bet<<")"<<endl;
    return _bet; 
}
//全压、返回已下注筹码
int Player::Allin_Bet(){
    _bet+=_chips;
    _chips=0;
    cout<<_name<<": ALL IN ("<<_bet
        <<")"<<endl;
    return _bet;
}

//Table  ``````````````````````````````````````````````

void Table::Print_Table(int n){
    Print_Cards(_public_card,n);
}

//Game ``````````````````````````````````````````````
//初始化玩家
void Game::Set_Players(int chips,int pos){
    for(int i=0;i<_players_num;++i){
        string name = "玩家";
        name.append(std::to_string(i+1));
        Player p1(name,i,chips);
        _players.push_back(p1);
    }
}

//当前对局结束后的处理
void Game::Next_Game(){
    int i=0;
    //清空获胜玩家
    Reset_Game_Winer();
    //换庄位
    ++_pos_dealer;
    if(_pos_dealer>=_players_num){_pos_dealer=0;}
    //重置卡组后洗牌
    _deck.Reset_Deck();
    _deck.Shuffle_Deck(1);
    //重置牌桌
    _table.Reset_Table_MaxBet();
    _table.Reset_Table_Cards();
    //重置玩家
    for(auto &c:_players){
        //重置存活
        c.Reset_Alive();
        //清空下注
        c.Reset_Bet();
        //清空手牌,牌型
        c.Reset_Hands();
        c.Reset_Level();
    }
    //cout<<_pos_dealer<<endl;
}


void Game::Game_Start(){
}

int Game::Safe_Pos(int pos){
    if(pos>=_players_num){pos=pos%_players_num;}
    return pos;
}

void Game::Game_Stand_Alone(){
    int ownP=-1;//单人位置
    _deck.Creat_Deck();
    _deck.Shuffle_Deck(); //洗牌
    cout << "单人游戏模式  开始" << endl;
    int time=0;
    vector<string> winersname;
    map<int,int> winermap;
    while (1)
    {
        int pos_now = Safe_Pos(_pos_dealer+1);
        if(pos_now>=_players_num){pos_now=0;}
        //大小盲下盲注;
        _table._jackpot+=_players[pos_now++].Raise_Bet(_table._small_blind);
        pos_now=Safe_Pos(pos_now);
        _table._jackpot+=_players[pos_now++].Raise_Bet(_table._big_blind);
        pos_now=Safe_Pos(pos_now);
        //发玩家手牌；
        Send_Hands();
        cout<<"········"<<endl;
        cout<<"|发牌圈|"<<endl;
        cout<<"········"<<endl;
        //枪手操作 
        //判读是否是人机
        while(pos_now!=ownP&&pos_now!=Safe_Pos(_pos_dealer+1))
        {
            //人机策略操作
            //无脑跟注
            if(Can_Bet(_players[pos_now])){
                int add=_table._max_bet-_players[pos_now]._bet;
                _table._jackpot+=_players[pos_now].Add_Bet(add,_table._max_bet);
            }else{
                _table._jackpot+= _players[pos_now].Allin_Bet();
            }
            if(pos_now==Safe_Pos(_pos_dealer+2)){
                break;
            }
            ++pos_now;
            pos_now=Safe_Pos(pos_now);
        }
        //翻牌圈
        cout<<"········"<<endl;
        cout<<"|翻牌圈|"<<endl;
        cout<<"········"<<endl;
        Print_Game();
        Show_Flop();
        Get_Players_Leave();
        pos_now=Safe_Pos(_pos_dealer+1);
        while(pos_now!=ownP)
        {
            //人机策略操作
            //无脑跟注
            if(Can_Bet(_players[pos_now])){
                _table._jackpot+=_players[pos_now].Call_Bet(_table._max_bet);
            }else{
                _table._jackpot+= _players[pos_now].Allin_Bet();
            }
            ++pos_now;
            pos_now=Safe_Pos(pos_now);
            if(pos_now==Safe_Pos(_pos_dealer+1)){
                break;
            }
        }

        //转牌圈
        cout<<"········"<<endl;
        cout<<"|转牌圈|"<<endl;
        cout<<"········"<<endl;
        Print_Game();
        Show_Turn();
        Get_Players_Leave();
        pos_now=Safe_Pos(_pos_dealer+1);
        
        while(pos_now!=ownP)
        {
            //人机策略操作
            //无脑跟注
            if(Can_Bet(_players[pos_now])){
                _table._jackpot+=_players[pos_now].Call_Bet(_table._max_bet);
            }else{
                _table._jackpot+= _players[pos_now].Allin_Bet();
            }
            ++pos_now;
            pos_now=Safe_Pos(pos_now);
            if(pos_now==Safe_Pos(_pos_dealer+1)){
                break;
            }

        }
        //河牌圈
        cout<<"········"<<endl;
        cout<<"|河牌圈|"<<endl;
        cout<<"········"<<endl;
        Print_Game();
        Show_Turn();
        Get_Players_Leave();
        pos_now=Safe_Pos(_pos_dealer+1);
        while(pos_now!=ownP)
        {
            //人机策略操作
            //无脑跟注
            if(Can_Bet(_players[pos_now])){
                _table._jackpot+=_players[pos_now].Call_Bet(_table._max_bet);
            }else{
                _table._jackpot+= _players[pos_now].Allin_Bet();
            }
            ++pos_now;
            pos_now=Safe_Pos(pos_now);
            if(pos_now==Safe_Pos(_pos_dealer+1)){
                break;
            }
        }
       
        //存活玩家比牌，公布胜负
        cout <<"··········" << endl;
        cout <<"|存活玩家|"<<endl;
        cout <<"··········" << endl;
        vector<Card> win=_table._public_card;
        int type=Type_for_5Cards(win);
        int winplayer=0;
        for(int i=0;i<_players_num;++i)
        {
            //如果存活
            if(_players[i]._alive){
                //打印手牌
                cout<<_players[i]._name<<" 牌型: ";
                Print_Type(_players[i]._type);
                cout<<endl;
                _players[i].Print_Player();
                Print_Cards(_players[i]._level,5);
                //找出最大的牌型
                if(type<=_players[i]._type){

                    if(type==_players[i]._type&&Compare_Type(_players[i]._level,win,type)){
                        win=_players[i]._level;
                        type=_players[i]._type;
                        winplayer=i;
                    }else{
                        win=_players[i]._level;
                        type=_players[i]._type;
                        winplayer=i;
                    }
                }
            }
        }
        //获得最大牌型
        //但存在牌型相同且大小也相同的情况
       _winers.push_back(_players[winplayer]);
       for(int i=0;i<_players_num;++i){
        if(i!=winplayer&&_players[i]._alive)
        {
            if(type==_players[i]._type){
                if(Compare_Type(_players[i]._level,win,type)){
                if(Compare_Num(_players[i]._level,win)){
                    _winers.push_back(_players[i]);
                }
                }
           }
        }
       }
       cout << "········" << endl;
       cout << "|公共牌|" << endl;
       cout << "········" << endl;
       _table.Print_Table();
       cout << "··········" << endl;
       cout << "|获胜玩家|" << endl;
       cout << "··········" << endl;
       for (auto &c : _winers)
       {
           cout << "\n赢家:" << c._name << "  牌型:";
           Print_Type(c._type);
           cout << endl;
           c.Print_Player();
           Print_Cards(c._level, 5);
           cout << endl;
        }
        //结算奖励
        int winbet=_table._jackpot/_winers.size();
        for(auto &c:_winers){
            
            //winersname.push_back(c._name);
            ++winermap[c._table_num];
        
            _table._jackpot-=winbet;
            cout<<c._name<<": "<<c._chips<<"+"<<winbet;
            _players[c._table_num]._chips+=winbet;
            cout<<" 剩余筹码: "<<c._chips<<endl;
        }
        Print_Game();
        Show_All_Players_Chips();
        if(time++>10){
            int popw;
            time=0;

            for (auto &c : winermap)
            {
                cout << c.first << ":";
                for (int i = 0; i < c.second; ++i)
                {
                    cout << "|";
                }
                cout << c.second;
                cout << endl;
            }

            cin>>popw;
            if(popw==2){
                break;
            }
        //Window_Go_On();
        }
        Next_Game();
    }
#if 0
    for(auto &c:winermap){
        cout<<c.first<<":";
        for(int i=0;i<c.second;++i){
            cout<<"|";
        }
        cout<<c.second;
        cout<<endl;
    }
#endif

}

void Game::Test(){
   _deck.Creat_Deck();
   _deck.Shuffle_Deck();
   int time=0;
   map<int,int>winermap;
   map<int ,int>typemap;
   while (1)
   {
    int pos_now=Safe_Pos(_pos_dealer+1);
    Send_Hands();
//倒置发牌
#if 0
        auto &pc = _players;
        for (int i = pc.size() - 1; i >= 0; --i)
        {
            pc[i]._hands.push_back(_deck.Send_Card());
        }
        for (int i = pc.size() - 1; i >= 0; --i)
        {
            pc[i]._hands.push_back(_deck.Send_Card());
        }

#endif
        _table._public_card.push_back(_deck.Send_Card());
        _table._public_card.push_back(_deck.Send_Card());
        _table._public_card.push_back(_deck.Send_Card());
        _table._public_card.push_back(_deck.Send_Card());
        _table._public_card.push_back(_deck.Send_Card());
        Get_Players_Leave();
        vector<Card> win = _table._public_card;
        int type=Type_for_5Cards(win);
        int winplayer=0;
        //_table.Print_Table();
        for(int i=0;i<_players_num;++i)
        {
            //如果存活
            if(_players[i]._alive){
                //打印手牌
#if 0
                cout<<_players[i]._name<<" 牌型: ";
                Print_Type(_players[i]._type);
                cout<<endl;
                _players[i].Print_Player();
                Print_Cards(_players[i]._level,5);
#endif
                //找出最大的牌型
                if(type<=_players[i]._type){

                    if(type==_players[i]._type&&Compare_Type(_players[i]._level,win,type)){
                        win=_players[i]._level;
                        type=_players[i]._type;
                        winplayer=i;
                    }else{
                        win=_players[i]._level;
                        type=_players[i]._type;
                        winplayer=i;
                    }
                }
            }
        }
        //获得最大牌型
        //但存在牌型相同且大小也相同的情况
       _winers.push_back(Player(_players[winplayer]));
       for(int i=0;i<_players_num;++i){
        if(i!=winplayer&&_players[i]._alive)
        {
            if(type==_players[i]._type){
                if(Compare_Type(_players[i]._level,win,type)){
                if(Compare_Num(_players[i]._level,win)){
                    _winers.push_back(_players[i]);
                }
                }
           }
        }
       }
       for (auto &c : _winers)
       {
           ++winermap[c._table_num];
           ++typemap[c._type];
#if 0
           cout << "\n赢家:" << c._name << "  牌型:";
           Print_Type(c._type);
           cout << endl;
           c.Print_Player();
           Print_Cards(c._level, 5);
           cout << endl;
#endif
       }

       if (time++ >= 100)
       {
           int popw;
           time = 0;

#if 0
           auto pmap = winermap;
           for (auto &c : pmap)
           {
               cout << c.first << ":";
           }
           cout << endl;
           int down = 1;
           while (1)
           {
               for (auto &c : pmap)
               {
                   if (c.second != 0)
                   {
                       cout << "|_|";
                       --c.second;
                   }
                   else
                   {
                       cout << "   ";
                   }
               }
               cout << endl;
               for (auto &c : pmap)
               {
                   if (c.second != 0)
                   {
                       down = 1;
                   }
                   else
                   {
                       down = 0;
                   }
               }
               if (down == 0)
               {
                   break;
               }
           }
#endif
#if 1
           for (auto &c : winermap)
           {
               cout <<"玩家"<< c.first+1 << "胜出:";
               for (int i = 0; i < c.second; ++i)
               {
                   cout << "|";
               }
               cout << c.second;
               cout << endl;
           }
           cout<<endl;
           for (auto &c : typemap)
           {
               Print_Type(c.first);
               for (int i = 0; i < c.second; ++i)
               {
                   cout << "|";
               }
               cout << c.second;
               cout << endl;
           }
#endif
           cin >> popw;
           if (popw == 2)
           {
               break;
           }
       }
       Next_Game();
   }
}


void Game::Show_All_Players_Chips(){
    for(auto & c:_players){
        cout<<c._name<<": 剩余筹码"<<c._chips<<endl;
    }
}


void Game::Get_Players_Leave(){
    for(auto &c:_players){
        c.Reset_Level();
        c._level=Type_for_Cards(_table._public_card,c._hands);
        c._type=Type_for_5Cards(c._level);
    }
}

void Game::Send_Hands(){
    auto &c =_players;
    for(int i=Safe_Pos(_pos_dealer+1);;){
        c[i++]._hands.push_back(_deck.Send_Card());
        i = Safe_Pos(i);
        if(i==Safe_Pos(_pos_dealer+1)){break;}
    }
    for(int i=Safe_Pos(_pos_dealer+1);;){
        c[i++]._hands.push_back(_deck.Send_Card());
        i=Safe_Pos(i);
        if(i==Safe_Pos(_pos_dealer+1)){break;}
    }
}

bool Game::Can_Bet(Player &player){
    return player._chips+player._bet>=_table._max_bet;
}
void Game::Show_Flop(){
    //给牌桌发牌
    _deck.Send_Card();
    _table._public_card.push_back(_deck.Send_Card());
    _deck.Send_Card();
    _table._public_card.push_back(_deck.Send_Card());
    _deck.Send_Card();
    _table._public_card.push_back(_deck.Send_Card());
    //_table.Print_Table();
}

void Game::Show_Turn(){
    //给牌桌发牌
    _deck.Send_Card();
    _table._public_card.push_back(_deck.Send_Card());
    //_table.Print_Table();
}

void Game::Show_River(){
    //给牌桌发牌
    _deck.Send_Card();
    _table._public_card.push_back(_deck.Send_Card());
    //_table.Print_Table();
}

void Game::Print_Game(){
    cout<<"奖池: "<<_table._jackpot
        <<"  最大下注: "<<_table._max_bet
        <<" 剩余玩家数: "<<_alive_num<<endl;
}

void Game::Window(){

}

//公开的普通函数``````````````````````````````````

//打印卡牌的花色
void Print_Colour(const int colour){
    if(colour==SUITS_SPADE){
        cout<<"\033[34m♠\033[0m";
    }else if(colour==SUITS_CLUBS){
        cout<<"\033[31m♦\033[0m";
    }else if(colour==SUITS_HEARTS){
        cout<<"\033[31m♥\033[0m";
    }else if(colour==SUITS_DIAMONDS){
        cout<<"\033[34m♣\033[0m";
    }
}

//打印卡牌数号
void Print_Num(const int num){
    if(num==10){cout<<"J";}
    else if(num==11){cout<<"Q";}
    else if(num==12){cout<<"K";}
    else if(num==13){cout<<"A";}
    else {cout<<num+1;}
}

//打印卡牌堆，可以指定每行打印多少卡牌
void Print_Cards(const vector<Card> & cards,int Line_num){
    for(int i=0;i<cards.size();i+=Line_num ){
    for(int Line=0;Line<Line_num&&Line+i<cards.size();++Line){
        cout<<" ___  ";
    }
    cout<<endl;
    for(int Line=0;Line<Line_num&&Line+i<cards.size();++Line){
        cout<<"| ";
        Print_Colour(cards[i+Line]._colour);
        cout<<" | ";
    }
    cout<<endl;
    for (int Line = 0; Line < Line_num&&Line+i<cards.size(); ++Line)
    {
        if(cards[i+Line]._num!=9){
        cout<<"| ";
        Print_Num(cards[i+Line]._num);
        cout<<" | ";}
        else{
            cout<<"|1 0| ";
        }
    }
    cout<<endl;
    for(int Line=0;Line<Line_num&&Line+i<cards.size();++Line){
        cout<<"|___| ";
    }
    cout<<endl;
    }
}

//按照点数排序(从小到大)
void Sort_Cards_Num(vector<Card> &cards){
    sort(cards.begin(),cards.end(),[](Card a,Card b){
        if(a._num==b._num){
            return a._colour<b._colour;
        }
        return a._num<b._num;
    });
}

//按照花色排序(从小到大)
void Sort_Cards_Colour(vector<Card> &cards){
    sort(cards.begin(),cards.end(),[](Card a,Card b){
        if(a._colour==b._colour){
            return a._num<b._num;
        }
        return a._colour<b._colour;
    });
}

//返回最大的组合
vector<Card> Type_for_Cards(vector<Card> pb_cards,vector<Card> hd_cards){
    vector<Card> one_kind;
    vector<Card> max;
    int type=0;
    one_kind.reserve(5);
    if(pb_cards.size()==3){
        one_kind=pb_cards;
        for(auto &hc:hd_cards){
            one_kind.push_back(hc);
        }
        return one_kind;
    }
    if(pb_cards.size()==4){
        one_kind=pb_cards;
        one_kind.push_back(hd_cards.front());
        max=one_kind;
        type=Type_for_5Cards(one_kind);
        Card tmp;
        for(int i=0;i<5;++i){
            tmp=one_kind[i];
            one_kind[i]=hd_cards.back();
            int tmp_type=Type_for_5Cards(one_kind);
            if(tmp_type>type){
                type=tmp_type;
                max=one_kind;
            }else if(tmp_type==type){
                if(Compare_Type(one_kind,max,type)){max=one_kind;}
            }
            one_kind[i]=tmp;
        }
        return max;
    }
    if(pb_cards.size()==5){
        //不替换
        one_kind=pb_cards;
        max=one_kind;
        type=Type_for_5Cards(one_kind);
        Card tmp;
        for(int i=0;i<5;++i){
            //替换第一张手牌
            tmp=one_kind[i];
            one_kind[i]=hd_cards.front();
            int tmp_type=Type_for_5Cards(one_kind);
            if (tmp_type>type)
            {
                type=tmp_type;
                max=one_kind;
            }else if(tmp_type==type){
                if(Compare_Type(one_kind,max,type)){max=one_kind;}
            }
            one_kind[i]=tmp;
            //替换第二张手牌
            one_kind[i]=hd_cards.back();
            tmp_type=Type_for_5Cards(one_kind);
            if (tmp_type>type)
            {
                type=tmp_type;
                max=one_kind;
            }else if(tmp_type==type){
                if(Compare_Type(one_kind,max,type)){max=one_kind;}
            }
            one_kind[i]=tmp;
        }
        Card tmp2;
        for(int i=0;i<4;++i){
            //替换两种牌的情况
            for(int j=i+1;j<5;++j){
                tmp=one_kind[i];
                tmp2=one_kind[j];
                one_kind[i]=hd_cards.front();
                one_kind[j]=hd_cards.back();
                int tmp_type=Type_for_5Cards(one_kind);
                if(tmp_type>type){
                    type=tmp_type;
                    max=one_kind;
                }else if(tmp_type==type){
                if(Compare_Type(one_kind,max,type)){max=one_kind;}
                }
                one_kind[i]=tmp;
                one_kind[j]=tmp2;
            }
        }
        return max;
    }

}

//5张牌的类型
int Type_for_5Cards(vector<Card> cards){
    if(cards.size()!=5){
        return -1;
    }
    //排序只针对5张牌
    Sort_Cards_Num(cards);
    int Type=0;
    //对有序5张牌分析
    if(Type_Straight(cards)){
        if(Type_Flush(cards)){
            if(cards.back()._num==13){ Type= ROYAL_FLUSH;}
            else{ Type= STRAIGHT_FLUSH;}
        }else{Type= STRAIGHT;}
    }else if(Type_Flush(cards)){
        Type=FLUSH;
    }
    int TypeK=Type_for_Kind(cards);
    if(Type<TypeK){Type=TypeK;}
    return Type;
}

//单独判断最小的顺子A2345
bool Type_Straight_min(const vector<Card>& cards){
    int num=1;
    for(int i=0;i<4;++i){
        if(cards[i]._num==num){
            ++num;
            continue;
        }else{
            return false;
        }
    }
    if(cards[4]._num==13){
        return true;
    }else{
        return false;
    }
}

//判断顺子（5张牌）
bool Type_Straight(const vector<Card> & cards){
    if(Type_Straight_min(cards)){
        return true;
    }
    if(cards.back()._num-cards.front()._num!=4){
        return false;
    }
    set<int> Cnum;
    for(auto &c:cards){
        Cnum.insert(c._num);
    }
    if(Cnum.size()==5){
        return true;
    }else{
        return false;
    }
}

//判断同花 (5张牌)
bool Type_Flush(const vector<Card>& cards){
    map<int,int> Mcolour;
    for(auto &c:cards){
        ++Mcolour[c._colour];
    }
    for(auto &m:Mcolour){
        if(m.second==5){
            return true;
        }
    }
    return false;
}

//判断一对、两对、三条、葫芦、四条
int Type_for_Kind(const vector<Card>& cards){
    map<int,int> Mcard;
    for(auto &c:cards){
        ++Mcard[c._num];
    }
    int pair=0;
    int three=0;
    for(auto &m:Mcard){
        if(m.second==4){return FOUR_OF_A_KIND;}
        if(m.second==3){++three;}
        if(m.second==2){++pair;}
    }
    if(three==1){
        if(pair==1){return FULL_HOUSE;}
        else{return THREE_OF_A_KIND;}
    }else{
        if(pair==0){return HIGH_CARD;}
        else if(pair==1){return ONE_PAIR;}
        else {return TWO_PAIRS;}
    }
}

//打印牌型
void Print_Type(int Type){
    switch (Type)
    {
    case HIGH_CARD:cout<<HIGH_CARD; break;
    case ONE_PAIR:cout<<ONE_PAIR; break;
    case TWO_PAIRS:cout<<TWO_PAIRS; break;
    case THREE_OF_A_KIND:cout<<THREE_OF_A_KIND; break;
    case STRAIGHT:cout<<STRAIGHT; break;
    case FLUSH:cout<<FLUSH; break;
    case FULL_HOUSE:cout<<FULL_HOUSE; break;
    case FOUR_OF_A_KIND:cout<<FOUR_OF_A_KIND; break;
    case STRAIGHT_FLUSH:cout<<STRAIGHT_FLUSH; break;
    case ROYAL_FLUSH:cout<<ROYAL_FLUSH; break;
    default:
        break;
    }
}

//重载牌型枚举
std::ostream & operator <<(std::ostream & os,TypeCards t){
    switch (t)
    {
    case HIGH_CARD:os<<"高牌 (High Card)"; break;
    case ONE_PAIR:os<<"一对 (One Pair)"; break;
    case TWO_PAIRS:os<<"两对 (Two Pairs)"; break;
    case THREE_OF_A_KIND:os<<"三条 (Three Of A Kind)"; break;
    case STRAIGHT:os<<"顺子 (Straight)"; break;
    case FLUSH:os<<"同花 (Flush)"; break;
    case FULL_HOUSE:os<<"葫芦 (Full House)"; break;
    case FOUR_OF_A_KIND:os<<"四条 (Four Of A Kind)"; break;
    case STRAIGHT_FLUSH:os<<"同花顺 (Straight Flush)"; break;
    case ROYAL_FLUSH:os<<"皇家同花顺 (Royal Flush)"; break;
    
    default:os.setstate(std::ios_base::failbit);
    }
}

//判断A和B单数号是否全相同
bool Compare_Num(vector<Card> cardsA,vector<Card> cardsB){
    Sort_Cards_Num(cardsA);
    Sort_Cards_Num(cardsB);
    for(int i=0;i<5;++i){
        if(cardsA[i]._num!=cardsB[i]._num){
            return false;
        }
    }
    return true;
}

//指定类型比较 A>=B
bool Compare_Type(vector<Card> cardsA,vector<Card> cardsB,int type){
    switch (type)
    {
    case HIGH_CARD:return  Compare_Type_HIGH_CARD(cardsA,cardsB);break;
    case ONE_PAIR:return Compare_Type_ONE_PAIR(cardsA,cardsB); break;
    case TWO_PAIRS:return Compare_Type_TWO_PAIRS(cardsA,cardsB);break;
    case THREE_OF_A_KIND:return Compare_Type_THREE_OF_A_KIND(cardsA,cardsB); break;
    case STRAIGHT:return Compare_Type_STRAIGHT(cardsA,cardsB); break;
    case FLUSH:return Compare_Type_FLUSH(cardsA,cardsB); break;
    case FULL_HOUSE:return Compare_Type_FULL_HOUSE(cardsA,cardsB); break;
    case FOUR_OF_A_KIND:return Compare_Type_FOUR_OF_A_KIND(cardsA,cardsB); break;
    case STRAIGHT_FLUSH:return Compare_Type_STRAIGHT_FLUSH(cardsA,cardsB); break;
    case ROYAL_FLUSH:return Compare_Type_ROYAL_FLUSH(cardsA,cardsB); break;
    default:
        break;
    }
    return false;
}

//高牌比较,A>=B
bool Compare_Type_HIGH_CARD(vector<Card> cardsA,vector<Card> cardsB){
    Sort_Cards_Num(cardsA);
    Sort_Cards_Num(cardsB);
    for(int i=4;i>=0;--i){
        if(cardsA[i]._num!=cardsB[i]._num){
            return cardsA[i]._num>cardsB[i]._num;
        }
    }
    return true;
}
//一对比较,A>=B
bool Compare_Type_ONE_PAIR(vector<Card> cardsA,vector<Card> cardsB){
    map<int,int> mA;
    map<int,int> mB;
    for(int i=0;i<5;++i){
        ++mA[cardsA[i]._num];
        ++mB[cardsB[i]._num];
    }
    int pairA=0;int pairB=0;
    for(auto &ca:mA){
        if(ca.second==2){pairA=ca.first;}
    }
    for(auto &cb:mB){
        if(cb.second==2){pairB=cb.first;}
    }
    if (pairA!=pairB){return pairA>pairB;}
    else{
        auto oneA =--mA.end();
        auto oneB =--mB.end();
        //由于对子大小相同，只需再依次从大到小比较即可
        for(;;--oneA,--oneB){
            if(oneA->first!=oneB->first){return oneA->first>oneB->first;}
            if(oneA==mA.begin()||oneB==mB.begin()){return true;}
        }
    }
}
//两对 A>=B
bool Compare_Type_TWO_PAIRS(vector<Card> cardsA,vector<Card> cardsB){
    map<int,int> mA;
    map<int,int> mB;
    for(int i=0;i<5;++i){
        ++mA[cardsA[i]._num];
        ++mB[cardsB[i]._num];
    }
    int pairA[2]={0}; int pairB[2]={0};
    int oneA=0;int oneB=0;
    int i=0;
    for(auto &ca:mA){
        if(ca.second==2){pairA[i++]=ca.first;}
        if(ca.second==1){oneA=ca.first;}
    }
    i=0;
    for(auto &cb:mB){
        if(cb.second==2){pairB[i++]=cb.first;}
        if(cb.second==1){oneB=cb.first;}
    }
    for(i=0;i<2;++i){
        if(pairA[i]!=pairB[i]){return pairA[i]>pairB[i];}
    }
    return oneA>=oneB;
}
//三条 A>=B
bool Compare_Type_THREE_OF_A_KIND(vector<Card> cardsA,vector<Card> cardsB){
    map<int,int> mA;
    map<int,int> mB;
    for(int i=0;i<5;++i){
        ++mA[cardsA[i]._num];
        ++mB[cardsB[i]._num];
    }
    int threeA=0;int threeB=0;
    for(auto &c:mA){
        if(c.second==3){threeA=c.first;}
    }
    for(auto &c:mB){
        if(c.second==3){threeB=c.first;}
    }
    if(threeA!=threeB){return threeA>threeB;}
    else{
        auto oneA =--mA.end();
        auto oneB =--mB.end();
        for(;;--oneA,--oneB){
            if(oneA->first!=oneB->first){return oneA->first>oneB->first;}
            if(oneA==mA.begin()||oneB==mB.begin()){return true;}
        }
    }
}
//顺子 A>=B
bool Compare_Type_STRAIGHT(vector<Card> cardsA,vector<Card> cardsB){
    Sort_Cards_Num(cardsA);
    Sort_Cards_Num(cardsB);
    if(cardsA.front()._num==1&&cardsA.back()._num==13){
        if(cardsB.front()._num==1&&cardsB.back()._num==13){
            return true;
        }else{
            return false;
        }
    }
    if(cardsB.front()._num==1&&cardsB.back()._num==13){
        return true;
    }
    return cardsA.back()._num>=cardsB.back()._num;
}
//同花 A>=B
bool Compare_Type_FLUSH(vector<Card> cardsA,vector<Card> cardsB){
    Sort_Cards_Num(cardsA);
    Sort_Cards_Num(cardsB);
    for(int i=4;i>=0;--i){
        if(cardsA[i]._num!=cardsB[i]._num){
            return cardsA[i]._num>cardsB[i]._num;
        }
    }
    return true;
}
//葫芦 A>=B
bool Compare_Type_FULL_HOUSE(vector<Card> cardsA,vector<Card> cardsB){
    map<int,int> mA;
    map<int,int> mB;
    for(int i=0;i<5;++i){
        ++mA[cardsA[i]._num];
        ++mB[cardsB[i]._num];
    }
    int threeA=0;int threeB=0;
    int twoA=0; int twoB=0;
    for(auto &c:mA){
        if(c.second==3){threeA=c.first;}
        if(c.second==2){twoA=c.first;}
    }
    for(auto &c:mB){
        if(c.second==3){threeB=c.first;}
        if(c.second==2){twoB=c.first;}
    }
    if(threeA!=threeB){return threeA>threeB;}
    else{
       return twoA>=twoB; 
    }
}
//四条 A>=B
bool Compare_Type_FOUR_OF_A_KIND(vector<Card> cardsA,vector<Card> cardsB){
    map<int,int> mA;
    map<int,int> mB;
    for(int i=0;i<5;++i){
        ++mA[cardsA[i]._num];
        ++mB[cardsB[i]._num];
    }
    int fourA=0;int fourB=0;
    int oneA=0; int oneB=0;
    for(auto &c:mA){
        if(c.second==4){fourA=c.first;}
        if(c.second==1){oneA=c.first;}
    }
    for(auto &c:mB){
        if(c.second==4){fourB=c.first;}
        if(c.second==1){oneB=c.first;}
    }
    if(fourA!=fourB){return fourA>fourB;}
    else{
       return oneA>=oneB; 
    }
}
//同花顺 A>=B
bool Compare_Type_STRAIGHT_FLUSH(vector<Card> cardsA,vector<Card> cardsB){
    Sort_Cards_Num(cardsA);
    Sort_Cards_Num(cardsB);
    if(cardsA.front()._num==1&&cardsA.back()._num==13){
        if(cardsB.front()._num==1&&cardsB.back()._num==13){
            return true;
        }else{
            return false;
        }
    }
    if(cardsB.front()._num==1&&cardsB.back()._num==13){
        return true;
    }
    return cardsA.back()._num>=cardsB.back()._num;
}
//皇家同花顺 A>=B
bool Compare_Type_ROYAL_FLUSH(vector<Card> cardsA,vector<Card> cardsB){
    Sort_Cards_Num(cardsA);
    Sort_Cards_Num(cardsB);
    if(cardsA.front()._num==1&&cardsA.back()._num==13){
        if(cardsB.front()._num==1&&cardsB.back()._num==13){
            return true;
        }else{
            return false;
        }
    }
    return true;
}


void Window_Go_On(){
    int opt=0;
    cout<<"1.继续  2.退出"<<endl;
    while (1)
    {
        cin>>opt;
        if(opt==1){
            break;
        }else if(opt==2){
            exit(0);
        }else{
            cout<<"\033[1A\r\033[K";
        }
    }
    
}
