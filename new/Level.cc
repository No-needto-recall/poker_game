#include "Level.hpp"

LevelType LEVEL::GetLevel(Cards keycards){
    return  0;
}

string LEVEL::CardsToString(Cards cards){
    //一组牌转化为字符串
    //“02”，“013”
    //首位表示花色，下一位表示点数，用“.”表示卡牌描述结束
    string Str;
    for(auto& rc:cards){
        string tmp;
        tmp.reserve(4);
        tmp+=std::to_string(rc.GetColour());
        tmp+=std::to_string(rc.GetNum());
        tmp+='.';
        cout<<tmp.size();
        Str+=tmp;
    }
    Str.shrink_to_fit();
    return Str;
}

void Level::CreatMap(){
    

}
