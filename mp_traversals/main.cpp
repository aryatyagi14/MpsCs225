
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  //create the png and floodfill
  PNG hippo;
  hippo.readFromFile("hippo.png");
  FloodFilledImage one = FloodFilledImage(hippo);
  //create traversal
  DFS dfs(hippo, Point(0,0), 10.0);
  //create my color picker
  MyColorPicker mine(hippo);
  MyColorPicker sec(hippo);
  one.addFloodFill(dfs, mine);
  one.addFloodFill(dfs, sec);

  Animation animation = one.animate(500);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
