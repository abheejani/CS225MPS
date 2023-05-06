#include <string>
using std::string;
#include <cmath>

#include "Image.h"
#include <algorithm>

Image::Image() : PNG()
{

}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height)
{
    
}

/*
Darken an Image by decreasing the luminance of every pixel by 0.1.

This function ensures that the luminance remains in the range [0, 1].
*/
void Image::darken()
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.l -= .1;
            if(p.l > 1)
            {
                p.l = 1;
            }
            if(p.l < 0)
            {
               p.l = 0;
            }
        }
    }
}

/*
Darkens an Image by decreasing the luminance of every pixel by amount.

This function ensures that the luminance remains in the range [0, 1].
*/
void Image::darken(double myAmount)
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.l -= myAmount;
            if(p.l > 1)
            {
                p.l = 1;
            }
            if(p.l < 0)
            {
               p.l = 0;
            }
        }
    }
}


/*
Desaturates an Image by decreasing the saturation of every pixel by 0.1.

This function ensures that the saturation remains in the range [0, 1].
*/
void Image::desaturate()
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.s -= .1;
            if(p.s > 1)
            {
                p.s = 1;
            }
            if(p.s < 0)
            {
               p.s = 0;
            }
        }
    }
}

/*
Desaturates an Image by decreasing the saturation of every pixel by amount.

This function ensures that the saturation remains in the range [0, 1].
*/
void Image::desaturate(double myAmount)
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.s -= myAmount;
            if(p.s > 1)
            {
                p.s = 1;
            }
            if(p.s < 0)
            {
               p.s = 0;
            }
        }
    }
}

/* Turns the image grayscale. */
void Image::grayscale()
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.s = 0;
        }
    }
}

/* Illinify the image. */
void Image::illinify()
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            if(p.h >= 0 && p.h <= 113.5)
            {
                p.h = 11;
            }
            if(p.h >= 113.5 && p.h <= 293.5)
            {
                p.h = 216;
            }
            if(p.h >= 293.5 && p.h <= 360)
            {
                p.h = 11;
            }
        }
    }
}

/*
Lighten an Image by increasing the luminance of every pixel by 0.1.

This function ensures that the luminance remains in the range [0, 1].
*/
void Image::lighten()
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.l += .1;
            if(p.l > 1)
            {
                p.l = 1;
            }
        }
    }
}
/*
Lighten an Image by increasing the luminance of every pixel by amount.

This function ensures that the luminance remains in the range [0, 1].

Parameters
amount	The desired increase in luminance.
*/
void Image::lighten(double myAmount)
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.l += myAmount;
            if(p.l > 1)
            {
                p.l = 1;
            }
            if(p.l < 0)
            {
               p.l = 0;
            }
        }
    }
}

/*
Rotates the color wheel by degrees.

Rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360].

Parameters
degrees	The desired amount of rotation.
*/
void Image::rotateColor(double myDegrees)
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            myDegrees = fmod(myDegrees, 360);
            p.h = p.h + myDegrees;
            if(p.h < 0)
            {
                p.h += 360;
            }
            if(p.h > 360)
            {
                p.h -= 360;
            }
        }
    }
}

void Image::saturate()
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.s += .1;
            if(p.s > 1)
            {
                p.s = 1;
            }
            if(p.s < 0)
            {
               p.s = 0;
            }
        }
    }
}

void Image::saturate(double myAmount)
{
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            HSLAPixel & p = getPixel(i,j);
            p.s += myAmount;
            if(p.s > 1)
            {
                p.s = 1;
            }
            if(p.s < 0)
            {
               p.s = 0;
            }
        }
    }
}

void Image::scale(double myAmount)
{
    Image originalImage = *this;
    unsigned newWidth = this->width() * myAmount;
    unsigned newHeight = this->height() * myAmount;
    this->resize(newWidth, newHeight);
    for(unsigned int i = 0; i < this->width(); i++)
    {
        for(unsigned int j = 0; j < this->height(); j++)
        {
            this->getPixel(i,j) = originalImage.getPixel(i/myAmount, j/myAmount);
        }
    }
}


void Image::scale(unsigned w, unsigned h)
{
    double widthSample = double(w)/this->width();
    double heightSample = double(h)/this->height();
    this->scale(fmin(widthSample, heightSample));
}