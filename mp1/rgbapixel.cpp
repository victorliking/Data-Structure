#include "rgbapixel.h"
RGBAPixel::RGBAPixel()
{  red=255;
   green=255;
   blue=255;
   alpha=255;
}
RGBAPixel::RGBAPixel(unsigned char red_now,unsigned char green_now,unsigned char blue_now)
{  red=red_now;
   green=green_now;
   blue=blue_now;
   alpha=255;

}
