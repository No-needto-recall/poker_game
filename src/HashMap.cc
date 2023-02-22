#include "HashMap.hpp"

int MathFunc::Group_M_To_K(int m,int k)
{
    //优化
    if(m<k){return 0;}
    if(k>m/2){
        k=m-k;
    }
    if(k==0){return 1;}
    if(k==1){return m;}
    int dividend=1;
    int tmp1=m;
    while(1){
        dividend*=tmp1;
        --tmp1;
        if(tmp1==m-k+1){
            dividend*=tmp1;
            break;
        }
    }
    int tmp2=k;
    int divisor=1;
    while(1){
        divisor*=tmp2;
        --tmp2;
        if(tmp2==1)
        {
            break;
        }
    }
    return dividend/divisor;
    
}

void MathFunc::SortNums(char *num){
    int i,j;
    for(i=4;i>0;--i)
    {
        for(j=0;j<i;++j)
        {
            if(num[j]>num[i])
            {
                char tmp=num[j];
                num[j]=num[i];
                num[i]=tmp;
            }
        }
    }
}

void PrintCardNum(int *arr){
    for(int i=0;i<5;++i)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
}

int HashMap::Hash(char *num){
    int arr[5]={0};
    MathFunc::SortNums(num);
    for(int i=0;i<5;++i)
    {
        arr[i]=num[i];
    }
    // PrintCardNum(arr);
    int b0=MathFunc::Group_M_To_K(arr[0],1);
    int b1=MathFunc::Group_M_To_K(arr[1],2);
    int b2=MathFunc::Group_M_To_K(arr[2],3);
    int b3=MathFunc::Group_M_To_K(arr[3],4);
    int b4=MathFunc::Group_M_To_K(arr[4],5);

    return b0+b1+b2+b3+b4;
}


void HashMap::Insert(CardsKeyVal kv){
    char* arr=&kv._num0;
    //要排序后才能哈希
    MathFunc::SortNums(arr);
    //根据哈希后的坐标赋值过去
    _valmap[Hash(arr)]=kv._val;
}

unsigned short &HashMap::Find(char* arr){
    MathFunc::SortNums(arr);
    return _valmap[Hash(arr)];
}

bool HashMap::Full(){
    for(auto &rc:_valmap)
    {
        if(rc==0){return false;}
    }
    return true;
}






