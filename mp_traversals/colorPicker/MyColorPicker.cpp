#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include "../cs225/PNG.h"

using namespace cs225;

MyColorPicker::MyColorPicker(PNG png) {
  base = new PNG(png);
}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  
  unsigned hue = x + y;
  while(hue >= 360) {
    hue -= 360;
  }
  HSLAPixel& pix = base -> getPixel(x,y);
  pix.h = hue;
  return pix;
  
}
