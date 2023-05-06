#include "Image.h"
#include "StickerSheet.h"

#include <iostream>
using namespace cs225;
int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.scale(.5);
  std::cout << "The width is: " << alma.width() << " and the height is: " << alma.height() << std::endl;
  alma.writeToFile("scale.png");

  std::cout << "Using Image::Rotate to create `rotate.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.rotateColor(70);
  alma.writeToFile("rotate.png");

  std::cout << "Using Image::Illinify to create `illinify.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.illinify();
  alma.writeToFile("illinify.png");

  StickerSheet sheet = StickerSheet(alma, 5);
  Image i;
  i.readFromFile("../data/i.png");
  sheet.addSticker(i,0,0);
  sheet.render();
  alma.readFromFile("../data/alma.png");
  alma.writeToFile("sticker.png");

  return 0;
}
