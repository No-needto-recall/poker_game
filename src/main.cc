#include "Game.hpp"

Level* Level::_plevel=GetPlevel();//饿汉模式，开始就初始化

int main(int argc, char const *argv[])
{
    /* code */
    if(argc!=2){
        cerr<<"argc !=2"<<endl;
        cerr<<"pls enter players number "<<endl;
        exit(1);
    }
    Level::GetPlevel()->LoadMapFromFile();//加载levelmap.dat为判断牌力做准备
     Game game(std::stoi(argv[1]));//初始化玩家人数
     game.GameStart();
    return 0;
}

