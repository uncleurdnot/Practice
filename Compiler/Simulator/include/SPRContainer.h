#ifndef SPRCONTAINER_H
#define SPRCONTAINER_H
#include "SpecialReg_ARRY.h"
using namespace std;
class SPRContainer
{
    public:
        SPRContainer();
        virtual ~SPRContainer();
        SpecialReg_ARRY getlistitem(string n)
        {
            SpecialReg_ARRY listitem;
            for(int i = 0; i < list.size(); i++)
            {
                if(list.at(i).Getname() == n)
                {
                    listitem = list.at(i);
                    break;
                }
            }
            return listitem;
        }
        void overwritelist(string n, vector<int> newarr)
        {
            for(int i = 0; i < list.size(); i++)
            {
                if(list.at(i).Getname() == n)
                {
                    list.at(i).Setvals(newarr);
                    break;
                }
            }
        }
        void add(string n)
        {
            SpecialReg_ARRY temp = SpecialReg_ARRY(n);
            list.push_back(temp);
        }
        void clear()
        {
            vector<SpecialReg_ARRY> n;
            list = n;
        }
    protected:

    private:
        vector<SpecialReg_ARRY> list;
};

#endif // SPRCONTAINER_H
