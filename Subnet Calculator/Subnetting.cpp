/*Quentin Minor
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;
vector<int> d2b(int d);
int b2d(string b);
class ipaddress {
public:
	ipaddress()
	{

	}
	ipaddress(string ip)
	{
		string temp;
		istringstream ss(ip);
		getline(ss, temp, '.');
		bit1 = stoi(temp);
		getline(ss, temp, '.');
		bit2 = stoi(temp);
		getline(ss, temp, '.');
		bit3 = stoi(temp);
		getline(ss, temp, '/');
		bit4 = stoi(temp);
		getline(ss, temp, '\n');
		slash = stoi(temp);
		if (bit1 <= 126)
		{
			ipc = 'A';
		}
		else if (bit1 <= 191)
		{
			ipc = 'B';
		}
		else if (bit1 <= 223)
		{
			ipc = 'C';
		}
		else if (bit1 <= 239)
		{
			ipc = 'D';
		}
		else
		{
			ipc = 'E';
		}
		snm = calcsubnetmask();
		subnet = calcsubnet();
	}
	vector<int> calcsubnetmask()
	{
		//cout << "SLASH:" << slash << endl;
		vector<int> subnetmask(slash, 1);
		//cout << subnetmask.size() << endl;
		while (subnetmask.size() < 32)
		{
			subnetmask.push_back(0);
		}
		return subnetmask;
	}
	vector<int> calcsubnet()
	{
		int temp;
		vector<int> tempvec, cvec;
		vector<int> ret(32, 0);
		cvec = d2b(bit1);
		tempvec = d2b(bit2);
		cvec.insert(cvec.end(), tempvec.begin(), tempvec.end());
		tempvec = d2b(bit3);
		cvec.insert(cvec.end(), tempvec.begin(), tempvec.end());
		tempvec = d2b(bit4);
		cvec.insert(cvec.end(), tempvec.begin(), tempvec.end());
		currip = cvec;
		for (int i = 0; i < ret.size(); i++)
		{
			if (cvec.at(i) == 1 && snm.at(i) == 1)
			{
				ret.at(i) = 1;
			}
		}
		vector<int> bcst(ret.begin(), ret.begin() + slash);
		while (bcst.size() < 32)
		{
			bcst.push_back(1);
		}
		subnetbcst = bcst;
		return ret;
	}
	void print()
	{
		cout << "Usable Hosts:\t" << pow(2, 32 - slash) - 2 << endl;
		cout << "Class:\t" << ipc << endl;
		cout << "Classfull Net Address:\t";
		if (ipc == 'A')
		{
			cout << bit1 << ".0.0.0" << endl;
		}
		else if (ipc == 'B')
		{
			cout << bit1 << "." << bit2 << ".0.0" << endl;
		}
		else if (ipc == 'C')
		{
			cout << bit1 << "." << bit2 << "." << bit3 << ".0" << endl;
		}
		cout << "Classfull Broadcast Address:\t";
		if (ipc == 'A')
		{
			cout << bit1 << ".255.255.255" << endl;
		}
		else if (ipc == 'B')
		{
			cout << bit1 << "." << bit2 << ".255.255" << endl;
		}
		else if (ipc == 'C')
		{
			cout << bit1 << "." << bit2 << "." << bit3 << ".255" << endl;
		}
		cout << "Subnet Mask:\t";
		string temp;
		for (int i = 0; i < 8; i++)
		{
			temp += to_string(snm.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 8; i < 16; i++)
		{
			temp += to_string(snm.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 16; i < 24; i++)
		{
			temp += to_string(snm.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 24; i < 32; i++)
		{
			temp += to_string(snm.at(i));
		}
		cout << b2d(temp) << endl;
		temp = "";
		cout << "Subnet Address:\t";
		for (int i = 0; i < 8; i++)
		{
			temp += to_string(subnet.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 8; i < 16; i++)
		{
			temp += to_string(subnet.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 16; i < 24; i++)
		{
			temp += to_string(subnet.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 24; i < 32; i++)
		{
			temp += to_string(subnet.at(i));
		}
		cout << b2d(temp) << endl;
		temp = "";



		cout << "Subnet Broadcast:\t";
		for (int i = 0; i < 8; i++)
		{
			temp += to_string(subnetbcst.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 8; i < 16; i++)
		{
			temp += to_string(subnetbcst.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 16; i < 24; i++)
		{
			temp += to_string(subnetbcst.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 24; i < 32; i++)
		{
			temp += to_string(subnetbcst.at(i));
		}
		cout << b2d(temp) << endl;
		temp = "";
		cout << "Host range within subnet:\t";
		for (int i = 0; i < 8; i++)
		{
			temp += to_string(subnet.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 8; i < 16; i++)
		{
			temp += to_string(subnet.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 16; i < 24; i++)
		{
			temp += to_string(subnet.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 24; i < 31; i++)
		{
			temp += to_string(subnet.at(i));
		}
		temp += "1";
		cout << b2d(temp);
		temp = "";

		cout << " to ";

		for (int i = 0; i < 8; i++)
		{
			temp += to_string(subnetbcst.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 8; i < 16; i++)
		{
			temp += to_string(subnetbcst.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 16; i < 24; i++)
		{
			temp += to_string(subnetbcst.at(i));
			//cout << snm.at(i);
		}
		cout << b2d(temp) << ".";
		temp = "";
		for (int i = 24; i < 31; i++)
		{
			temp += to_string(subnetbcst.at(i));
		}
		temp += "0";
		cout << b2d(temp) << endl;
		temp = "";
		vector<int> t1(currip.begin(), currip.begin() + slash);
		vector<int> t2(subnet.begin(), subnet.begin() + slash);
		if (currip != subnet && currip != subnetbcst && t1 == t2)
		{
			cout << "This is a valid host" << endl;
		}
		else
		{
			cout << "This is not a valid host" << endl;
		}
	}
	friend ostream& operator <<(ostream& os, const ipaddress& ip)
	{
		os << ip.bit1 << "." << ip.bit2 << "." << ip.bit3 << "." << ip.bit4 << "/" << ip.slash << endl;
		return os;
	}
	int bit1 = 0;
	int bit2 = 0;
	int bit3 = 0;
	int bit4 = 0;
	int slash = 32;
	char ipc;
	vector<int> snm;
	vector<int> subnet;
	vector<int> subnetbcst;
	vector<int> currip;
};

int main() {
	string ip;
	cout << "Input IP:\t";
	getline(cin, ip);
	ipaddress CalcIP(ip);
	cout << endl << CalcIP;
	CalcIP.print();
}
int b2d(string b)  //Converts Binary Numbers (Strings) to Decimal Numbers
{
	int d = 0;
	for (int i = b.size() - 1; i >= 0; i--)
	{
		if (b[i] == '1')
		{
			d += pow(2, 7 - i);
		}
	}
	return d;

}
vector<int> d2b(int d) //Converts Decimal numbers to Binary Numbers (As a vector of Ints)
{
	if (d > 255)
	{
		cout << "An exception occurred.  Integer values are accepted up to 255.  Larger values cannot be processed." << endl;
		throw std::exception();
	}
	vector<int> b;
	for (int i = 0; i < 8; i++)
	{
		b.insert(b.begin(), d % 2);
		d = d / 2;
	}
	return b;
}