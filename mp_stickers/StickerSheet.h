/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <vector>
using std::string;

class StickerSheet {
    public:
        StickerSheet(const Image& picture, unsigned max);
        StickerSheet(const StickerSheet& other);
        ~StickerSheet();
        const StickerSheet& operator=(const StickerSheet& other); 
        void _copy(StickerSheet const & other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image& sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const; //include stickers that go out of bounds?
    private:
        std::vector<Image*> s;
        std::vector<int> x;
        std::vector<int> y;
        unsigned maxStickers; //max 
        Image* base;
        
        
};
 
