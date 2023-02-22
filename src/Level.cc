#include "Level.hpp"

LevelType Level::GetLevel(Cards keycards)
{
    GROUP_CARDS::SortCardsNum(keycards);
    string ftmp=LEVEL::CardsToString(keycards);
    auto ret=_cardsmap.find(ftmp);
    if(ret==_cardsmap.end())
    {
        cerr<<"not find in map "<<endl;
        GroupCards tmp(5);
        tmp.ReturnCards()=keycards;
        GROUP_CARDS::PrintCards(tmp);
        exit(1);
    }else{
        return ret->second;
    }
}

string LEVEL::CardsToString(Cards cards)
{
    //一组牌转化为字符串
    //“.”表示卡牌描述结束
    string Str;
    Str.reserve(20);
    for (auto &rc : cards)
    {

        char tmp = static_cast<char>(rc.GetColour() * 13 + rc.GetNum() - 2);
        Str += tmp;
    }
    Str.shrink_to_fit();
    return Str;
}
Cards LEVEL::StringToCards(string str)
{
    Cards tmp;
    for (auto &rs : str)
    {
        Card tmp0(rs);
        tmp.push_back(tmp0);
    }
    return tmp;
}

void Level::CreatMap()
{
    auto c_start=std::clock();
    CreatMapRoyalFlush();
    CreatMapStraightFlush();
    CreatMapFourOfAKind();
    CreatMapFullHouse();
    CreatMapFlush();
    CreatMapStraight();
    CreatMapThreeOfAKind();
    CreatMapTwoPair();
    CreatMapOnePair();
    CreatMapHighCard();
    auto c_end=std::clock();
    cout<<"time use :"<<1000*(c_end-c_start)/CLOCKS_PER_SEC<<" ms\n";
    cout<<"map.size:"<<_cardsmap.size()<<endl;

}
void Level::CreatMapRoyalFlush()
{
    int lv = 1;
    lv = 1;
    //对皇家同花顺
    for (int i = 0; i < 4; ++i)
    {
        char ch0 = i * 13 + 0;  // 2
        char ch1 = i * 13 + 1;  // 3
        char ch2 = i * 13 + 2;  // 4
        char ch3 = i * 13 + 3;  // 5
        char ch4 = i * 13 + 12; // A
        char ch5 = i * 13 + 8;  // 10
        char ch6 = i * 13 + 9;  // J
        char ch7 = i * 13 + 10; // Q
        char ch8 = i * 13 + 11; // K
        string tmp({ch5, ch6, ch7, ch8, ch4});
        _cardsmap.insert({tmp, lv});
        string tmp2({ch0, ch1, ch2, ch3, ch4});
        _cardsmap.insert({tmp2, lv + 1});
    }
}
void Level::CreatMapStraightFlush()
{
    int lv = 2;
    //对同花顺；
    for (int i = 0; i < 4; ++i)
    {
        char colour = i * 13;
        for (int j = 12; j >= 4; --j)
        {
            char numS = j;
            char card0 = colour + numS, card1 = card0 - 4, card2 = card0 - 3, card3 = card0 - 2, card4 = card0 - 1;
            string tmp({card1, card2, card3, card4, card0});
            _cardsmap.insert({tmp, ++lv});
        }
        lv = 2;
    }
    lv = 2 + 9;
    for (int i = 0; i < 4; ++i)
    {
        char colour = i * 13;
        char card = colour + 0, card1 = colour + 1, card2 = colour + 2, card3 = colour + 3;
        char cardA = colour + 12;
        string tmp({card, card1, card2, card3, cardA});
        _cardsmap.insert({tmp, lv});
    }
}
void Level::CreatMapFourOfAKind()
{
    // lv=2+9+1;
    int lv = 12;
    //四条
    for (int i = 12; i >= 0; --i)
    {
        char nums = i, nums1 = nums + 13, nums2 = nums1 + 13, nums3 = nums2 + 13;
        string tmp;
        tmp.resize(4);
        tmp[0] = nums;
        tmp[1] = nums1;
        tmp[2] = nums2;
        tmp[3] = nums3;
        for (int j = 0; j < 4; ++j)
        {
            char colour = j;
            for (int k = 12; k >= 0; --k)
            {
                if (k == i)
                {
                    continue;
                }
                char card = colour * 13 + k;
                string use;
                if (i > k)
                {
                    use = card + tmp;
                }
                else
                {
                    use = tmp + card;
                }
                _cardsmap.insert({use, ++lv});
            }
            lv -= 12;
        }
        lv += 12;
    }
}
void Level::CreatMapFullHouse()
{
    // lv=2+9+1+12*13;
    int lv = 168;
    //葫芦
    char colourarr[4] = {0, 13, 26, 39};
    for (int i = 12; i >= 0; --i)
    {
        char num0 = i;
        for (int c1 = 0; c1 <= 4 - 3; ++c1)
        {
            for (int c2 = c1 + 1; c2 <= 4 - 3 + 1; ++c2)
            {
                for (int c3 = c2 + 1; c3 <= 4 - 3 + 2; ++c3)
                {
                    char num1 = num0 + colourarr[c1];
                    char num2 = num0 + colourarr[c2];
                    char num3 = num0 + colourarr[c3];
                    for (int s1 = 0; s1 <= 4 - 2; ++s1)
                    {
                        for (int s2 = s1 + 1; s2 <= 4 - 2 + 1; ++s2)
                        {
                            for (int k = 12; k >= 0; --k)
                            {
                                if (k == i)
                                {
                                    continue;
                                }
                                char num4 = k + colourarr[s1];
                                char num5 = k + colourarr[s2];
                                if (k > i)
                                {
                                    string use({num1, num2, num3, num4, num5});
                                    _cardsmap.insert({use, ++lv});
                                }
                                else
                                {
                                    string use({num4, num5, num1, num2, num3});
                                    _cardsmap.insert({use, ++lv});
                                }
                            }
                            lv -= 12;
                        }
                    }
                }
            }
        }
        lv += 12;
    }
}
void Level::CreatMapFlush()
{
    // lv=2+10+156+156;
    int lv = 324;
    //同花
    for (int co = 0; co < 4; ++co)
    {
        char colour = co * 13;
        int timetmp = 0;
        for (int n1 = 12; n1 >= 4; --n1)
        {
            for (int n2 = n1 - 1; n2 >= 3; --n2)
            {
                for (int n3 = n2 - 1; n3 >= 2; --n3)
                {
                    for (int n4 = n3 - 1; n4 >= 1; --n4)
                    {
                        for (int n5 = n4 - 1; n5 >= 0; --n5)
                        {
                            if (n5 + 1 == n4 && n4 + 1 == n3 && n3 + 1 == n2 && n2 + 1 == n1)
                            {
                                continue;
                            }
                            if (n5 == 0 &&n5 + 1 ==n4 &&n4 + 1 == n3 &&n3 + 1 == n2 &&n1 == 12)
                            {
                                continue;
                            }
                            char card0 = n5 + colour;
                            char card1 = n4 + colour;
                            char card2 = n3 + colour;
                            char card3 = n2 + colour;
                            char card4 = n1 + colour;
                            //隐含n1>n2>n3>n4>n5;
                            string tmp({card0, card1, card2, card3, card4});
                            // tmp需要排除顺子的可能
                            _cardsmap.insert({tmp, ++lv});
                            ++timetmp;
                        }
                    }
                }
            }
        }
        lv -= timetmp;
    }
}
void Level::CreatMapStraight()
{
    // lv=324+1287-10;
    int lv = 1601;
    //顺子
    for (int num4 = 12; num4 >= 4; --num4)
    {
        ++lv;
        for (int colour4 = 0; colour4 < 4; ++colour4)
        {
            char card4 = num4 + colour4 * 13; //第五张牌
            for (int colour3 = 0; colour3 < 4; ++colour3)
            {
                char card3 = num4 - 1 + colour3 * 13; //第四张牌
                for (int colour2 = 0; colour2 < 4; ++colour2)
                {
                    char card2 = num4 - 2 + colour2 * 13; //第三张牌
                    for (int colour1 = 0; colour1 < 4; ++colour1)
                    {
                        char card1 = num4 - 3 + colour1 * 13; //第二张牌
                        for (int colour0 = 0; colour0 < 4; ++colour0)
                        {
                            if (colour0 == colour1 && colour1 == colour2 &&
                                colour2 == colour3 && colour3 == colour4)
                            {
                                continue;
                            }
                            char card0 = num4 - 4 + colour0 * 13;
                            string tmp({card0, card1, card2, card3, card4});
                            _cardsmap.insert({tmp, lv});
                        }
                    }
                }
            }
        }
    }
    ++lv;
    for (int colour4 = 0; colour4 < 4; ++colour4)
    {
        char card4 = 12 + colour4 * 13; //第五张牌 A
        for (int colour3 = 0; colour3 < 4; ++colour3)
        {
            char card3 = 3 + colour3 * 13; //第四张牌 5
            for (int colour2 = 0; colour2 < 4; ++colour2)
            {
                char card2 = 2 + colour2 * 13; //第三张牌 4
                for (int colour1 = 0; colour1 < 4; ++colour1)
                {
                    char card1 = 1 + colour1 * 13; //第二张牌 3
                    for (int colour0 = 0; colour0 < 4; ++colour0)
                    {
                        if (colour0 == colour1 && colour1 == colour2 &&
                            colour2 == colour3 && colour3 == colour4)
                        {
                            continue;
                        }
                        char card0 = 0 + colour0 * 13; //第一张牌 2
                        string tmp({card0, card1, card2, card3, card4});
                        _cardsmap.insert({tmp, lv});
                    }
                }
            }
        }
    }
}
void Level::CreatMapThreeOfAKind()
{
    // lv=1601+10;
    int lv = 1611;
    //三条YX1X2
    for (int numY = 12; numY >= 0; --numY)
    { //确定三张点数一样的牌的点数
        for (int co1 = 0; co1 <= 4 - 3; ++co1)
        {
            for (int co2 = co1 + 1; co2 <= 4 - 3 + 1; ++co2)
            {
                for (int co3 = co2 + 1; co3 <= 4 - 3 + 2; ++co3)
                {
                    char card0 = numY + co1 * 13;
                    char card1 = numY + co2 * 13;
                    char card2 = numY + co3 * 13;
                    string tmpY({card0, card1, card2}); //一组三张点数一样的牌
                    //从剩余的12中选两个点数出来
                    for (int num1 = 12; num1 >= 1; --num1)
                    {
                        if (num1 == numY)
                        {
                            continue;
                        }
                        for (int num2 = num1 - 1; num2 >= 0; --num2)
                        {
                            if (num2 == numY)
                            {
                                continue;
                            }
                            ++lv;
                            for (int colour1 = 0; colour1 < 4; ++colour1)
                            {
                                for (int colour2 = 0; colour2 < 4; ++colour2)
                                {
                                    char cardX1 = num1 + colour1 * 13;
                                    char cardX2 = num2 + colour2 * 13;
                                    string tmpX1({cardX1});
                                    string tmpX2({cardX2});
                                    string tmp;
                                    //隐含num2<num1;
                                    if (numY < num2)
                                    {
                                        tmp = tmpY + tmpX2 + tmpX1;
                                    }
                                    else if (numY < num1)
                                    {
                                        tmp = tmpX2 + tmpY + tmpX1;
                                    }
                                    else
                                    {
                                        tmp = tmpX2 + tmpX1 + tmpY;
                                    }
                                    _cardsmap.insert({tmp, lv});
                                }
                            }
                        }
                    }
                    lv -= 66;
                }
            }
        }
        lv += 66;
    }
}
void Level::CreatMapTwoPair()
{
    // lv=1611+66*13;
    int lv = 2469;
    //两对 从13种数号中选2种
    for (int numY1 = 12; numY1 >= 1; --numY1) //大的对子
    {
        for (int numY2 = numY1 - 1; numY2 >= 0; --numY2) //小的对子
        {
            for (int colour1 = 0; colour1 <= 4 - 2; ++colour1)
            {
                for (int colour2 = colour1 + 1; colour2 <= 4 - 2 + 1; ++colour2)
                {
                    for (int colour3 = 0; colour3 <= 4 - 2; ++colour3)
                    {
                        for (int colour4 = colour3 + 1; colour4 <= 4 - 2 + 1; ++colour4)
                        {
                            //确定两对每张牌的花色
                            char card0 = numY1 + colour1 * 13;
                            char card1 = numY1 + colour2 * 13;
                            //隐含colour2>colour1
                            string tmpY1({card0, card1});
                            char card2 = numY2 + colour3 * 13;
                            char card3 = numY2 + colour4 * 13;
                            string tmpY2({card2, card3});
                            for (int numX = 12; numX >= 0; --numX)
                            {
                                if (numX == numY1 || numX == numY2)
                                {
                                    continue;
                                }
                                ++lv;
                                for (int colour5 = 0; colour5 < 4; ++colour5)
                                {
                                    char card4 = numX + colour5 * 13;
                                    string tmpX({card4});
                                    //隐含numY1>numY2;
                                    string tmp;
                                    if (numX > numY1)
                                    {
                                        tmp = tmpY2 + tmpY1 + tmpX;
                                    }
                                    else if (numX > numY2)
                                    {
                                        tmp = tmpY2 + tmpX + tmpY1;
                                    }
                                    else
                                    {
                                        tmp = tmpX + tmpY2 + tmpY1;
                                    }
                                    _cardsmap.insert({tmp, lv});
                                }
                            }
                            lv -= 11;
                        }
                    }
                }
            }
            lv += 11;
        }
    }
}
void Level::CreatMapOnePair()
{
    // lv=2469+78*11;
    int lv = 3327;
    //一对
    for (int numY = 12; numY >= 0; --numY) //对子的数号
    {
        for (int colour1 = 0; colour1 <= 4 - 2; ++colour1)
        {
            for (int colour2 = colour1 + 1; colour2 <= 4 - 2 + 1; ++colour2)
            {
                //确定对子的花色组合
                char card0 = numY + colour1 * 13;
                char card1 = numY + colour2 * 13;
                string tmpY({card0, card1});
                //从剩余的12中选出3个点数出来
                for (int num1 = 12; num1 >= 2; --num1)
                {
                    for (int num2 = num1 - 1; num2 >= 1; --num2)
                    {
                        for (int num3 = num2 - 1; num3 >= 0; --num3)
                        {
                            if (num1 == numY || num2 == numY || num3 == numY)
                            {
                                continue;
                            }
                            ++lv;
                            for (int colour3 = 0; colour3 < 4; ++colour3)
                            {
                                for (int colour4 = 0; colour4 < 4; ++colour4)
                                {
                                    for (int colour5 = 0; colour5 < 4; ++colour5)
                                    {
                                        char card2 = num1 + colour3 * 13;
                                        string tmpX1({card2});
                                        char card3 = num2 + colour4 * 13;
                                        string tmpX2({card3});
                                        char card4 = num3 + colour5 * 13;
                                        string tmpX3({card4});
                                        string tmp;
                                        //隐含num3<num2<num1
                                        if (numY < num3)
                                        {
                                            tmp = tmpY + tmpX3 + tmpX2 + tmpX1;
                                        }
                                        else if (numY < num2)
                                        {
                                            tmp = tmpX3 + tmpY + tmpX2 + tmpX1;
                                        }
                                        else if (numY < num1)
                                        {
                                            tmp = tmpX3 + tmpX2 + tmpY + tmpX1;
                                        }
                                        else
                                        {
                                            tmp = tmpX3 + tmpX2 + tmpX1 + tmpY;
                                        }
                                        _cardsmap.insert({tmp, lv});
                                    }
                                }
                            }
                        }
                    }
                }
                lv -= 220;
            }
        }
        lv += 220;
    }
}
void Level::CreatMapHighCard()
{
    // lv=3327+220*13;
    int lv = 6187;
    //高牌
    int times = 0;
    for (int numX1 = 12; numX1 >= 4; --numX1)
    {
        for (int numX2 = numX1 - 1; numX2 >= 3; --numX2)
        {
            for (int numX3 = numX2 - 1; numX3 >= 2; --numX3)
            {
                for (int numX4 = numX3 - 1; numX4 >= 1; --numX4)
                {
                    for (int numX5 = numX4 - 1; numX5 >= 0; --numX5)
                    {
                        if (numX5 + 1 == numX4 && numX4 + 1 == numX3 &&
                            numX3 + 1 == numX2 && numX2 + 1 == numX1)
                        {
                            continue;
                        }
                        if (numX5 == 0 && numX5 + 1 == numX4 && numX4 + 1 == numX3 &&
                            numX3 + 1 == numX2 && numX1 == 12)
                        {
                            continue;
                        }
                        ++lv;
                        times = 0;
                        for (int colour1 = 0; colour1 < 4; ++colour1)
                        {
                            for (int colour2 = 0; colour2 < 4; ++colour2)
                            {
                                for (int colour3 = 0; colour3 < 4; ++colour3)
                                {
                                    for (int colour4 = 0; colour4 < 4; ++colour4)
                                    {
                                        for (int colour5 = 0; colour5 < 4; ++colour5)
                                        {
                                            if (colour1 == colour2 && colour2 == colour3 &&
                                                colour3 == colour4 && colour4 == colour5)
                                            {
                                                continue;
                                            }
                                            char card0 = numX1 + colour1 * 13;
                                            char card1 = numX2 + colour2 * 13;
                                            char card2 = numX3 + colour3 * 13;
                                            char card3 = numX4 + colour4 * 13;
                                            char card4 = numX5 + colour5 * 13;
                                            //隐含numX5<numX4<numX3<numX2<numX1
                                            string tmp({card4, card3, card2, card1, card0});
                                            _cardsmap.insert({tmp, lv});
                                        }
                                    }
                                }
                            }
                        }
                        //会跳过同花顺，同花，顺子
                    }
                }
            }
        }
    }
}

