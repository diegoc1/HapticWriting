//
//  WritingGraphics.cpp
//  application
//
//  Created by Will Harvey on 5/19/14.
//  Copyright (c) 2014 Force Dimension. All rights reserved.
//

#include "WritingGraphics.h"

using namespace chai3d;
using namespace std;


WritingGraphics::WritingGraphics(cMesh *mesh)
{
    canvas = mesh;
    paintColor.setGrayDarkSlate();
}

void WritingGraphics::setUtensil(Utensil utensilType) {
    utensil = utensilType;
}

void WritingGraphics::drawAtPoint(const cVector3d texCoord, double force, double timeInterval) {
    
    // retrieve pixel information
    int px, py;
    canvas->m_texture->m_image->getPixelLocation(texCoord, px, py);
    
    // paint color at tool position
    const double K_INK = 20;
    const double K_SIZE = 10;
    const int BRUSH_SIZE = 25;
    
    double size = cClamp((K_SIZE * force), 0.0, (double)(BRUSH_SIZE));
    for (int x=-BRUSH_SIZE; x<BRUSH_SIZE; x++)
    {
        for (int y=-BRUSH_SIZE; y<BRUSH_SIZE; y++)
        {
            // compute new color percentage
            double distance = sqrt((double)(x*x+y*y));
            if (distance <= size)
            {
                // get color at location
                cColorb color, newColor;
                canvas->m_texture->m_image->getPixelColor(px+x, py+y, color);
                
                // compute color factor based of pixel position and force interaction
                double factor = cClamp(K_INK * timeInterval * cClamp(force, 0.0, 10.0) * cClamp(1 - distance/size, 0.0, 1.0), 0.0, 1.0);
                
                // compute new color
                newColor.setR((1.0 - factor) * color.getR() + factor * paintColor.getR());
                newColor.setG((1.0 - factor) * color.getG() + factor * paintColor.getG());
                newColor.setB((1.0 - factor) * color.getB() + factor * paintColor.getB());
                
                // assign new color to pixel
                canvas->m_texture->m_image->setPixelColor(px+x, py+y, newColor);
            }
        }
    }
    
    // update texture
    canvas->m_texture->markForUpdate();
    
    
}