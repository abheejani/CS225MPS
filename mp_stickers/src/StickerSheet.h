#pragma once
#include "Image.h"
#include <vector>
using namespace std;

struct layerStruct{
    int myX;
    int myY;
    Image* mySticker;
};

class StickerSheet
{
    public:
        StickerSheet (const StickerSheet &other);
        StickerSheet(const Image &picture, unsigned max);
        const StickerSheet& operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index) const;
        int layers () const;
        Image render () const;
        void copy(const StickerSheet &other);
    private:
         unsigned max_;
         Image picture_;
         vector<layerStruct> layers_;
};
