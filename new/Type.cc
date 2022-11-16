#include "Type.hpp"

Type::Type(Cards cards5)
:GroupCards(5)
,_type(TYPE::GetType(cards5))
,_greadter(TYPE::SetGreadter(_type))
{
    _cards=cards5;
    GROUP_CARDS::SortCardsNum(_cards);
}

void Type::SetCards(Cards cards){
    if(cards.size()!=5){
        cerr<<"Type::SetCards() cards.size()!=5 \n";
        return;
    }
    _cards=cards;
    SetType(TYPE::GetType(_cards));
}

void Type::Show()const{
    if(_type==0){
        cerr<<"Type::Show()const _type==0 \n";
        return;
    }
    TYPE::PrintType(_type);
    cout<<endl;
    GROUP_CARDS::PrintCards(*this, 1, 5);
}

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

Compare TYPE::SetGreadter(const TypeType type){
    if(type==HIGH_CARD){return GREADER::HighCard;}
    else if(type==ONE_PAIR){return GREADER::KindCard;}
    else if(type==TWO_PAIRS){return GREADER::KindCard;}
    else if(type==THREE_OF_A_KIND){return GREADER::KindCard;}
    else if(type==STRAIGHT){return GREADER::HighCard;}
    else if(type==FLUSH){return GREADER::HighCard;}
    else if(type==FULL_HOUSE){return GREADER::KindCard;}
    else if(type==FOUR_OF_A_KIND){return GREADER::KindCard;}
    else if(type==STRAIGHT_FLUSH){return GREADER::HighCard;}
    else {return GREADER::RoyalFlush;}
}


bool Type::operator>(const Type&rhs)const{
    if(this->_type==rhs._type){return _greadter(*this,rhs);}
    return this->_type>rhs._type;
}

bool Type::operator==(const Type&rhs)const{
    if(this->_type==rhs._type){return EQUA::Equa(*this,rhs);}
    return false;
}

bool Type::operator>=(const Type&rhs)const{
    return *this>rhs||*this==rhs;
}
bool Type::operator<=(const Type&rhs)const{
    return !(*this>rhs);
}

bool GREADER::HighCard(const Type & Left,const Type & Right){
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    for(int i=4;i>=0;--i){
        if(Cleft[i].GetNum()!=Cright[i].GetNum()){
            return Cleft[i].GetNum()>Cright[i].GetNum();
        }
    }
    return false;
}
bool GREADER::KindCard(const Type & Left,const Type & Right){
    map<NumType,int> numLMap;
    map<NumType,int> numRMap;
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
bool GREADER::RoyalFlush(const Type & Left,const Type & Right){
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    return Cleft[0].GetNum()>Right.GetNums();
}

bool EQUA::Equa(const Type & Left,const Type & Right){
    auto Cleft=Left.ReturnCards();
    auto Cright=Right.ReturnCards();
    for(int i=4;i>=0;--i){
        if(Cleft[i].GetNum()!=Cright[i].GetNum()){return false;}
    }
    return true;
}
