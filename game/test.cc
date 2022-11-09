#include "poker.hpp"


void test0(){
    cout<<" ___ "<<" ___ "<<endl;
    cout<<"| ♠ |"<<"| \033[31m♥\033[0m |"<<endl;
    cout<<"| 5 |"<<"| 5 |"<<endl;
    cout<<"|___|"<<"|___|"<<endl;
    
}

void test1(){
    Deck d1;
    Player p1;
    Player p2;
    Table t1;
    d1.Creat_Deck();

    for (int k = 0; k < 10; ++k)
    {
        d1.Shuffle_Deck(2);
        for (int j = 0; j < 7; ++j)
        {
            for (int i = 0; i < 5; ++i)
            {
                t1._public_card.push_back(d1.Send_Card());
            }
            p1._hands.push_back(d1.Send_Card());
            p1._hands.push_back(d1.Send_Card());
            p2._hands = Type_for_Cards(t1._public_card, p1._hands);
            t1.Print_Table();
            p1.Print_Player();
            Sort_Cards_Num(p2._hands);
            p2.Print_Player(5);
            Print_Type(Type_for_5Cards(p2._hands));
            cout<<endl;
            p1.Reset_Hands();
            p2.Reset_Hands();
            t1.Reset_Table_All();
        }
        d1.Reset_Deck();
    }
}
void test2(int num){
    random_device r;
    default_random_engine er(r());
    uniform_int_distribution<int> uniform_dist(0,51);
    map<int,int> mapnum;
    for(int i=0;i<num;++i){
        int mean=uniform_dist(er);
        ++mapnum[mean];
    }
    for(auto &c:mapnum){
        cout<<c.first<<":";
        for(int i=0;i<c.second;++i){
            cout<<"|";
        }
        cout<<endl;
    }
}

void test3(){
    vector<Card> v1;
    v1.push_back(Card(1,0));
    v1.push_back(Card(2,0));
    v1.push_back(Card(3,0));
    v1.push_back(Card(4,0));
    v1.push_back(Card(13,0));
    Print_Cards(v1,5);
    if(Type_Straight(v1)){
        cout<<"is Straight"<<endl;
    }else{
        cout<<"not Straight"<<endl;
    }
    if(Type_Flush(v1)){
        cout<<"is Flush"<<endl;
    }else{
        cout<<"nou Flush"<<endl;
    }
}

void test4(){
    Deck d1;
    Player p1;
    Player p2;
    d1.Creat_Deck();
    d1.Shuffle_Deck();
    p1._hands.push_back(d1.Send_Card());
    p1._hands.push_back(d1.Send_Card());
    p1._hands.push_back(d1.Send_Card());
    p1._hands.push_back(d1.Send_Card());
    p1._hands.push_back(d1.Send_Card());
    p2._hands.push_back(d1.Send_Card());
    p2._hands.push_back(d1.Send_Card());
    vector<Card> type=Type_for_Cards(p1._hands,p2._hands);
    Print_Cards(p1._hands,5);
    Print_Cards(p2._hands);
    Print_Cards(type,5);
    Print_Type(Type_for_5Cards(type));
    cout<<endl;
}

void test5(){
    Player p1;
    Player p2;
    Table t1;
    p1._hands.push_back(Card(6,1));
    p1._hands.push_back(Card(8,1));
    p2._hands.push_back(Card(11,1));
    p2._hands.push_back(Card(4,0));
    t1._public_card.push_back(Card(8,0));
    t1._public_card.push_back(Card(2,2));
    t1._public_card.push_back(Card(8,3));
    t1._public_card.push_back(Card(4,2));
    t1._public_card.push_back(Card(4,1));
    p1.Print_Player();
    p2.Print_Player();
    t1.Print_Table();
    p1._level=Type_for_Cards(t1._public_card,p1._hands);
    p2._level=Type_for_Cards(t1._public_card,p2._hands);
    Print_Cards(p1._level,5);
    Print_Cards(p2._level,5);
    if(Compare_Type_FULL_HOUSE(p1._level,p2._level)){
    Print_Cards(p1._level,5);
    }else{
    Print_Cards(p2._level,5);
    }
}



int main(int argc, char const *argv[])
{
    //test1();
  
    //test3();
    //test4();
    //test5();

#if 0
    Game game1(std::stoi(argv[1]));
    game1.Set_Players(10000,std::stoi(argv[2]));
    game1.Game_Stand_Alone();
#endif

#if 1
    Game game2(std::stoi(argv[1]));
    game2.Set_Players(5000);
    game2.Test();
#endif


    //test2(5000);
    return 0;
}
