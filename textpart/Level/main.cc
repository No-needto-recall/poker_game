#include "Level.hpp"

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

void test(){
    unordered_map<string,int> Cmap;
    GroupCards gcards(5);
    gcards.ReturnCards().push_back(Card(6,0));
    gcards.ReturnCards().push_back(Card(7,0));
    gcards.ReturnCards().push_back(Card(7,1));
    gcards.ReturnCards().push_back(Card(7,2));
    gcards.ReturnCards().push_back(Card(7,3));
    GROUP_CARDS::PrintCards(gcards);
    string tmp3(LEVEL::CardsToString(gcards.ReturnCards()));
    cout<<tmp3<<endl;
    gcards.ReturnCards()=LEVEL::StringToCards(tmp3);
    GROUP_CARDS::SortCardsNum(gcards.ReturnCards());
    GROUP_CARDS::PrintCards(gcards);

}

int main()
{

    test();
    cout<<endl;
    Level lv;
    lv.CreatMap();
    lv.ImageMap();
    lv.ShowMap();
    return 0;
}

