
#include "cs225/PNG.h"
#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_ = max;
    picture_ = Image(picture);

    for(unsigned int i = 0; i < max_ ; i++) {
        layerStruct myLayer = {0,0,NULL};
        layers_.push_back(myLayer);
    }
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if(this != &other) {
        layers_.clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max) {
    if(max == 0) {
        layers_.clear();
    }
    if(max >= layers_.size()) {
        max_ = max;
    }
    else {
        layers_.erase(layers_.begin() + max, layers_.end());
    }
}

int StickerSheet::addSticker (Image &sticker, int x, int y) {
    for(unsigned int index = 0; index < layers_.size(); index++) {
        if(layers_.at(index).mySticker == NULL) {
            layers_.at(index).mySticker = (&sticker);
            layers_.at(index).myX = x;
            layers_.at(index).myY = y;
            return index;
        }
    }
    layerStruct myLayer = {x, y, &sticker};
    layers_.push_back(myLayer);
    max_++;
    return max_-1;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y) {
    if(layer >= 0 && layer < max_) {
        layers_.at(layer).mySticker = &sticker;
        layers_.at(layer).myX = x;
        layers_.at(layer).myY = y;
        return layer;
    }
    else {
        return -1;
    }
}

bool StickerSheet::translate (unsigned index, int x, int y) {
    if(index >= 0 && index < layers_.size() && layers_.at(index).mySticker != NULL) {
        layers_.at(index).myX = x;
        layers_.at(index).myY = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker (unsigned index) {
    if(index >= 0 && index < max_) {
        layers_.at(index).mySticker = NULL;
    }
}

Image* StickerSheet::getSticker (unsigned index) const {
    if(index >= 0 && index < layers_.size()) {
        if(layers_.at(index).mySticker != NULL) {
            return layers_.at(index).mySticker;
        }
    }
    return NULL;
}

int StickerSheet::layers () const {
    return max_;
}

Image StickerSheet::render() const
{
    if(layers_.size() == 0) {
        return picture_;
    }

    int minX = 0;
    int minY = 0;
    int maxX = picture_.width();
    int maxY = picture_.height();

    for(unsigned int index = 0; index < layers_.size(); index++) {
        if(layers_.at(index).mySticker != NULL){
            if(layers_.at(index).myX < minX) {
                minX = layers_.at(index).myX;
            }
            if(layers_.at(index).myY < minY) {
                minY = layers_.at(index).myY;
            }
            if( ( (layers_.at(index).myX + (int)layers_.at(index).mySticker->width()) > maxX ) ){
                maxX = layers_.at(index).myX + layers_.at(index).mySticker->width();
            }
            if( ( (layers_.at(index).myY + (int)layers_.at(index).mySticker->height()) > maxY ) ) {
                maxY = (layers_.at(index).myY + layers_.at(index).mySticker->height());
            }
        }
    }

    unsigned newWidth = (unsigned)(maxX - minX);
    unsigned newHeight = (unsigned)(maxY - minY);

    unsigned howMuchWeGoRight = 0 - minX;
    unsigned howMuchWeGoDown = 0 - minY;

    Image newImage(newWidth, newHeight);
  
    for(unsigned i = 0; i < picture_.width(); i++) {
        for(unsigned j = 0; j < picture_.height(); j++) {
            newImage.getPixel(i+howMuchWeGoRight,j+howMuchWeGoDown) = picture_.getPixel(i, j);
        }
    }

    for(unsigned v = 0; v < layers_.size(); v++){
        if(layers_.at(v).mySticker != NULL) {
            for(unsigned int i = 0; i < layers_.at(v).mySticker->width(); i++) {
                for(unsigned int j = 0; j < layers_.at(v).mySticker->height(); j++) {
                    int x = layers_.at(v).myX;
                    int y = layers_.at(v).myY;
                    if(layers_.at(v).mySticker->getPixel(i,j).a!=0) {
                        newImage.getPixel(i + x - minX, j + y - minY) = (layers_.at(v).mySticker)->getPixel(i,j);
                    }
                }
            }
        }
    }
    return newImage;

}

void StickerSheet::copy(const StickerSheet &other) {
    max_ = other.max_;
    picture_ = other.picture_;
    layers_ = other.layers_;
}