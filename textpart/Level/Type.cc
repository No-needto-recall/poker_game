#include "Type.hpp"

Type::Type(Cards cards5)
:GroupCards(5)
,_level(TYPE::GetLevelFromMap(cards5))
// ,_greadter(TYPE::SetGreadter(_type))
{
    _cards=cards5;
    GROUP_CARDS::SortCardsNum(_cards);
}
//设置5张牌给Type的_cards,获取其牌型，改变其比较函数
void Type::SetCards(Cards cards){
    if(cards.size()!=5){
        cerr<<"Type::SetCards() cards.size()!=5 \n";
        return;
    }
    _cards=cards;
    SetType(TYPE::GetLevelFromMap(_cards));
}

void Type::Show()const{
    if(GetType()==0){
        cerr<<"Type::Show()const _type==0 \n";
        return;
    }
    TYPE::PrintType(GetType());
    cout<<endl;
    GROUP_CARDS::PrintCards(*this, 1, 5);
}
//根据5张牌，判断LV
LevelType TYPE::GetLevelFromMap(const Cards&cards5)
{
    return Level::GetPlevel()->GetLevel(cards5);
}
#if 0
//根据5张牌，判断牌力
TypeType TYPE::GetType(const Cards&cards5){
    //暂存,排序
    Cards tmp=cards5;
    GROUP_CARDS::SortCardsNum(tmp);

    //统计相同点数的出现次数
    map<NumType,int> kind_map;
    //统计相同花色的出现次数
    map<ColourType,int> colour_map;
    for(auto &rc:tmp){
        ++kind_map[rc.GetNum()];
        ++colour_map[rc.GetColour()];
    }
    int arrkind[4]={0};
    bool colour5=false;
    for(auto &rc:kind_map){
        if(rc.second==1){++arrkind[0];}
        else if(rc.second==2){++arrkind[1];}
        else if(rc.second==3){++arrkind[2];}
        else if(rc.second==4){++arrkind[3];}
    }
    for(auto &rc:colour_map){
        if(rc.second==5){colour5=true;}
    }
    bool straight5=false;
    if(arrkind[0]==5){straight5=TYPE::IsStraight(tmp);}
    bool RoyalFlush5=false;
    if(colour5&&straight5){RoyalFlush5=TYPE::IsRoyalFlush(tmp);}

    TypeType typeTmp=0;
    if(RoyalFlush5){typeTmp=ROYAL_FLUSH;}
    else if(colour5&&straight5){typeTmp=STRAIGHT_FLUSH;}
    else if(arrkind[3]==1){typeTmp=FOUR_OF_A_KIND;}
    else if(arrkind[2]==1&&arrkind[1]==1){typeTmp=FULL_HOUSE;}
    else if(colour5){typeTmp=FLUSH;}
    else if(arrkind[0]==5&&straight5){typeTmp=STRAIGHT;}
    else if(arrkind[2]==1&&arrkind[0]==2){typeTmp=THREE_OF_A_KIND;}
    else if(arrkind[1]==2&&arrkind[0]==1){typeTmp=TWO_PAIRS;}
    else if(arrkind[1]==1&&arrkind[0]==3){typeTmp=ONE_PAIR;}
    else {typeTmp=HIGH_CARD;}

    return  typeTmp;
}
#endif
#if 0
bool TYPE::IsStraight(const Cards &cards){
    
    if(cards[0].GetNum()+4==cards[4].GetNum()){
        return true;
    }
    if(cards[0].GetNum()==NUM_2&&cards[3].GetNum()==NUM_5&&cards[4].GetNum()==NUM_A){
        return true;
    }
    return false;
}

