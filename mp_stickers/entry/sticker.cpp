#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
int main() {
  Image alma;    
  alma.readFromFile("../data/alma.png");
  Image i;       
  i.readFromFile("../data/i.png");
  Image penguin; 
  penguin.readFromFile("../data/penguin.png");
  Image expected; 
  expected.readFromFile("../data/expected-saturate.png");
  StickerSheet sheet(expected, 5);
  alma.scale(2);
  sheet.addSticker(alma, 10, 30);
  sheet.addSticker(i, 20, 0);
  sheet.addSticker(penguin, 1000, -30);
  penguin.scale(40);
  penguin.illinify();
  alma.rotateColor(180);
  //Image cat;
  //cat.readFromFile("../data/cat.png");
  //sheet.addSticker(cat, 100, 100);
  Image render = sheet.render();
  render.writeToFile("myImage.png");
  return 0;
}
