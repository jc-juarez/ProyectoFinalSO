# ProyectoFinalSO
Operative Systems Final Project
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

vector<double> FIFO(string str, int numPages){
  // FIFO Algorithm
  // Number of Pages is 5
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
  vector<double> res;
  double efficiency = (1.0-(double(fail)/double(str.size())))*100.0;
  res.push_back(fail);
  res.push_back(efficiency);
  return res;
}

vector<double> LRU(string str, int numPages){
  // LRU Algorithm
  unordered_map<char,int> nums; // Map for Allocating Processes and their last position 
  //Number of Pages is 5
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
  vector<double> res;
  double efficiency = (1.0-(double(fail)/double(str.size())))*100.0;
  res.push_back(fail);
  res.push_back(efficiency);
  return res; 
}

int main(){
  int option = 0;
  string str = "";
  char c = ' ';
  int r = 0;
  int numPages = 5;
  cout << "* Sistemas Operativos - Final Project *\n" << endl;
  // Both Algorithms run on 5 Page Frames
  while(true){ 
    // Create Random String
    str = "";
    int num=30;
    srand (time(NULL));    // initialize the random number generator
    for (int i=0; i<num; i++){    
        r = rand() % 10;   // generate a random number
        c = 'a' + r;            // Convert to a character from a-z
        c = toupper(c);
        str+=c;
    }
    
    //str = "7012030423032"; // String to analyze
    cout << "The Generated String is: " << str << endl;
    cout << "Options: " << endl;
    cout << "1) FIFO" << endl;
    cout << "2) LRU" << endl;
    cout << "3) Exit" << endl;
    cout << "Select the Algorithm to perform: ";
    cin >> option;
    cout << endl;
  if(option==1){
  vector<double> res = FIFO(str, numPages);
  cout << "String: " << str << endl;
  cout << "Page Frame Fails: " << int(res[0]) << endl;
  cout << "Efficiency: " << res[1] << "%" << endl;
  cout << endl;
  cout << "////////////////" << endl;
  cout << endl;
  }
  else if(option==2){
  vector<double> res = LRU(str, numPages);
  cout << "String: " << str << endl;
  cout << "Page Frame Fails: " << int(res[0]) << endl;
  cout << "Efficiency: " << res[1] << "%" << endl;
  cout << endl;
  cout << "////////////////" << endl;
  cout << endl;
  }
  else{
    cout << "LISTOS PARA EL 100!!!";
    break;
  }
  }
}