bool TYPE::IsRoyalFlush(const Cards &cards){
    if(cards[4].GetNum()==NUM_A)
    {
        return true;
    }
    return false;
}
#endif
void TYPE::PrintType(TypeType type){
     if(type==HIGH_CARD){cout<<"高牌 (High Card)";}
    else if(type==ONE_PAIR){cout<<"一对 (One Pair)";}
    else if(type==TWO_PAIRS){cout<<"两对 (Two Pairs)";}
    else if(type==THREE_OF_A_KIND){cout<<"三条 (Three Of A Kind)";}
    else if(type==STRAIGHT){cout<<"顺子 (Straight)";}
    else if(type==FLUSH){cout<<"同花 (Flush)";}
    else if(type==FULL_HOUSE){cout<<"葫芦 (Full House)";}
    else if(type==FOUR_OF_A_KIND){cout<<"四条 (Four Of A Kind)";}
    else if(type==STRAIGHT_FLUSH){cout<<"同花顺 (Straight Flush)";}
    else {cout<<"皇家同花顺 (Royal Flush)";}
}
#if 0
Compare TYPE::SetGreadter(const TypeType type){
    if(type==HIGH_CARD){return GREADER::KindCard;}
    else if(type==ONE_PAIR){return GREADER::KindCard;}
    else if(type==TWO_PAIRS){return GREADER::KindCard;}
    else if(type==THREE_OF_A_KIND){return GREADER::KindCard;}
    else if(type==STRAIGHT){return GREADER::KindCard;}
    else if(type==FLUSH){return GREADER::KindCard;}
    else if(type==FULL_HOUSE){return GREADER::KindCard;}
    else if(type==FOUR_OF_A_KIND){return GREADER::KindCard;}
    else if(type==STRAIGHT_FLUSH){return GREADER::KindCard;}
    else {return GREADER::KindCard;}
}
#endif
#if 0
bool Type::operator>(const Type&rhs)const{
    if(this->_type==rhs._type){return GREADER::KindCard(*this,rhs);}
    return this->_type>rhs._type;
}
bool Type::operator<(const Type&rhs)const{
    return !(*(this)>=rhs);
}

bool Type::operator==(const Type&rhs)const{
    if(this->_type==rhs._type){return EQUA::Equa(*this,rhs);}
    return false;
}

bool Type::operator!=(const Type&rhs)const{
    return !(*(this)==rhs);
}

bool Type::operator>=(const Type&rhs)const{
    return *this>rhs||*this==rhs;
}
bool Type::operator<=(const Type&rhs)const{
    return !(*this>rhs);
}
#endif
bool Type::operator>(const Type&rhs)const{
    return this->_level<rhs._level;
}
bool Type::operator<(const Type&rhs)const{
    return this->_level>rhs._level;
}

bool Type::operator==(const Type&rhs)const{
    return this->_level==rhs._level;
}

bool Type::operator!=(const Type&rhs)const{
    return this->_level!=rhs._level;
}

bool Type::operator>=(const Type&rhs)const{
    return rhs._level>=this->_level;
}
bool Type::operator<=(const Type&rhs)const{
    return rhs._level<=this->_level;
}

TypeType Type::LevelToType(const LevelType lv)const{
    if(lv<1){
        cerr<<"error lv:"<<lv<<endl;
        exit(1);}
    else if(lv<=2){return ROYAL_FLUSH;}
    else if(lv<=12){return STRAIGHT_FLUSH;}
    else if(lv<=168){return FOUR_OF_A_KIND;}
    else if(lv<=324){return FULL_HOUSE;}
    else if(lv<=1601){return FLUSH;}
    else if(lv<=1611){return STRAIGHT;}
    else if(lv<=2469){return THREE_OF_A_KIND;}
    else if(lv<=3327){return TWO_PAIRS;}
    else if(lv<=6187){return ONE_PAIR;}
    else if(lv<=7464){return HIGH_CARD;}
    else{
        cerr<<"error lv:"<<lv<<endl;
        exit(1);
    }
}

