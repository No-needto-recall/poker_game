#include <iostream>

#include <map>

using std::cout;
using std::endl;
using std::map;

void text(){
    map<int,int,std::greater<int> > MapNum;
    for(int i=10;i>0;--i){
        ++MapNum[i];
    }
    for(auto&rm:MapNum){
        cout<<rm.first<<":"<<rm.second<<endl;
    }
}

void PrintHart(){
    cout<<"\033[31m\033[47m♥\033[0m";
}
void PrintSpade(){
    cout<<"\033[30m\033[47m♠\033[0m";
}
void PrintNum(int num){
    cout<<"\033[30m\033[47m"<<num<<"\033[0m";
}

void PrintBack(){
    cout<<"\033[47m \033[0m";
}
void text2(){
    PrintBack();
    PrintHart();
    PrintBack();
    cout<<endl;
    PrintBack();
    PrintNum(2);
    PrintBack();
    cout<<endl;

    cout<<endl;
    PrintHart();
    PrintBack();
    cout<<" ";
    PrintSpade();
    PrintBack();
    cout<<endl;
    PrintNum(1);
    PrintNum(0);
    cout<<" ";
    PrintBack();
    PrintNum(2);
    cout<<endl;
    
}
int main()
{
    /* text(); */
    text2();
    return 0;
}

