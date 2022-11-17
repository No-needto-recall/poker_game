#ifndef _CTL_CHIP_HPP_
#define _CTL_CHIP_HPP_


using ChipType=unsigned int;

class Chip
{
public:
    Chip(ChipType chip=2000)
    :_chip(chip)
    {}
    ~Chip() {}
    //判空
    bool IsEmpty(){return _chip==0;}
    //使用筹码
    bool UseChip(ChipType usenum){
        if(usenum>_chip){return false;}
        _chip-=usenum;
        return true;
    }
    //获取筹码
    void GetChip(ChipType getnum){_chip+=getnum;}
    //设置筹码
    void SetChip(ChipType setchip){_chip=setchip;}
    //查看筹码
    ChipType PeekChip()const{return _chip;}
protected:
    ChipType _chip;

};

class Chips
:public Chip
{
public:
    Chips(ChipType chips=2000)
    :Chip(chips)
    ,_bet(0)
    {}
    ~Chips(){}
    //更新下注
    bool UpdateBet(ChipType bet){
        if(bet<_bet){return  false;}
        _bet=bet;
        return true;
    }
    void CleanBet(){_bet=0;}
    ChipType PeekBet()const{return _bet;}
private:
    ChipType _bet;
};

class Jackpot
:public Chip
{
public: 
    Jackpot(ChipType jackpot=0)
    :Chip(jackpot)
    ,_maxbet(0)
    {}
    ~Jackpot(){}
    //跟新最大下注
    bool UpdateMaxBet(ChipType bet){
        if(bet<_maxbet){return false;}
        _maxbet=bet; 
        return  true;
    }
    void CleanMaxBet(){_maxbet=0;}
    ChipType PeekMaxBet()const{return _maxbet;}
private:
    ChipType _maxbet;
};



#endif
