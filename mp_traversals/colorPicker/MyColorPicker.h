#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 * when it traverses an image how do you want it to choose the color 
 * lets try saturate, make saturation = 1
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(PNG png);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  PNG* base;
};
