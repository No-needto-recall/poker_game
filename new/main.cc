#include "Game.hpp"



int main(int argc, char const *argv[])
{
    /* code */
    if(argc!=2){
        cerr<<"argc !=2"<<endl;
        exit(1);
    }
    Game game(std::stoi(argv[1]));
    game.GameStart();
    return 0;
}

