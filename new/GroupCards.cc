#include "GroupCards.hpp"

using namespace CARD;

template<>
Card& Cards::operator[](size_t x){
    x=x%size();
    return *(begin()+x);
}

void GROUP_CARDS::PrintCards(const GroupCards &cards,const int row,const int cow){
    //指定打印几row行，几cow列卡牌
    //暂存卡牌总数
    
    int cards_num=cards.GetSize(); 
    if(row*cow<cards_num){
        cards_num=row*cow;
    }
    int cards_pos=0;
    const Card* arr_cards=cards.GetFirstCards();
    int Line_num=cow;
        for(int i=0;i<cards_num;i+=Line_num ){
    for(int Line=0;Line<Line_num&&Line+i<cards_num;++Line){
        cout<<" ___  ";
    }
    cout<<endl;
    for(int Line=0;Line<Line_num&&Line+i<cards_num;++Line){
        cout<<"| ";
        PrintColour(arr_cards[i+Line].GetColour());
        cout<<" | ";
    }
    cout<<endl;
    for (int Line = 0; Line < Line_num&&Line+i<cards_num; ++Line)
    {
        if(arr_cards[i+Line].GetNum()!=10){
        cout<<"| ";
        PrintNum(arr_cards[i+Line].GetNum());
        cout<<" | ";}
        else{
            cout<<"|1 0| ";
        }
    }
    cout<<endl;
    for(int Line=0;Line<Line_num&&Line+i<cards_num;++Line){
        cout<<"|___| ";
    }
    cout<<endl;
    }

}

void GROUP_CARDS::SortCardsNum(Cards&cards){
    sort(cards.begin(),cards.end(),[](Card a,Card b){
        if(a.GetNum()==b.GetNum()){
            return a.GetColour()<b.GetColour();
        }
        return a.GetNum()<b.GetNum();
    });
}

void GROUP_CARDS::SortCardsColour(Cards&cards){
        sort(cards.begin(),cards.end(),[](Card a,Card b){
        if(a.GetColour()==b.GetColour()){
            return a.GetNum()<b.GetNum();
        }
        return a.GetColour()<b.GetColour();
    });
}

Cards GROUP_CARDS::CardsAddCards(Cards& Lcards,Cards& Rcards){
    Cards tmp;
    tmp.reserve(Lcards.size()+Rcards.size());
    for(auto &rc:Lcards){
        tmp.push_back(rc);
    }
    for(auto &rc:Rcards){
        tmp.push_back(rc);
    }
    return tmp;
}