#if 0
bool GREADER::HighCard(const Type & Left,const Type & Right){
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    GROUP_CARDS::SortCardsNum(Cleft);
    GROUP_CARDS::SortCardsNum(Cright);
    for(int i=4;i>=0;--i){
        if(Cleft[i].GetNum()!=Cright[i].GetNum()){
            return Cleft[i].GetNum()>Cright[i].GetNum();
        }
    }
    return false;
}
#endif
#if 0
bool GREADER::KindCard(const Type & Left,const Type & Right){
    map<NumType,int,std::greater<NumType> > numLMap;
    map<NumType,int,std::greater<NumType> > numRMap;
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    for(int i=0;i<5;++i){
        ++numLMap[Cleft[i].GetNum()];
        ++numRMap[Cright[i].GetNum()];
    }
    int kind4[2]={0};
    int kind3[2]={0};
    int Lkind2[2]={0};
    int Rkind2[2]={0};
    int Lkind1[5]={0};
    int Rkind1[5]={0};
    int pos2l,pos2r,pos1l,pos1r;
    pos2l=pos2r=pos1l=pos1r=0;
    for(auto &rc:numLMap){
        if(rc.second==4){kind4[0]=rc.first;}
        if(rc.second==3){kind3[0]=rc.first;}
        if(rc.second==2){Lkind2[pos2l++]=rc.first;}
        if(rc.second==1){Lkind1[pos1l++]=rc.first;}
    }
    for(auto &rc:numRMap){
        if(rc.second==4){kind4[1]=rc.first;}
        if(rc.second==3){kind3[1]=rc.first;}
        if(rc.second==2){Rkind2[pos2r++]=rc.first;}
        if(rc.second==1){Rkind1[pos1r++]=rc.first;}
    }
    if(kind4[0]!=0&&kind4[1]!=0){
        if(kind4[0]!=kind4[1]){
            return kind4[0]>kind4[1];
        }else{return Lkind1[0]>Rkind1[0];}
    }
   else if(kind3[0]!=0&&kind3[1]!=0){
        if(Lkind2[0]!=0&&Rkind2[0]!=0){
            if(kind3[0]!=kind3[1]){return kind3[0]>kind3[1];}
            else{return Lkind2[0]>Rkind2[0];}
        }else{
            if(kind3[0]!=kind3[1]){return  kind3[0]>kind3[1];}
            else{
                for(int i=0;i<3;++i){if(Lkind1[i]!=Rkind1[i]){return Lkind1[i]>Rkind1[i];}}
                return false;
            }
        }
    }
   else if(Lkind2[0]!=0&&Lkind2[1]!=0&&Rkind2[0]!=0&&Rkind2[1]!=0){
        for(int i=0;i<2;++i){
            if(Lkind2[i]!=Rkind2[i]){return Lkind2[i]>Rkind2[i];}
        }
        return Lkind1[0]>Rkind1[0];
    }
    else if(Lkind2[0]!=0&&Rkind2[0]!=0){
        if(Lkind2[0]!=Rkind2[0]){return Lkind2[0]>Rkind2[0];}
        for(int i=0;i<3;++i){
            if(Lkind1[i]!=Rkind1[i]){return Lkind1[i]>Rkind1[i];}
        }
        return false;
    }
    else{
        for(int i=0;i<5;++i){
            if(Lkind1[i]!=Rkind1[i]){return Lkind1[i]>Rkind1[i];}
        }
        return false;
    }
}
#endif
#if 0
bool GREADER::RoyalFlush(const Type & Left,const Type & Right){
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    return Cleft[0].GetNum()>Right.GetNums();
}
#endif
#if 0
bool EQUA::Equa(const Type & Left,const Type & Right){
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    GROUP_CARDS::SortCardsNum(Cleft);
    GROUP_CARDS::SortCardsNum(Cright);
    for(int i=4;i>=0;--i){
        if(Cleft[i].GetNum()!=Cright[i].GetNum()){return false;}
    }
    return true;
}
#endif

Type TYPE::GainType(Cards cards){
    int Cnum=cards.size();
    if(Cnum<5){
        cerr<<"TYPE::GainType() Cnum<5 \n";
        exit(1);
    }
    Type Tret;
    if(Cnum==5){
        Tret.SetCards(cards);
        return Tret;
    }else{
        //从N张牌中选5张
        Cards Ctmp;
        Type Ttmp;
        const int Five=5;
        Ctmp.resize(Five);
        int Pick1,Pick2,Pick3,Pick4,Pick5;
        for(Pick1=0;Pick1<=Cnum-Five;++Pick1){
            for(Pick2=Pick1+1;Pick2<=Cnum-Five+1;++Pick2){
                for(Pick3=Pick2+1;Pick3<=Cnum-Five+2;++Pick3){
                    for(Pick4=Pick3+1;Pick4<=Cnum-Five+3;++Pick4){
                        for(Pick5=Pick4+1;Pick5<=Cnum-Five+4;++Pick5){
                            Ctmp[0]=cards[Pick1];
                            Ctmp[1]=cards[Pick2];
                            Ctmp[2]=cards[Pick3];
                            Ctmp[3]=cards[Pick4];
                            Ctmp[4]=cards[Pick5];
                            Ttmp.SetCards(Ctmp);
                            if(Ttmp>Tret){
                                Tret.SetCards(Ctmp);
                            }
                        }
                    }
                }
            }
        }
        return Tret;
    }
}



void TYPE::SwapCards(const Cards &pubcards,Cards &target){
    int pos=0;
    int size=target.size();
    for(int i=0;i<size;++i)
    {
        pos=FindCardInCards(pubcards,target[i]);
        if(pos!=-1){
            Card tmp=target[i];
            target[i]=target[pos];
            target[pos]=tmp;
        }
    }
}
int TYPE::FindCardInCards(const Cards& pubcards,const Card& contrust){
    int size=pubcards.size(); 
    for(int i=0;i<size;++i){
        if(pubcards[i]==contrust){return i;}
    }
    return -1;
}
