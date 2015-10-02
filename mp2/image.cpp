#include "image.h"


void Image::flipleft()
{   int width = this->width();
    int height = this->height();
    int center=width/2;
    for(int j=0;j<height;j++)
    {  
        for(int i=0;i<center;i++)
        { RGBAPixel temp;
          temp = *(*this)(i,j);
          *(*this)(i,j)=*(*this)(width-i-1,j);
          *(*this)(width-i-1,j)=temp;
        }
       
    }

}


void Image::adjustbrightness(int r, int g, int b)
{  for(int i=0;i<this->height();i++)
     for(int j=0;j<this->width();j++)
     { if((*this)(j,i)->red+r>255)
       { (*this)(j,i)->red=255;
       }
       else if((*this)(j,i)->red+r<0)
       { (*this)(j,i)->red=0;
       }
       else 
       { (*this)(j,i)->red=(*this)(j,i)->red+r;
       }
        if((*this)(j,i)->green+g>255)
       { (*this)(j,i)->green=255;
       }
       else if((*this)(j,i)->green+g<0)
       { (*this)(j,i)->green=0;
       }
       else 
       { (*this)(j,i)->green=(*this)(j,i)->green+g;
       }
        if((*this)(j,i)->blue+b>255)
       { (*this)(j,i)->blue=255;
       }
       else if((*this)(j,i)->blue+b<0)
       { (*this)(j,i)->blue=0;
       }
       else 
       { (*this)(j,i)->blue=(*this)(j,i)->blue+b;
       }
      
     }    
   
}


void Image::invertcolors()
{  for(int i=0;i<this->height();i++)
     for(int j=0;j<this->width();j++)
     {  (*this)(j,i)->red=255- (*this)(j,i)->red;
        (*this)(j,i)->green=255- (*this)(j,i)->green;
        (*this)(j,i)->blue=255- (*this)(j,i)->blue;
     }


}
