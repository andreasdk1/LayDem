//
//  Particle.h
//  LayDem
//
//  Created by Andreas Lay on 13/09/2022.
//

#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"

#include <vector>

class Particle {
 public:
    Particle();
    Particle( ci::vec2 );
    void update();
    void draw();
    void bounce();
    void updateParticleLocations();
    void breathe( ci::vec2 );
    
    ci::vec2    mLoc;
    ci::vec2    mLoc_new;
    ci::vec2    mDir;
    ci::vec3    mColor;

    float   mRadius;
    float   mVel;
    float   mTimeOfBirth;
    int     mID;
    int     mShape;
};

