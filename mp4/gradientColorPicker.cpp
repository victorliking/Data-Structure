#include <stdlib.h>
#include "gradientColorPicker.h"

/**
 * Constructs a new gradientColorPicker.
 *
 * @param fadeColor1 The first color to start the gradient at.
 * @param fadeColor2 The second color to end the gradient with.
 * @param radius How quickly to transition to fadeColor2.
 * @param centerX X coordinate for the center of the gradient.
 * @param centerY Y coordinate for the center of the gradient.
 */
gradientColorPicker::gradientColorPicker( RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int centerX, int centerY ) {
	/** 
	 * @todo Construct your gradientColorPicker here! You may find it
	 *	helpful to create additional member variables to store things.
	 */
	this->in_fadeColor1= fadeColor1;
	this->in_fadeColor2= fadeColor2;
	r = radius;
	this->center_x = centerX;
	this->center_y = centerY;
}

/**
 * Picks the color for pixel (x, y).
 *
 * The first color fades into the second color as you move from the initial
 * fill point, the center, to the radius. Beyond the radius, all pixels
 * should be just color2. 
 *
 * You should calculate the distance between two points using the standard
 * Manhattan distance formula, 
 * 
 * \f$d = |center\_x - given\_x| + |center\_y - given\_y|\f$
 *
 * Then, scale each of the three channels (R, G, and B) from fadeColor1 to
 * fadeColor2 linearly from d = 0 to d = radius. 
 *
 * For example, the red color at distance d where d is less than the radius
 * must be
 *
 * \f$ redFill = fadeColor.red - \left\lfloor
   \frac{d*fadeColor1.red}{radius}\right\rfloor +
   \left\lfloor\frac{d*fadeColor2.red}{radius}\right\rfloor\f$
 *
 * Note that all values are integers. If you do not follow this formula,
 * your colors may be very close but round differently than ours.
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
RGBAPixel gradientColorPicker::operator()(int x, int y)
{
	RGBAPixel color;
	/**
	 * @todo Return the correct color here!
	 */
	int d1,d2,d;
	if(x<center_x)
	d1 = center_x - x;
	else  
   	d1 = x - center_x;
	if(y<center_y)
	d2 = center_y - y;
	else 
	d2 = y -center_y;
	d = d1 + d2;
 	if(d > r)
	return in_fadeColor2;
	color.red = in_fadeColor1.red - ((int)(d*in_fadeColor1.red/r))+ ((int)(d*in_fadeColor2.red/r));
    	color.green = in_fadeColor1.green - ((int)(d*in_fadeColor1.green/r))+ ((int)(d*in_fadeColor2.green/r));
    	color.blue = in_fadeColor1.blue - ((int)(d*in_fadeColor1.blue/r))+ ((int)(d*in_fadeColor2.blue/r));
	return color;
}
