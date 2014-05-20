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

class WritingGraphics
{
    cWorld* world;
    cVector3d lastDrawPoint;
    bool needToSetLastDrawPoint;
    
public:
    WritingGraphics(cWorld *world);
    virtual void drawAtPoint(const cVector3d position);
};

#endif /* defined(__application__WritingGraphics__) */
