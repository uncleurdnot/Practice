#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
using namespace std;
vector<int> d2b(int d);
ostream& operator<<(ostream& os, const vector<int>& v);
string r2b(string Reg);

int main()
{
    int arryfound = -1;
    ifstream fin;
    string ifile;
    vector<string> arrays;
    while(true)
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
        break;
    }
    string ofile;
    cout << "Please enter output file name:\t";
    getline(cin, ofile);
    ofstream out(ofile);          // the file generated with 0s and 1s
    string opcode;                  // store the instruction in opcode
    int lc = 1;                     //trace what line our code is on
    int n;                          // if i need to store a number from the instruction
    string reg;                   // if i am reading a register. Note I have 8 registered
                                  // which i call: R1, R2, R3, R4, R5, R6, R7, and R8.
    int open_loop = 0;
    while(!fin.eof())                   // while not reached end of file
    {
        fin >> opcode;
        //cout << opcode << endl;
        if(opcode.substr(0,2) == "//") //Check for comment
        {
            while(opcode != "./")
            {
                fin >> opcode;
            }
            opcode = "";
            continue;
        }
        else
        {
            //out << opcode << "\t";
        }
        if(opcode == "STO")
        {
            out << "0000";
            fin >> reg;
            out << r2b(reg) << "00000000" << endl;
        }
        else if(opcode == "PUT")
        {
            out << "0001";
            fin >> n;
            out << d2b(n);
            //out << " ";
            fin >> reg;
            out << r2b(reg);
            out << endl;
        }

        else if(opcode == "OUT")
        {
            fin >> reg;
            if(reg == "`")//This is text
            {
                reg = "";
                while(reg != "`")
                {
                    fin >> reg;
                    if(reg == "`")
                    {
                        break;
                    }
                    for(int i = 0; i < reg.size(); i++)
                    {
                        if(reg[i] == '\\')
                        {
                            if(reg[i+1] == 't')
                            {
                                out << "0010" << d2b(int('\t')) << "00000000" << endl;
                                i++;
                                continue;
                            }
                            else if(reg[i+1] == 'n')
                            {
                                out << "0010" << d2b(int('\n')) << "00000000" << endl;
                                i++;
                                continue;
                            }
                            else if(reg[i+1] == '\\')
                            {
                                out << "0010" << d2b(int('\\')) << "00000000" << endl;
                                i++;
                                continue;
                            }
                        }
                        out << "0010" << d2b(int(reg[i])) << "00000000" << endl;
                    }
                    out << "0010" << "00100000" << "00000000" << endl;
                }

            }
            else if(reg[0] == 'R') //This is a register
            {
                out << "0010" << r2b(reg) << "11111111" << endl;
            }
            else
            {
                out << "0010" << "00000000" << "00000001" << endl;
            }
        }

        else if(opcode == "ADD")
        {
            out << "0011";
            fin >> reg;
            out << r2b(reg);
            out << "00000000" << endl;
        }

        else if(opcode == "SUB")
        {
            out << "0100";
            fin >> reg;
            out << r2b(reg);
            fin >> reg;
            out << r2b(reg);
            out << endl;
        }

        else if(opcode == "HALT")
        {
            out << "0101" << "00000000" << "00000000" << endl;
        }

        else if(opcode == "LOAD")
        {
            out << "0110";
            fin >> reg;
            out << r2b(reg) << "00000000" << endl;

        }

        else if(opcode == "INPUT")
        {
            out << "0111" << "00000000" << "00000000" << endl;
        }

        else if(opcode == "CLEAR")
        {
            out << "1000" << "00000000" << "00000000" << endl;
        }

        else if(opcode == "LOOP")
        {
            open_loop += 1;
            out << "1001";
            fin >> reg;
            out << r2b(reg);
            out << "00000000" << endl;
        }

        else if(opcode == "LOOP_")
        {
            open_loop -= 1;
            out << "1010" << "00000000" << "00000000" << endl;
        }
        else if(opcode == "ARRY")
        {
            out << "1011";
            fin >> reg;
            //cout << reg << endl;
            for(int i = 0; i < arrays.size(); i++)
            {
                if(arrays.at(i) == reg)
                {
                    cout << "You have an error in your ARRY code.  Specifically, you've defined the same array twice!\n Error at line " << lc << endl;
                    throw std::exception();
                }
            }
            arrays.push_back(reg);
            out << d2b(arrays.size()-1) << "00000000" << endl;
            //cout << d2b(arrays.size()-1) << endl;
        }
        else if(opcode == "ADDARRY")
        {
            out << "1101";
            fin >> reg;
            out << r2b(reg);
            fin >> reg;
            for(int i = 0; i < arrays.size(); i++)
            {
                if(arrays.at(i) == reg)
                {
                    arryfound = i;
                    break;
                }
            }
            if(arryfound < 0)
            {
                cout << "You have an error in your ARRY code.  Specifically, You haven't declared the array \"" << reg << "\"!\n Error at line " << lc << endl;
                throw std::exception();
            }
            else
            {
                out << d2b(arryfound) << endl;
                arryfound = -1;
            }
        }
        else if(opcode == "DELARY")
        {
            out << "1110";
            fin >> n;
            out << d2b(n);
            out << "00000000" << endl;
        }
        else if(opcode == "LOOK")
        {

            out << "1100";
            fin >> reg;
            for(int i = 0; i < arrays.size(); i++)
            {
                if(arrays.at(i) == reg)
                {
                    arryfound = i;
                    break;
                }
            }
            if(arryfound < 0)
            {
                cout << "You have an error in your ARRY code.  Specifically, You haven't declared the array \"" << reg << "\"!\n Error at line " << lc << endl;
                throw std::exception();
            }
            else
            {
                out << d2b(arryfound);
                arryfound = -1;
            }
            if(fin.peek() == 'R')
            {
                fin >> reg;
                out << r2b(reg) << endl;
            }
            else
            {
                out << "11111111" << endl;
            }

        }
        else
        {
            cout << "An exception occurred.  There is a bug in the assembly code at line " << lc << "." << endl;
            throw std::exception();
        }
        lc++;
    }
    if(open_loop != 0)
    {
        cout << "An exception occurred.  You have " << open_loop << " LOOP commands without a LOOP_ closing statement." << endl;
        throw std::exception();
    }
    fin.close();
    out.close();
    cout << "File generated successfully" << endl;
    return 0;
}
vector<int> d2b(int d)
{
    if(d > 255)
    {
      cout << "An exception occurred.  Integer values are accepted up to 255.  Larger values cannot be processed." << endl;
      throw std::exception();
    }
    vector<int> b;
    for(int i = 0; i < 8; i++)
    {
        b.insert(b.begin(), d%2);
        d = d/2;
    }
    return b;
}
ostream& operator<<(ostream& os, const vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << v[i];
    }
    return os;
}
string r2b(string Reg)
{
    map<string, string> Ans;

    Ans["R1"] = "00000000";
    Ans["R2"] = "00000001";
    Ans["R3"] = "00000010";
    Ans["R4"] = "00000011";
    Ans["R5"] = "00000100";
    Ans["R6"] = "00000101";
    Ans["R7"] = "00000110";
    Ans["R8"] = "00000111";

    return Ans[Reg];
}
