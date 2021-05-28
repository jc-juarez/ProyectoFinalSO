// Sistemas Operativos - Equipo 5
// FIFO and LRU Algorithm

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits.h>

using namespace std;

int main(){

  //Por Extra Points Table
  //vector<char> nums;
  //int table[5][30];

  unordered_map<char,int> nums; 
  string str = "ABCDDGADCBECFAFGAABCD";
  int numPages = 3;
  int fail = 0;

  for(int i=0; i<str.size(); i++){
    if(nums.size() < numPages){
      if(!nums.count(str[i])) fail++;
      nums[str[i]] = i;
    }else{
      if(!nums.count(str[i])){
        fail++;
        int greater = INT_MIN;
        char greaterChar = ' ';
        for(auto &x : nums){
          int currDist = i - x.second;
          if(currDist > greater){
              greater = currDist;
              greaterChar = x.first;
          }  
        }
        nums.erase(greaterChar);
        nums[str[i]] = i;
      }else{
        nums[str[i]] = i;
      }  
    }
  }
  cout << "String: " << str << endl;
  cout << "Frame Fails: " << fail << endl;
  double res = (1.0-(double(fail)/double(str.size())))*100.0;
  cout << "Efficiency: " << res << "%";
  return 0;
}
