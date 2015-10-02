#include <iostream>
#include <algorithm>
#include "rgbapixel.h"
#include "png.h"

using namespace std;
/**
 this function is using to draw a new picture have the small size with picture we want to rotate
 */
PNG rotate_image(PNG original,int width, int height)
{  unsigned char red[width*height];
   unsigned char green[width*height];
   unsigned char blue[width*height];
   
   int k=0;
   for(int i=0;i<height;i++)
   {	for (int j=0;j<width;j++)
      {  red[k]= original(j,i)->red;
         blue[k]= original(j,i)->blue;
         green[k]= original(j,i)->green;
        
        k++;
        
      }
   }
   
   for(int i= 0;i<height;i++)
   {	for (int j= 0;j<width;j++)
        { k--;
          original(j,i)->red=red[k];
          original(j,i)->green=green[k];
          original(j,i)->blue=blue[k];
          
         
        }  
   }
      
   return original;
} 

/**
 * this main function is using to rotate the picture 180 degree
 */
int main()
{   int width,height;
    PNG image("in.png");
    width = image.width();
    height = image.height();
    image = rotate_image(image,width,height);
    image.writeToFile("out.png");
    return 0;




}
