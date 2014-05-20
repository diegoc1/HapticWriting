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

WritingGraphics::WritingGraphics(cWorld *newWorld)
{
    world = newWorld;
}

void WritingGraphics::drawAtPoint(const cVector3d position) {    
    if (needToSetLastDrawPoint) {
        lastDrawPoint = position;
        needToSetLastDrawPoint = FALSE;
    }
    
    else {
        cVector3d startPoint = lastDrawPoint;
        cVector3d endPoint = position;
        
        cout << "adding line: " << startPoint << " --> " << endPoint;
        
        cShapeLine *lineToDraw = new cShapeLine(startPoint, endPoint);
        world->addChild(lineToDraw);
        
        lastDrawPoint = endPoint;
    }
}