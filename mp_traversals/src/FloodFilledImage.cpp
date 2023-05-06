#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png): mypng(png){
  /** @todo [Part 2] */
}
 
/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  // for(auto it = traversal.begin(); it != traversal.end(); ++it){
  //   mypng.getPixel(it.start_.x, it.start_.y) = colorPicker.getColor(it.start_.x, it.start_.y);
  // }
  myTrav.push_back(&traversal);
  myCol.push_back(&colorPicker);
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
 * @param frameInterval how often to save frames of the animation
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */

  PNG pngcopy = mypng;

  animation.addFrame(pngcopy);

  for (unsigned i = 0; i < myTrav.size(); i++) {

    unsigned j = 0;
    for (Traversals::ImageTraversal::Iterator it = myTrav[i]->begin(); it != myTrav[i]->end(); ++it) {
      if (j == frameInterval) {
        animation.addFrame(pngcopy);
        j = 0;
      }
      HSLAPixel& orig = pngcopy.getPixel((*it).x, (*it).y);
      HSLAPixel pix = myCol[i]->getColor((*it).x, (*it).y);

      orig=pix;

      // orig.h = pix.h;
      // orig.s = pix.s;
      // orig.l = pix.l;
      // orig.a = pix.a;
      j++;
    }
    
  }

  animation.addFrame(pngcopy);
  
  return animation;
}