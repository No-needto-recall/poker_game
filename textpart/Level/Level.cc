#include "Level.hpp"

LevelType LEVEL::GetLevel(Cards keycards){
    return  0;
}

string LEVEL::CardsToString(Cards cards){
    //一组牌转化为字符串
    //“.”表示卡牌描述结束
    string Str;
    Str.reserve(20);
    for(auto& rc:cards){
        
        char tmp=static_cast<char>(rc.GetColour()*13+rc.GetNum()-2);
        Str+=tmp;
    }
    Str.shrink_to_fit();
    return Str;
}
Cards LEVEL::StringToCards(string str){
    Cards tmp;
    for(auto &rs:str)
    {
        Card tmp0(rs);
        tmp.push_back(tmp0);
    }
    return tmp;
}

void Level::CreatMap(){
    int lv=1;
    //对皇家同花顺
    for (int i = 0; i < 4; ++i)
    {
        char ch0=i*13+0;//2
        char ch1=i*13+1;//3
        char ch2=i*13+2;//4
        char ch3=i*13+3;//5
        char ch4=i*13+12;//A
        char ch5=i*13+8;//10
        char ch6=i*13+9;//J
        char ch7=i*13+10;//Q
        char ch8=i*13+11;//K
        string tmp({ch5,ch6,ch7,ch8,ch4});
        _cardsmap.insert({tmp,lv});
        string tmp2({ch0,ch1,ch2,ch3,ch4});
        _cardsmap.insert({tmp2,lv+1});
    }
    lv=2;

#if 0
    //对同花顺；
    for(int i=0;i<4;++i){
        char colour=i*13;
        for(int j=12;j>=4;--j){
            char numS = j;
            char card0 = colour + numS,card1=card0-4,card2=card0-3,card3=card0-2,card4=card0-1;
            string tmp({card1, card2, card3, card4, card0});
            _cardsmap.insert({tmp,++lv});
        }
       lv=2; 
    }
    lv=2+9;
    for(int i=0;i<4;++i){
        char colour=i*13;
        char card=colour+0,card1=colour+1,card2=colour+2,card3=colour+3;
        char cardA=colour+12;
        string tmp({card,card1,card2,card3,cardA});
        _cardsmap.insert({tmp,lv});
    }
#endif
#if 0
    lv=2+9+1;
    //四条
    for(int i=12;i>=0;--i){
        char nums=i,nums1=nums+13,nums2=nums1+13,nums3=nums2+13;
        string tmp;
        tmp.resize(4);
        tmp[0]=nums;
        tmp[1]=nums1;
        tmp[2]=nums2;
        tmp[3]=nums3;
        for(int j=0;j<4;++j)
        {
            char colour=j;
            for(int k=12;k>=0;--k){
                if(k==i){continue;}
                char card=colour*13+k;
                string use;
                if(i>k){use=card+tmp;}
                else{use=tmp+card;}
                _cardsmap.insert({use,++lv});
            }
            lv-=12;
        }
        lv+=12;
    }
#endif
    // lv=2+9+1+12*13;
    lv=168;
#if 1
    //葫芦
    
#endif


    cout<<"lv:"<<lv<<endl;
}

void Level::ShowMap(){
    GroupCards tmp(5);
    int times=0;
    for(auto &rm:_imagemap){
        cout<<"Lv:"<<rm.first<<endl;
        for(auto &rv:rm.second)
        {
            tmp.ReturnCards()=LEVEL::StringToCards(rv);
            GROUP_CARDS::PrintCards(tmp);
            cout<<endl;
        }
        ++times;
        if(times=20){
            // cin>>times;
        }
    }
}

void Level::ImageMap(){
    for(auto &rm:_cardsmap)
    {
        _imagemap[rm.second].push_back(rm.first);

    }
}
