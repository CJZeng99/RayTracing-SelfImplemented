#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include "Tokenizer.h"

class Window
{
public:
	// Window Properties
	static int width;
	static int height;
	static int depth;

	// Objects to render
	

	Window(std::string inputFile);
	~Window();

private:
	bool Load(std::string inputFile);
};
#endif
