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
    paintColor.setBlueLightSky();
    utensil = pencil;
}

void WritingGraphics::setUtensil(Utensil utensilType) {
    utensil = utensilType;
}

Utensil WritingGraphics::getUtsenil() {
    return utensil;
}


void WritingGraphics::drawAtPoint(const cVector3d texCoord, double force, double timeInterval) {
    
    // retrieve pixel information
    int px, py;
    canvas->m_texture->m_image->getPixelLocation(texCoord, px, py);
    
    // paint color at tool position
    if (utensil == pencil) {
        
        cColorb pencilColor;
        pencilColor.setGrayLightSlate();

        const double K_INK = 10;
        const double K_SIZE = 10;
        const int BRUSH_SIZE = 4;
        double size = cClamp((K_SIZE * force), 0.0, (double)(BRUSH_SIZE));

        for (int x=-BRUSH_SIZE; x<BRUSH_SIZE; x++)
        {
            for (int y=-BRUSH_SIZE; y<BRUSH_SIZE; y++)
            {
                double distance = sqrt((double)(x*x+y*y));
                if (distance <= size)
                {
                    double factor = cClamp(K_INK * timeInterval * cClamp(force, 0.0, 10.0) * cClamp(1 - distance/size, 0.0, 1.0), 0.0, 1.0);
                    
                    cColorb color;
                    canvas->m_texture->m_image->getPixelColor(px+x, py+y, color);
                    cColorb newColor;
                    newColor.setR((1.0 - factor) * color.getR() + factor * pencilColor.getR());
                    newColor.setG((1.0 - factor) * color.getG() + factor * pencilColor.getG());
                    newColor.setB((1.0 - factor) * color.getB() + factor * pencilColor.getB());
                    
                    canvas->m_texture->m_image->setPixelColor(px+x, py+y, newColor);
                }
            }
        }
    }
    
    
    //if (utensil == paintbrush) {
    else {
        const double K_INK = 10;
        const double K_SIZE = 10;
        const int BRUSH_SIZE = 32;
        double size = cClamp((K_SIZE * force), 0.0, (double)(BRUSH_SIZE));

        
        //Set the new pixels
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
        
        int height = canvas->m_texture->m_image->getHeight();
        int width = canvas->m_texture->m_image->getWidth();
        
        //Apply a blur
        int startX = max(2, px - BRUSH_SIZE);
        int endX = min(width - 3, px + BRUSH_SIZE);
        
        int startY = max(2, py - BRUSH_SIZE);
        int endY = min(height - 3, py + BRUSH_SIZE);
        
        for (int x=startX; x < endX; x++) {

            for (int y=startY; y < endY; y++) {
                
                cColorb oldColor;
                canvas->m_texture->m_image->getPixelColor(x, y, oldColor);
                
                double averageR = 0.0;
                double averageG = 0.0;
                double averageB = 0.0;
                
                //Apply kernel at pixel
                for (int i = -2; i < 3; i++) {
                    for (int j = -2; j < 3; j++) {
                        cColorb color;
                        canvas->m_texture->m_image->getPixelColor(x+i, y+j, color);
                        
                        float factor = 4;
                        if ((i == -2 && j == -2) || (i == -2 && j == 2) || (i == 2 && j == -2) || (i == 2 && j == 2)) {
                            factor = 1;
                        }
                        
                        else if ((i == -1 && j == -1) || (i == -1 && j == 1) || (i == 1 && j == -1) || (i == 1 && j == 1)) {
                            factor = 17;
                        }
                        
                        else if ((i == -2 && j == 0) || (i == 0 && j == -2) || (i == 2 && j == 0) || (i == 0 && j == 2)) {
                            factor = 7;
                        }
                        
                        else if ((i == -1 && j == 0) || (i == 0 && j == -1) || (i == 1 && j == 0) || (i == 0 && j == 1)) {
                            factor = 26;
                        }
                        
                        else if (i == 0 && j == 0) factor = 41;
                        
                        
                        averageR = averageR + factor * color.getR();
                        averageG = averageG + factor * color.getG();
                        averageB = averageB + factor * color.getB();
                        
                    }
                }
                
                cColorb newColor;
                // compute new color
                newColor.setR((3*oldColor.getR() + averageR/273)/4);
                newColor.setG((3*oldColor.getG() + averageG/273)/4);
                newColor.setB((3*oldColor.getB() + averageB/273)/4);
                
                // assign new color to pixel
                canvas->m_texture->m_image->setPixelColor(x, y, newColor);
            }
        }
    }

    // update texture
    canvas->m_texture->markForUpdate();
    
    
}