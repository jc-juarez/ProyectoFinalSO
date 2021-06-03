 // Sistemas Operativos - Equipo 5.
// Final Project - FIFO and LRU Algorithm.
// June 6th 2021.
// Juan Carlos Juárez. A00824524.
// Alfredo José Welsh. A00825988.
// Ángel Limones. A00825333.

/* *READ ME*

<!>The Following Program recreates FIFO and LRU Page Replacement Algorithms.

<!>How to Run the Program
Step 1 - Execute the Program in a C++ IDE
Step 2 - A Menu Option will appear. The program will generate a Random Stream of Processes, then you can select which Algorithm to perform; Enter 1 for FIFO, Enter 2 for LRU. After selecting the Algorithm the number of Fails and Efficiency will be given.
Step 3 - If you wish to exit, Enter 3.

*/

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
    if(nums.size() < numPages){ // If the set size less than Number of Pages
      if(!nums.count(x)){ // If the process not in set 
        fail++; // Count fail
        nums.insert(x); // Insert the process into the set
        q.push(x); //And instert it into the queue
      }
    }else{ //Else if the set size is equal to numpages
      if(!nums.count(x)){ // If the proces is not in the set
        fail++; //Count fail
        int currVal = 0; // The Process to Eliminate from the Set and Queue
        currVal = q.front(); // Obtain the Value in Front 
        q.pop(); // Pops Value from Queue
        nums.erase(currVal); // Erase Value from the set
        q.push(x); // Push current process into queue
        nums.insert(x); // Insert the current process into the set
      }
    }  
  }
  vector<double> res;
  double efficiency = (1.0-(double(fail)/double(str.size())))*100.0; // Efficiecy = (1-(fails/size))*100
  res.push_back(fail);
  res.push_back(efficiency);
  return res; // Obtain result with number of fails and efficiency
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
  double efficiency = (1.0-(double(fail)/double(str.size())))*100.0; // Efficiecy = (1-(fails/size))*100
  res.push_back(fail);
  res.push_back(efficiency);
  return res; // Obtain result with number of fails and efficiency
}

int main(){
  int option = 0; // Menu Option
  string str = ""; // String to Generate
  char c = ' '; // Used to Generate Random String
  int r = 0; // Used to Generate Randon Number
  int numPages = 5; // Number of Page Frames, always 5
  cout << "\n* Sistemas Operativos - Final Project *\n" << endl;
  // Both Algorithms run on 5 Page Frames
  while(true){ 
    // Create Random String
    str = "";
    int num=30;
    srand (time(NULL));    
    for (int i=0; i<num; i++){    
        r = rand() % 10;  
        c = 'a' + r;           
        c = toupper(c);
        str+=c;
    }
    cout << "The Random Generated String is: " << str << endl;
    cout << "Options: " << endl;
    cout << "1) FIFO" << endl;
    cout << "2) LRU" << endl;
    cout << "3) Exit" << endl;
    cout << "Select the Algorithm to perform: ";
    cin >> option;
    cout << endl;
  if(option==1){ // FIFO
  vector<double> res = FIFO(str, numPages);
  cout << "String: " << str << endl;
  cout << "Page Frame Fails: " << int(res[0]) << endl;
  cout << "Efficiency: " << res[1] << "%" << endl;
  cout << endl;
  cout << "////////////////" << endl;
  cout << endl;
  }
  else if(option==2){ // LRU
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
