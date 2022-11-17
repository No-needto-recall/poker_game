#include <iostream>

#include <map>

using std::cout;
using std::endl;
using std::map;

int main()
{
    map<int,int,std::greater<int> > MapNum;
    for(int i=10;i>0;--i){
        ++MapNum[i];
    }
    for(auto&rm:MapNum){
        cout<<rm.first<<":"<<rm.second<<endl;
    }
    return 0;
}

