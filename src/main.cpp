#include "main.h"


static void CreateImage(unsigned char* pixels, std::string fname)
{
	FreeImage_Initialise();


	FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, 100, 100, 100 * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	FreeImage_DeInitialise();

}

void main(int argc, char** argv)
{
	// TODO: command line parsing
	// TODO: input file parsing
	// TODO: camera setup
	// TODO: object setup
	// TODO: acceleration implementation
	// TODO: raytracing

	// create pixel bitmap (test only)
	unsigned char* pixels = (unsigned char*)malloc((3 * 100 * 100) * sizeof(char));;
	for (int i = 0; i < 30000; i++)
	{
		*(pixels + i * sizeof(char)) = 255;
	}

	// create image
	std::string fname = "output/IllSendYouToJesus.png";
	CreateImage(pixels, fname);

	// clean memory
	free(pixels);
}