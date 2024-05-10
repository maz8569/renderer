#include "OrthogonalCamera.h"

Ray OrthogonalCamera::generateRay(float x, float y, unsigned int width, unsigned int height)
{
    
    float pixelWidth = 2.0f / width;
    float pixelheight = 2.0f / height;

    float srX = -1.0f + (x + 0.5f) * pixelWidth;
    float srY = 1.0f - (y + 0.5f) * pixelheight;
    return Ray({ srX + Position().x, srY + Position().y, 0}, _target);

}