void Level::ShowMap()
{
    GroupCards tmp(5);
    int times = 0;
    for (auto &rm : _imagemap)
    {
        cout << "Lv:" << rm.first << endl;
        for (auto &rv : rm.second)
        {
            tmp.ReturnCards() = LEVEL::StringToCards(rv);
            GROUP_CARDS::PrintCards(tmp);
            cout << endl;
            break;
        }
        ++times;
        if (times == 100)
        {
             cin>>times;
        }
    }
}

void Level::ImageMap()
{
    for (auto &rm : _cardsmap)
    {
        _imagemap[rm.second].push_back(rm.first);
    }
}

void Level::LoadMapFromFile()
{
    FILE* fp=std::fopen("../data/levelmap.dat","rb");
    if(!fp)
    {
        cerr<<"File opening failed in load"<<endl;
        cerr<<"start creat cardmap \n";
        CreatMap();
        cerr<<"start creat levelmap.dat \n";
        WriteMapToFile();
        return;
    }
    
    /* int times=0; */
    char tmp[5]={0};
    LevelType tmp2;
    cout<<"start load levelmap.dat "<<endl;
    auto c_start=std::clock();
    while(1){
        
        auto ret=std::fread(&tmp,sizeof(tmp),1,fp);
        string stmp({tmp[0],tmp[1],tmp[2],tmp[3],tmp[4]});
        auto ret2=std::fread(&tmp2,sizeof(tmp2),1,fp);
        if(ret==0&&ret2==0)
        {
            /* cout<<endl; */
            break;
        }
        auto retm=_cardsmap.insert({stmp,tmp2}).second;
        if(!retm){
            cerr<<"load map lose\n";
            exit(1);
        }
        /* ++times; */
        /* cout<<"\r"<<times; */
    }
    auto c_end=std::clock();
    cout<<"time use :"<<1000*(c_end-c_start)/CLOCKS_PER_SEC<<" ms\n";
    cout<<"map.size:"<<_cardsmap.size()<<endl;
    std::fclose(fp);

}

void Level::WriteMapToFile(){
    FILE* fp=std::fopen("../data/levelmap.dat","wb");
    if(!fp)
    {
        cerr<<"File opening failed in write"<<endl;
        exit(1);
    }

    int times=0;
    for(auto &rm:_cardsmap)
    {
        std::fwrite(rm.first.c_str(),rm.first.size(),1,fp);
        std::fwrite(&rm.second,sizeof(rm.second),1,fp);
       ++times; 
       cout<<"\r"<<times;
    }
    cout<<endl;
    std::fclose(fp);
    
}
