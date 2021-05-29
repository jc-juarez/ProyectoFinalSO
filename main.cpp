// Sistemas Operativos - Equipo 5
// Final Project - FIFO and LRU Algorithm
// Juan Carlos Juárez. A00824524.
// Alfredo José Welsh. A00825988.
// Ángel Limones. A00825333.

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <vector>
#include <queue>

using namespace std;

vector<int> FIFO(string str){
  // FIFO Algorithm
  int numPages = 5; // Number of Pages
  int fail = 0; // Number of Page Fails
  unordered_set<char> nums;
  queue<char> q;
  // Uses a queue to save Processes along a Set in order to lookup for the Processes in constant time
  for(char x : str){ // Traverses the string
    if(nums.size() < numPages){ // If set size less than Number of Pages
      if(!nums.count(x)){ // If the process not in set 
        fail++; //count fail
        nums.insert(x); //Insert the process 
        q.push(x); //And instert into the queue
      }
    }else{ //But, if the set size is equal to numpages, then
      if(!nums.count(x)){ // if the proces is not in the set
        fail++; //count a fail
        int currVal = 0; // is the var that i going to make pop in the queue
        currVal = q.front(); // to see the value in the front 
        q.pop(); // i make the pop
        nums.erase(currVal); // erase the value from the set
        q.push(x); // push current process into queue
        nums.insert(x); // insert the current process into the set
      }
    }  
  }
  vector<int> res;
  double efficiency = (1.0-(double(fail)/double(str.size())))*100.0;
  res.push_back(fail);
  res.push_back(efficiency);
  return res;
}

vector<int> LRU(string str){
  // LRU Algorithm
  unordered_map<char,int> nums; // Map for Allocating Processes and their last position 
  int numPages = 5; // Number of Pages
  int fail = 0; // Number of Page Fails 
  
  for(int i=0; i<str.size(); i++){ // Traverses the String and gets an Individual Process to analyze
    if(nums.size() < numPages){ // If Map size less than Number of Pages 
      if(!nums.count(str[i])) fail++; // If Process not in the Map then it is a Page Fail
      nums[str[i]] = i; // Sets new Process to closer position as it has been recently
    }else{ // Else If the Map Size is equal to the Number of Pages
      if(!nums.count(str[i])){ // If Process not in the Map
        fail++; // It is a Page Fail
         // We need to obtain the least seen one, which is the one with the greater distance
        int greater = INT_MIN; // Greater Variale to obtain greatest distance
        char greaterChar = ' '; // Greater Char Variable to obtain which Process corresponds to the greatest distance 
        for(auto &x : nums){ // Traverses the Map
          int currDist = i - x.second; // Obtain distance from last seen to current distance
          if(currDist > greater){ // If the distance is greater than the previously greater distance Update greater distance
            greater = currDist; // Save new greater distance
            greaterChar = x.first; // Save new greater Process
          }  
        }
        nums.erase(greaterChar); // Erase the greatest distance Process as it os the least recently used
        nums[str[i]] = i; // Sets new Process to closer position as it has been recently 
      }else{ // Else If Process in the Map
        nums[str[i]] = i; // Sets new Process to closer position as it has been recently  
      }  
    }
  } 
  vector<int> res;
  double efficiency = (1.0-(double(fail)/double(str.size())))*100.0;
  res.push_back(fail);
  res.push_back(efficiency);
  return res; 
}







int main(){

  //Por Extra Points Table
  //vector<char> nums;
  //int table[5][30];

  // Create Random String

  /*
  char c;
  int r;
  int num=30;
  srand (time(NULL));    // initialize the random number generator
  for (int i=0; i<num; i++){    
          r = rand() % 10;   // generate a random number
          c = 'a' + r;            // Convert to a character from a-z
          c = toupper(c);
          str+=c;
    }
  cout << str;
*/


  // FIFO Algorithm
  string str = "ABCDDECFADCBAFA"; // String to analyze
  

  cout << "String: " << str << endl;
  cout << "Frame Fails: " << fail << endl;
  cout << "Efficiency: " << res << "%";
  fail=0;




  // LRU Algorithm
/*
  unordered_map<char,int> nums; // Map for Allocating Processes and their last position 
  string str = ""; // String to analyze
  int numPages = 3; // Number of Pages
  int fail = 0; // Number of Page Fails

  for(int i=0; i<str.size(); i++){ // Traverses the String and gets an Individual Process to analyze
    if(nums.size() < numPages){ // If Map size less than Number of Pages 
      if(!nums.count(str[i])) fail++; // If Process not in the Map then it is a Page Fail
      nums[str[i]] = i; // Sets new Process to closer position as it has been recently
    }else{ // Else If the Map Size is equal to the Number of Pages
      if(!nums.count(str[i])){ // If Process not in the Map
        fail++; // It is a Page Fail
         // We need to obtain the least seen one, which is the one with the greater distance
        int greater = INT_MIN; // Greater Variale to obtain greatest distance
        char greaterChar = ' '; // Greater Char Variable to obtain which Process corresponds to the greatest distance 
        for(auto &x : nums){ // Traverses the Map
          int currDist = i - x.second; // Obtain distance from last seen to current distance
          if(currDist > greater){ // If the distance is greater than the previously greater distance Update greater distance
            greater = currDist; // Save new greater distance
            greaterChar = x.first; // Save new greater Process
          }  
        }
        nums.erase(greaterChar); // Erase the greatest distance Process as it os the least recently used
        nums[str[i]] = i; // Sets new Process to closer position as it has been recently 
      }else{ // Else If Process in the Map
        nums[str[i]] = i; // Sets new Process to closer position as it has been recently  
      }  
    }
  }


  cout << "String: " << str << endl;
  cout << "Frame Fails: " << fail << endl;
  double res = (1.0-(double(fail)/double(str.size())))*100.0;
  cout << "Efficiency: " << res << "%";
  fail=0;
  */
}
