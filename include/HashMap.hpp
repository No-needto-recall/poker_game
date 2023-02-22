#ifndef _CTL_HASHMAP_HPP_
#define _CTL_HASHMAP_HPP_

#include <vector>
#include <string>

using std::vector;
using std::string;


typedef struct{
    char _num0;
    char _num1;
    char _num2;
    char _num3;
    char _num4;
    unsigned short _val;
}CardsKeyVal;

namespace MathFunc{
    //m个不同的数里选出k个，有多少种组合情况。
    int Group_M_To_K(int m,int k);
    void SortNums(char*);
    void StringCopyToCardsKeyVal(string & str,CardsKeyVal & rhs);
    
    

}//end of MathFunc



//针对全组合对自然数映射的哈希
//目前仅针对德州扑克
class HashMap
{
public:
    HashMap(int size) {
        _valmap.resize(size);
    }
    ~HashMap() {}
    int Hash(char*);
    void Insert(CardsKeyVal);
    unsigned short& Find(char*);
    bool Full();
    vector<unsigned short> _valmap;
};

inline 
void MathFunc::StringCopyToCardsKeyVal(string &str,CardsKeyVal &rhs)
{
    rhs._num0=str[0];
    rhs._num1=str[1];
    rhs._num2=str[2];
    rhs._num3=str[3];
    rhs._num4=str[4];
}


#endif
