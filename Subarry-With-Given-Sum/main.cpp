#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
pair<int, int> checkvec(vector<int> vec, int S);
int main() {
  pair<int, int> index;
  int T, N, S, temp;
  vector<int> vec;
  cin >> T;
  for(int i = 0; i < T ; i++){
    vec.clear();
    cin >> N >> S;
    for(int j = 0; j < N; j++)
    {
      cin >> temp;
      vec.push_back(temp);
    }
    index = checkvec(vec, S);
    cout << index.first;
    if(index.first >= 0)
    {
      cout << " " << index.second;   
    }
    cout << endl;
  }
}
pair<int, int> checkvec(vector<int> vec, int S){
  int sum = 0;
  int idx = 0;
  pair<int, int> ret;
  ret.first = -1;
  for(int i = 0; i < vec.size(); i++){
    sum += vec.at(i);
    if(sum > S)
    {
      sum = 0;
      idx++;
      i = idx-1;
    }
    if(sum == S)
    {
      ret.first = idx+1;
      ret.second = i+1;
      break;
    }
    
  }
  return ret;
}