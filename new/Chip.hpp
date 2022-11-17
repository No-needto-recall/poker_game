#ifndef _CTL_CHIP_HPP_
#define _CTL_CHIP_HPP_


using ChipType=int;

class Chip
{
public:
    Chip(ChipType chip=2000)
    :_chip(chip)
    {}
    ~Chip() {}

protected:
    ChipType _chip;

};

class Chips
:public Chip
{
public:
    Chips(ChipType chips=2000)
    :Chip(chips)
    {}
    ~Chips(){}
};

class Jackpot
:public Chip
{
public: 
    Jackpot(ChipType jackpot=0)
    :Chip(jackpot)
    {}
    ~Jackpot(){}
};



#endif
