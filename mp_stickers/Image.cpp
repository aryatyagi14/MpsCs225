#include "Image.h"
#include <string>
using std::string;
using cs225::HSLAPixel;
//contructors
Image::Image() {
    PNG();
}
Image::Image(unsigned int w, unsigned int h) {
    PNG(w,h);
}
void Image::lighten() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = pixel.l + .1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = pixel.l + amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}
void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = pixel.l - .1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.l = pixel.l - amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}
void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = pixel.s + .1;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = pixel.s + amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}
void Image::desaturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = pixel.s - .1;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x,y);
            pixel.s = pixel.s - amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.h = pixel.h + degrees;
            if (pixel.h > 360) {
                pixel.h = pixel.h - 360;
            }
            if (pixel.h < 0 ) {
                pixel.h = 360 + pixel.h;
            }
        }
    } 
}
void Image::illinify() {
    for (unsigned int x = 0; x < width(); x++) {
		for (unsigned int y = 0; y < height(); y++) {
			HSLAPixel & pixel = getPixel(x,y);
			if (pixel.h > 293.5 || pixel.h < 113.5) {
				pixel.h = 11.0;
			} else {
				pixel.h = 216.0;
			}
		}
	}
}
void Image::scale(double factor) {
    unsigned int w = (unsigned int)width()*factor;
    unsigned int h = (unsigned int)height()*factor;
    PNG old(*this);
    resize(w,h);
    for (unsigned int x = 0; x < w; x++) {
        for (unsigned int y = 0; y < h; y++) {
            unsigned oldx = (unsigned) ((float) x/factor);
            unsigned oldy = (unsigned) ((float) y/factor);

            HSLAPixel& newp = getPixel(x,y);
            HSLAPixel& oldp = old.getPixel(oldx,oldy);
            newp = oldp;
        }
    }
    
}
void Image::scale(unsigned w, unsigned h) {
    double widthF = w/width();
    double heightF = h/height();
    if (widthF > heightF) {
        scale(widthF);
    } else {
        scale(heightF);
    }
}