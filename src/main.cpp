#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h"
#include "FreeImage.h"

using namespace std; 

// Main variables in the program.  
#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h" // prototypes for readfile.cpp  

// Reshapes the window
void reshape(int width, int height){
  w = width;
  h = height;

  float aspect = (float) w / (float) h, zNear = 0.1f, zFar = 99.0f;

  projection = Transform::perspective(fovy,aspect,zNear,zFar);
}

void saveScreenshot(string fname) {
  int pix = w * h;
  BYTE *pixels = new BYTE[3*pix];	
  for (int i = 0; i < 3*pix; i++) {
      unsigned char* pixelPtr = pixels + i * sizeof(BYTE);
      if (pixelPtr) *pixelPtr = '\255';
  }

  FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

  std::cout << "Saving screenshot: " << fname << "\n";

  FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
  delete[] pixels;
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
    exit(-1); 
  }

  FreeImage_Initialise();

  readfile(argv[1]); 

  FreeImage_DeInitialise();
  return 0;
}
