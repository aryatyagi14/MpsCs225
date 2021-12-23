#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <math.h>
using cs225::HSLAPixel;
using cs225::PNG;
void rotate(std::string inputFile, std::string outputFile) {
//create an empty PNG
	PNG image;
	image.readFromFile(inputFile);
//create a new PNG where we can copy the pixels over to w/o overriding the old file
	PNG newImage(image.width(), image.height());
//create variables that hold the max index of row and col
	int maxRow = image.height() - 1;
	int maxCol = image.width() - 1;
//loop through every pixel in the first image 
	for (unsigned int x = 0; x < image.width(); x++) {
		for (unsigned int y = 0; y < image.height(); y++) {
//get the pixel at this x,y that we need to place else where
			HSLAPixel & move = image.getPixel(x,y);
//get pixel from new image (rotated)
			HSLAPixel & place = newImage.getPixel(maxCol - x, maxRow - y);
//set this pixel in the rotated positon
			place = move;
		}
	}
//write the rotated image 
	newImage.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);

	for (int i = 0; i < 100; i ++) {
		unsigned int randX = rand() % 800 + 1;
		unsigned int randY = rand() % 800 + 1;
		int hue = rand() % 360 + 1;

		int eyeY = randY - 25;
		int eyeXL = randX - 35;
		int eyeXR = randX + 35;
		for (unsigned int x = 0; x < png.width(); x++) {
			for (unsigned int y = 0; y < png.height(); y++) {
				//makes the actual circle and black border
				double dist = sqrt((randX-x)*(randX-x) + (randY-y)*(randY-y));
				if (dist <= 100) {
					HSLAPixel & pixel = png.getPixel(x,y);
					pixel.h = hue;
					pixel.s = 100;
					pixel.l = 50;
					pixel.a = 1;
					if (dist >= 95) {
						pixel.s = 0;
						pixel.l = 0;
					}
					if (dist > 45 && dist <= 50 && y > randY+20) {
						pixel.s = 0;
						pixel.l = 0;
					}
				} 
				//makes the two eyes
				double distL = sqrt((eyeXL-x)*(eyeXL-x) + (eyeY-y)*(eyeY-y));
				double distR = sqrt((eyeXR-x)*(eyeXR-x) + (eyeY-y)*(eyeY-y));
				if (distL <= 8) {
					HSLAPixel & pixel = png.getPixel(x,y);
					pixel.s = 0;
					pixel.l = 0;
				}
				else if (distR <= 8) {
					HSLAPixel & pixel = png.getPixel(x,y);
					pixel.s = 0;
					pixel.l = 0;
				}  
			}
		}
		
	}

  return png;
}
