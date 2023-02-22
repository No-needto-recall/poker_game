#include "Game.hpp"

Level* Level::_plevel=GetPlevel();//饿汉模式，开始就初始化

int main(int argc, char const *argv[])
{
    if(argc!=2){
        cerr<<"argc !=2"<<endl;
        exit(1);
    }
    Level::GetPlevel()->LoadMapFromFile();
    Game game(std::stoi(argv[1]));
    game.GameStart();
    return 0;
}

