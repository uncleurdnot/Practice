#ifndef SPECIALREG_ARRY_H
#define SPECIALREG_ARRY_H
#include <vector>
#include <iostream>
using namespace std;

class SpecialReg_ARRY
{
    public:
        SpecialReg_ARRY();
        SpecialReg_ARRY(string n)
        {
            name = n;
        }
        virtual ~SpecialReg_ARRY();

        vector<int> Getvals() { return vals; }
        void Setvals(vector<int> val) { vals = val; }
        string Getname() { return name; }
        void Setname(string val) { name = val; }

    protected:

    private:
        vector<int> vals;
        string name;
};

#endif // SPECIALREG_ARRY_H
