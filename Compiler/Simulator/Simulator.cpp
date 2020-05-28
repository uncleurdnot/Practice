#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <vector>
#include "SPRContainer.h"
using namespace std;
int b2d(string b);
int findval(int n, vector<int> temp);
int main()
{
    bool fileopen = false;
    string opcode;
    string val;
    int ac = 0;
    int pc = 0;
    int i = 0;
    string reg;
    string sim;
    vector<int> looper;
    string ifile;
    ifstream fin;
    SPRContainer spr;
    vector<int> temp;

    map<string, int> Ans;

    Ans["00000000"] = 0;        //Didn't quite understand how substr() worked, I thought it was
    Ans["00000001"] = 0;        //string.substr(begin, end), instead of (begin,length), so I padded all
    Ans["00000010"] = 0;        //of these in an older version of the code to get them to work.
    Ans["00000011"] = 0;        //I could totally un-pad them, but there's no reason to do so as far as I can tell
    Ans["00000100"] = 0;        //program runs fine with them as is, and rewriting this section seems like more work than it's worth.
    Ans["00000101"] = 0;
    Ans["00000110"] = 0;
    Ans["00000111"] = 0;

    while(true)
    {
        while(!fileopen)
        {
            cout << "Please enter input file name:\t";
            getline(cin, ifile);
            fin.open(ifile);
            if(fin.fail())                  // always make sure the file was opened properly
            {
                cout << "File open failed\n";
                fin.clear();
                fin.ignore();
                continue;
            }
            fileopen = true;
            break;
        }
        while(!fin.eof())
        {
            fin >> sim;
            //cout << pc << ":\t";
            opcode = sim.substr(0,4);
            //cout << opcode << "\t";
            if(opcode == "0000") //STO
            {
                //cout << "STO";
                reg = sim.substr(4,8);
                Ans[reg] = ac;
                //cout << Ans[reg];
            }
            else if(opcode == "0001")//PUT
            {
                //cout << "PUT: ";
                val = sim.substr(4,8);
                reg = sim.substr(12,8);
                //cout << reg << "\t";
                Ans[reg] = b2d(val);
                //cout << Ans[reg];
            }
            else if(opcode == "0010")//OUT
            {
                //cout << "OUT: ";
                if(sim.substr(12,8) == "11111111")
                {
                    cout << Ans[sim.substr(4,8)];
                }
                else if(sim.substr(12,8) == "00000000")
                {
                    val = sim.substr(4,8);
                    cout << char(b2d(val));
                }
                else
                {
                    cout << ac;
                }
            }
            else if(opcode == "0011")//ADD
            {
                //cout << "ADD: ";
                reg = sim.substr(4,8);
                //cout << reg << "\t";
                ac += Ans[reg];
                //cout << "aaa" << endl;
            }
            else if(opcode == "0100")//SUB
            {
                reg = sim.substr(4,8);
                val = Ans[reg];
                ac -= b2d(val);
            }

            else if(opcode == "0110")//LOAD
            {
                reg = sim.substr(4,8);
                ac = Ans[reg];
            }

            else if(opcode == "0111") //INPUT
            {
                //cout << "INPUT!" << endl;
                cin >> ac;
                //cout << "aaa" << endl;
            }
            else if(opcode == "1000")//CLEAR
            {
                //cout << "CLEAR";
                Ans["00000000"] = 0;
                Ans["00000001"] = 0;
                Ans["00000010"] = 0;
                Ans["00000011"] = 0;
                Ans["00000100"] = 0;
                Ans["00000101"] = 0;
                Ans["00000110"] = 0;
                Ans["00000111"] = 0;
                spr.clear();
            }
            else if (opcode =="0101")//Halt
            {
                break;
            }
            else if (opcode == "1001")//LOOP
            {

                //cout << "LOOPING!" << endl;
                for(int i = 1; i < Ans[sim.substr(4,8)]; i++)
                {
                    //cout << "HERE" << endl;
                    looper.push_back(fin.tellg());
                    //cout << "LOOP: " << looper.at(0) << endl;
                }
            }
            else if (opcode == "1010") //LOOP_
            {
                if(looper.size() > 0)
                {
                    //cout << looper.at(0) << endl;
                    fin.seekg(looper.at(0)-16, fin.beg);//For some reason it was skipping a command.  Going back 16 bits fixes the issue.
                    looper.erase(looper.begin());
                }
            }
            else if (opcode == "1011")//ARRY
            {
                spr.add(sim.substr(4,8));
            }
            else if(opcode == "1101")//ADDARRY
            {
                reg = sim.substr(4,8);
                temp = spr.getlistitem(sim.substr(12,8)).Getvals();
                temp.push_back(Ans[reg]);
                spr.overwritelist(sim.substr(12,8), temp);

            }
            else if(opcode == "1100")//LOOK
            {
                temp = spr.getlistitem(sim.substr(4,8)).Getvals();
                if(sim.substr(12,8) == "11111111")
                {
                    cout << "Result:\t" << findval(ac, temp) << endl;
                }
                else
                {
                    cout << "Result:\t" << findval(Ans[sim.substr(12,8)], temp) << endl;
                }
            }
            else
            {
                cout << "An exception occurred.  Check the Assembler.  Maybe the function isn't matched to an opcode?  \nOPCODE:\t" << opcode << endl << "PC:\t" << pc << endl;
                throw std::exception();
            }
            pc++;
            //cout << endl;
        }
        cout << endl << endl << "Prorgam \"" << ifile << "\" ran successfully." << endl << endl;
        fileopen = false;
        fin.clear();
        fin.ignore();
        fin.close();
        cin.get();
    }
    return 0;
}
int b2d(string b)
{
    int d = 0;
    for(int i = b.size()- 1; i >= 0; i--)
    {
        if(b[i] == '1')
        {
            d += pow(2, 7-i);
        }
    }
    //cout << d << endl;
    return d;

}
int findval(int n, vector<int> temp)
{
    int found = -1;
    for(int i = 0; i < temp.size(); i++)
    {
        if(temp.at(i) == n)
        {
            found = i;
            break;
        }
    }
    return found;
}
