#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "FreeImage.h"
#include "Scene.h"

using namespace std; 


int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
		exit(-1); 
	}	

	FreeImage_Initialise();

	Scene scene1(argv[1]);
	scene1.TakeScreenshots();

	FreeImage_DeInitialise();
	return 0;
}
