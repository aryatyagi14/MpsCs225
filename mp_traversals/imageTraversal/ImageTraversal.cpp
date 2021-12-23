#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace std;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traverse = NULL;
  png_ = PNG();
  start_ = Point();
  current_ = Point();
  t_ = 0.0;
  visited = vector<bool>(0);

}
ImageTraversal::Iterator::Iterator(PNG p, Point s, double t, ImageTraversal* tra){
  traverse = tra;
  png_ = p;
  start_ = s;
  current_ = start_;
  t_ = t;
  visited = vector<bool>(png_.width()*png_.height(), false);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (traverse == NULL) {
    return *this;
  }
  if (!traverse->empty()) {
    traverse->pop();
  }
  
  visited[current_.x + (current_.y)*png_.width()] = true;
  //returns a reference to a iterator   
  //add in order of right,below,left,above
  Point right = Point(current_.x + 1, current_.y);
  Point below = Point(current_.x , current_.y + 1);
  Point left =  Point(current_.x - 1, current_.y);
  Point above = Point(current_.x , current_.y - 1);
  //check if they are valid positions (dont go off png_ & are allowed(check tolerance))
  //creating helper valid(Point p ) to check those
  //putting all neighbors
  //if the point is already on the list dont add again, mark added ones as visited
  if (valid(right)) {
    traverse -> add(right);
    //visited[right.x + (right.y)*png_.width()] = true;
  }
  if (valid(below)) {
    traverse -> add(below);
    //visited[below.x + (below.y)*png_.width()] = true;
  }
  if (valid(left)) {
    traverse -> add(left);
    //visited[left.x + (left.y)*png_.width()] = true;
  }
  if (valid(above)) {
    traverse -> add(above);
    //visited[above.x + (above.y)*png_.width()] = true;
  }
  //loop till one thing has not been visited and is in tolerance 
  //pop until then.
  while (!traverse -> empty() && !valid(traverse -> peek())) {
    traverse ->pop();
  }
  //if its not empty then set curr to next
  if (!traverse->empty()) {
    current_ = traverse->peek();
  }
  if (traverse -> empty()) {
    traverse = NULL;
  }
  return *this;
}

bool ImageTraversal::Iterator::valid(Point p) {
  //check if it goes out of bounds 
  if (p.x < 0 || p.x >= png_.width()){
    return false;
  }
  if (p.y < 0 || p.y >= png_.height()) {
    return false;
  }
  //check by tolerance if we are suppose to check this point
  //calculateDelta takes 2 HSLAPixels & returns double
  //use getPixel function in PNG class
  double diff = traverse->calculateDelta(png_.getPixel(p.x,p.y),png_.getPixel(start_.x,start_.y));
  if (diff >= t_) {
    return false;
  }
  //check if the point already been visited
  if (visited[p.x + (p.y)*png_.width()]) {
    return false;
  }
  return true;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //we are comparing 2 iterators from ImageTraversal, only used to check against end 
  //if we are at the end and the other is at the end then thy are =
  if (traverse == NULL && other.traverse == NULL) {
    return false;
  }
  //use the == in pointer class
  //if(current_ == (*other)) {
  //  return false;
  //}
  return true;
}

