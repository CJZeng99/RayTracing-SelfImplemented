#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "FreeImage.h"

using namespace std; 


int main(int argc, char* argv[]) {

  if (argc != 2) {
    cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
    exit(-1); 
  }

  FreeImage_Initialise();

  //readfile(argv[1]); 

  FreeImage_DeInitialise();
  return 0;
}
