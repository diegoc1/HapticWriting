//
//  WritingGraphics.h
//  application
//
//  Created by Will Harvey on 5/19/14.
//  Copyright (c) 2014 Force Dimension. All rights reserved.
//

#ifndef __application__WritingGraphics__
#define __application__WritingGraphics__

#include <iostream>
#include "chai3d.h"

using namespace chai3d;
using namespace std;

enum Utensil {pencil, marker, paintbrush};

class WritingGraphics
{
    cMesh* canvas;
    cVector3d lastDrawPoint;
    bool needToSetLastDrawPoint;
    Utensil utensil;
    cColorb paintColor;
    
    vector<cShapeLine *> drawnPencilLines;
    
public:
    WritingGraphics(cMesh *canvas);
    virtual void drawAtPoint(const cVector3d texCoord, double force, double timeInterval);
    
    //Erases previous drawing and sets the new utensil
    virtual void setUtensil(Utensil utensilType);
    virtual Utensil getUtsenil();
};

#endif /* defined(__application__WritingGraphics__) */
