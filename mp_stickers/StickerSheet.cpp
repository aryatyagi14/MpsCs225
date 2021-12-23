#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <vector>
using std::string;
using cs225::HSLAPixel;

//constructors
StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    //replaces the base image with picture
    base = new Image(picture);
    //changes max stickers to max
    maxStickers = max;
    
}
StickerSheet::StickerSheet(const StickerSheet& other) {
    //iterate through the other vector and set each pointer of the new one to the corresponding other
    //make deep copy, use new for image = new Image(other.s.at(i))
    _copy(other);
}
StickerSheet::~StickerSheet() {
    //go through vector and delete the pointer to each image?
    //since there is a new in the constructors we neeeeed a delete
    for (unsigned i = 0; i < s.size(); i++) {
        delete s[i];
        s[i] = NULL;
    }
}
const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    //use and make a _copy() function
    if (this != &other ) {
        _copy(other);
    }
    return *this;
}
void StickerSheet::_copy(StickerSheet const & other) {
    //clear self
    delete base;
    for (int i = 0; i < (int) s.size(); i++) {
        delete s[i];
    }
    //copy other to self
    //copy vectors first 
    //make an independent copy of the images from the other image vector s
    for (int i = 0; i < (int)other.s.size(); i++) {
        Image* img = new Image(*other.s[i]);
        s.push_back(img);
        x.push_back(other.x[i]);
        y.push_back(other.y[i]);
    }
    //copy base image
    Image* b = new Image(*other.base);
    base = b;
    //copy maxStickers
    maxStickers = other.maxStickers;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    //size down = delete the ima
    if (max < s.size()) {
        //loop through the index max to the end and delete image pointer
        for (unsigned i = max; i < s.size(); i++) {
            delete s[i];
        }
        //resizes the arrays
        s.resize(max);
        x.resize(max);
        y.resize(max);
    }
    //size up = re size the max, we dont waste space by adding nulls
    maxStickers = max;
}
int StickerSheet::addSticker(Image& sticker, unsigned x_, unsigned y_) {
    //add sticker to end of vectors
    if (s.size() >= maxStickers) {
        return -1;
    }
    Image* img = new Image(sticker);
    s.push_back(img);
    x.push_back(x_);
    y.push_back(y_); 
    //return index of sticker added
    return s.size() -1;
}
bool StickerSheet::translate(unsigned index, unsigned x_, unsigned y_) {
    ///chnages the x/y cords of the image at index
    //invalid if the layer doesnt have a sticker or if its bigger than max
    if (index > maxStickers || index > s.size()) {
        return false;
    }
    x[index] = x_;
    y[index] = y_;
    return true;
}
void StickerSheet::removeSticker(unsigned index){
    //delete heap memory 
    //check index for in bounds
    if (index >= 0 && index < s.size()) {
        s.erase(s.begin()+ index);
        x.erase(x.begin()+ index);
        y.erase(y.begin()+ index);
    }
    
}
Image* StickerSheet::getSticker(unsigned index) {
    //check index
    if (index >= 0 && index < s.size()) {
        return s[index];
    }
    return nullptr;
}
Image StickerSheet::render() const{
    //start the return image with the base image
    Image ret = Image();
    if (base == NULL) {
        return ret;
    }
    ret = *base;
    unsigned baseW = ret.width();
    unsigned baseH = ret.height();
    //loop through the sticker vector 
    for (unsigned i = 0; i < s.size(); i++) {
        //get the first image sticker, xcoord, and y coord
        Image* img = s[i]; //this is the sticker
        unsigned xcoord = x[i];
        unsigned ycoord = y[i];
        //draw image by looping through sticker pixels
        if ( img != nullptr) {
            //loop through sticker pixels
            //if this sticker is outside bounds resize
            if (img -> width() + xcoord > baseW || img -> height() + ycoord > baseH) {
                if (img -> width() + xcoord > baseW) {
                    ret.resize(img -> width() + xcoord, baseH);
                    baseW = img -> width() + xcoord;
                } 
                if (img -> height() + ycoord > baseH) {
                    ret.resize(baseW, img -> height() + ycoord);
                    baseH = img -> height() + ycoord;
                }
            }
            for (unsigned int x = 0; x < img -> width(); x++) {
                for (unsigned int y = 0; y < img -> height(); y++) {
                    //get the pixel in sticker 
                    HSLAPixel& sPixel = img -> getPixel(x,y);
                    if (sPixel.a > 0) {
                        ret.getPixel(x + xcoord, y + ycoord) = sPixel;
                    }
                }
            }
        }
    }
    return ret;
}