#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using std::vector;
using std::array;
using std::cout;
using std::endl;
using std::for_each;



void show_int_bit(long imap){
        long _tmp=imap;
        for(short i=0;i<22;++i){
            cout<<(_tmp&1)<<" ";
            if(3==i%4){cout<<"|";}
            _tmp=_tmp>>1;
        }
        cout<<endl;
}

long  get_all_bit_1(int twhere){
    long tmp=1;
    for(int i=0;i<(twhere%32);++i){
        tmp=tmp<<1;
        tmp=tmp&1;
    }
    return tmp;
}


class map22bit{
private:
    int _mapbit;
public:
    map22bit()
    :_mapbit(0)
    {}
    ~map22bit(){}
    void show_map(){
        int _tmp=_mapbit;
        for(short i=0;i<22;++i){cout<<((_tmp>>1)&1)<<" ";}
        cout<<endl;
    }
    bool operator[](int const&pos){
        int _tmp=_mapbit;
        return (_tmp>>(pos%22))&1;
    }
    void set_T(int const&pos){
        int tmp=1;
        tmp=tmp<<(pos%22);
        cout<<"tmp    : ";
        show_int_bit(tmp);
        cout<<"_mapbit: ";
        show_int_bit(_mapbit);
        _mapbit=_mapbit|tmp;
        cout<<"_mapbit: ";
        show_int_bit(_mapbit);
    }

    void set_F(int const&pos){
        int tmp=65535;
    }
};



void text2(){
    map22bit alive22;
    alive22.set_T(10);
    cout<<endl;
    alive22.set_T(5);
    cout<<endl;
    
    long tmp=get_all_bit_1(22);
    show_int_bit(tmp);
}



void text(){
auto print = [](const bool n){cout<<n<<" ";};
auto SetToF=[](bool&n){n=0;};

    vector<bool> vb(22,true);
    vb.shrink_to_fit();
    for(auto c:vb){
            cout<<c<<" ";
    }
    cout<<endl;
    
    /* for_each(vb.begin(),vb.end(),SetToF); */
    for(int i=0;i<vb.size();++i)
    {vb[i]=0;}
    for_each(vb.begin(),vb.end(),print);
    cout<<endl;
    cout<<"vb.size():"<<vb.size()<<endl;
    cout<<"vb.capacity()"<<vb.capacity()<<endl;
}
void text3(){
auto print = [](const bool n){cout<<n<<" ";};
auto SetToF=[](bool&n){n=0;};

    array<bool,1024> arr;
    for(auto &ca:arr){
        ca=true;
    }
    for(auto &ca:arr){
        cout<<ca<<" ";
    }
    cout<<endl;

    for_each(arr.begin(),arr.end(),SetToF);
    for_each(arr.begin(),arr.end(),print);
    cout<<endl;
}




int main()
{
    /* text(); */
    text2();
    return 0;
}

