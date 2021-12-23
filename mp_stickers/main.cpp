#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  Image expected;
  expected.readFromFile("tests/expected.png");
  Image img = sheet.render();
  img.writeToFile("img.png");
  //PART 3: create a sticker sheet that contains at least 3 stickers
  //meme 
  Image base;   base.readFromFile("Template.png");
  Image friday; friday.readFromFile("friday.png");
  Image kams;   kams.readFromFile("kams.png");
  Image joes;   joes.readFromFile("joes.png");
  Image lion;   lion.readFromFile("lion.png");
  Image mp;     mp.readFromFile("mp.png");
  Image due;    due.readFromFile("due.png");

  StickerSheet s1(base, 8);
  friday.scale(2.5);
  s1.addSticker(friday,0, 0);
  kams.scale(1.1);
  s1.addSticker(kams,400,0);
  joes.scale(1.3);
  s1.addSticker(joes, 0, 250);
  lion.scale(1.1);
  s1.addSticker(lion,400,250);
  mp.scale(2);
  s1.addSticker(mp,20, 500);
  due.scale(2.5);
  s1.addSticker(due,50,800);

  Image myImage = s1.render();
  myImage.writeToFile("myImage.png");
  return 0;
}
