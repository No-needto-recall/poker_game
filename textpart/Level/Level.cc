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
#if 1
    lv=1;
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
#endif

#if 1
    lv=2;
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
#if 1
    // lv=2+9+1;
    lv=12;
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
    
#if 1
    // lv=2+9+1+12*13;
    lv=168;
    //葫芦
    char colourarr[4]={0,13,26,39};
    for(int i=12;i>=0;--i){
        char num0=i;
        for(int c1=0;c1<=4-3;++c1)
        {
            for(int c2=c1+1;c2<=4-3+1;++c2)
            {
                for(int c3=c2+1;c3<=4-3+2;++c3)
                {
                    char num1=num0+colourarr[c1];
                    char num2=num0+colourarr[c2];
                    char num3=num0+colourarr[c3];
                    for(int s1=0;s1<=4-2;++s1)
                    {
                        for(int s2=s1+1;s2<=4-2+1;++s2)
                        {
                            for(int k=12;k>=0;--k){
                                if(k==i){continue;}
                                char num4=k+colourarr[s1];
                                char num5=k+colourarr[s2];
                                if(k>i){
                                    string use({num1,num2,num3,num4,num5});
                                    _cardsmap.insert({use,++lv});
                                }else{
                                    string use({num4,num5,num1,num2,num3});
                                    _cardsmap.insert({use,++lv});
                                }
                            }
                            lv-=12;
                        }
                    }
                }
            }
        }
        lv+=12;
    }
#endif
   
#if 1
    // lv=2+10+156+156;
    lv=324;
    //同花
    for(int co=0;co<4;++co){
        char colour=co*13;
        char nums[13] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        int timetmp=0;
        for (int n1 = 0; n1 <=13-5;++n1)
        {
            for(int n2=n1+1;n2<=13-5+1;++n2)
            {
                for(int n3=n2+1;n3<=13-5+2;++n3)
                {
                    for(int n4=n3+1;n4<=13-5+3;++n4)
                    {
                        for(int n5=n4+1;n5<=13-5+4;++n5)
                        {
                        char card0=nums[n5]+colour;
                        char card1=nums[n4]+colour;
                        char card2=nums[n3]+colour;
                        char card3=nums[n2]+colour;
                        char card4=nums[n1]+colour;
                        string tmp({card0,card1,card2,card3,card4});
                        //tmp需要排除顺子的可能
                        if(_cardsmap.find(tmp)!=_cardsmap.end()){continue;}
                        else{
                            _cardsmap.insert({tmp,++lv});
                            ++timetmp;
                            }
                        }
                    }
                }
            }
        }
        lv-=timetmp;
    }

#endif
#if 1
    // lv=324+1287-10;
    lv=1601;
    //顺子
    for(int num4=12;num4>=4;--num4)
    {
        ++lv;
        for(int colour4=0;colour4<4;++colour4)
        {
            char card4=num4+colour4*13;//第五张牌
            for(int colour3=0;colour3<4;++colour3)
            {
                char card3=num4-1+colour3*13;//第四张牌
                for(int colour2=0;colour2<4;++colour2)
                {
                    char card2=num4-2+colour2*13;//第三张牌
                    for(int colour1=0;colour1<4;++colour1)
                    {
                        char card1=num4-3+colour1*13;//第二张牌
                        for(int colour0=0;colour0<4;++colour0)
                        {
                            char card0=num4-4+colour0*13;
                            string tmp({card0,card1,card2,card3,card4});
                            if(_cardsmap.find(tmp)!=_cardsmap.end()){continue;}
                            else{
                                _cardsmap.insert({tmp,lv});
                            }
                        }
                    }
                }
            }
        }
    }
    ++lv;
    for(int colour4=0;colour4<4;++colour4)
    {
        char card4=12+colour4*13;//第五张牌 A
        for(int colour3=0;colour3<4;++colour3)
        {
            char card3=3+colour3*13;//第四张牌 5
            for(int colour2=0;colour2<4;++colour2)
            {
                char card2=2+colour2*13;//第三张牌 4
                for(int colour1=0;colour1<4;++colour1)
                {
                    char card1=1+colour1*13;//第二张牌 3
                    for(int colour0=0;colour0<4;++colour0)
                    {
                        char card0=0+colour0*13;//第一张牌 2
                        string tmp({card0,card1,card2,card3,card4});
                        if(_cardsmap.find(tmp)!=_cardsmap.end()){continue;}
                        else{
                            _cardsmap.insert({tmp,lv});
                        }
                    }
                }
            }
        }
    }
#endif
#if 1
    // lv=1601+10;
    lv=1611;
    //三条YX1X2
    for(int numY=12;numY>=0;--numY){//确定三张点数一样的牌的点数
        int times1=0;
        for(int co1=0;co1<=4-3;++co1)
        {
            for(int co2=co1+1;co2<=4-3+1;++co2)
            {
                for(int co3=co2+1;co3<=4-3+2;++co3)
                {
                    char card0=numY+co1*13;
                    char card1=numY+co2*13;
                    char card2=numY+co3*13;
                    string tmpY({card0,card1,card2});//一组三张点数一样的牌
                    for(int numX1=12;numX1>=0;--numX1)//X1的点数确定
                    {
                        if(numX1==numY){continue;}
                        for(int coX1=0;coX1<4;++coX1)//X1的花色确定
                        {
                            char cardX1=numX1+coX1*13;
                            int times2 = 0;
                            string tmpX1({cardX1});//确认X1的卡牌
                            for(int numX2=12;numX2>=0;--numX2)//x2的点数确定
                            {
                                if(numX1==numX2){continue;}
                                ++lv;
                                ++times2;    
                                for(int coX2=0;coX2<4;++coX2)//X2的花色确定
                                {
                                    char cardX2=numX2+coX2*13;
                                    string tmpX2({cardX2});//确定X2的卡牌
                                    string tmp;
                                    if(numY<numX1&&numY<numX2)//说明numY在最左侧
                                    {
                                        tmp+=numY;
                                        if(numX1<numX2){tmp+=numX1+numX2;}
                                        else{tmp+=numX2+numX1;}
                                    }
                                    else if(numX1<numY&&numX1<numX2)
                                    {
                                        tmp+=numX1;
                                        if(numY<numX2){tmp+=numY+numX2;}
                                        else{tmp+=numX2+numY;}
                                    }else if(numX2<numY&&numX2<numX1)
                                    {
                                        tmp+=numX2;
                                        if(numY<numX1){tmp+=numY+numX1;}
                                        else{tmp+=numX1+numY;}
                                    }
                                    if(_cardsmap.find(tmp)!=_cardsmap.end()){continue;}
                                    else{_cardsmap.insert({tmp,lv});}
                                }
                            }
                            lv -= times2; // X1的花色改变不会影响lv
                        }
                        ++lv;
                        ++times1;
                    }
                    lv -= times1; // Y的花色改变不会影响Lv
                }
            }
        }
    }
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
