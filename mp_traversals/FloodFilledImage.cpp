#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  base = new PNG(png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  imgT.push_back(&traversal);
  cp.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  animation.addFrame(*base);
  for (int i = 0; i < (int)imgT.size(); i++) {
    int count = 0;
    //now go through the traversal
    for (const Point p : *(imgT[i])) {
      //only add frames when it is a multiple of frameCount

      //chnage the pixel here
      int x = p.x;
      int y = p.y;
      HSLAPixel& current = base -> getPixel(x,y);
      HSLAPixel change = cp[i] -> getColor(x,y);
      //current.h = change.h;
      //current.s = change.s;
      //current.l = change.l;
      //current.a = change.a;
      current = change;
      count++;
      if (count % (int)frameInterval == 0) {
        animation.addFrame(*base);
      }
    }
  }
  //want to add the last frame even if its not a multiple of frameInterval
  animation.addFrame(*base);
  return animation;
}
