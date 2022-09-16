#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace ci::app;
using namespace ci;


int mID_old = 0;
extern bool particlesMotionTrigger;

Particle::Particle()
{
}

Particle::Particle( vec2 loc )
{
    mLoc = loc;
    mLoc_new = mLoc;
    mDir = Rand::randVec2();
    mVel = Rand::randFloat(6.0f); //random velocity
    mRadius = Rand::randFloat(10.0f,40.0f); //random radius
    mColor = Rand::randVec3(); //random color
    mTimeOfBirth = getElapsedSeconds();
    mID = mID_old;
    mID_old = mID+1;
    mShape = Rand::randInt(0,3); //include all 3 shapes
}

void Particle::update()
{
}


void Particle::draw()
{
    //update particle locations before drawing
    if (particlesMotionTrigger)
    {
        updateParticleLocations();
    }
    
    //set particle color
    gl::color(Color(mColor.x,mColor.y,mColor.z));
    
    if (mShape == 0)
    {
        gl::drawSolidCircle( vec2(mLoc_new.x,mLoc_new.y), mRadius );
    }
    else if (mShape == 1)
    {
        Rectf rect( mLoc_new.x-mRadius, mLoc_new.y-mRadius,mLoc_new.x+mRadius, mLoc_new.y+mRadius );
        gl::drawSolidRect(rect);
    }
    else if (mShape == 2)
    {
        Rectf rect( mLoc_new.x-mRadius, mLoc_new.y-mRadius/2,mLoc_new.x+mRadius, mLoc_new.y+mRadius/2 );
        gl::drawSolidRect(rect);
    }

}

void Particle::updateParticleLocations()
{
    float x =  mDir.x * mVel;// * (getElapsedSeconds()-mTimeOfBirth); //t=square of time=acceleration
    float y =  mDir.y * mVel;// * (getElapsedSeconds()-mTimeOfBirth);
    mLoc_new.x = mLoc_new.x + x;
    mLoc_new.y = mLoc_new.y + y;
    Particle::bounce(); //Bounce if the particle goes off the screen
}

void Particle::bounce()
{
    
    if (mShape == 0 || mShape == 1)
    {
        if ( mLoc_new.y - mRadius < 0 )
        {
            mDir.y = -mDir.y;
        }
        else if ( mLoc_new.x - mRadius < 0 )
        {
            mDir.x = -mDir.x;
        }
        else if ( mLoc_new.y + mRadius > (float)getWindowHeight() )
        {
            mDir.y = -mDir.y;
        }
        else if ( mLoc_new.x + mRadius > (float)getWindowWidth() )
        {
            mDir.x = -mDir.x;
        }
    }
    else if (mShape == 2)
    {
        if ( mLoc_new.y - mRadius/2 < 0 )
        {
            mDir.y = -mDir.y;
        }
        else if ( mLoc_new.x - mRadius < 0 )
        {
            mDir.x = -mDir.x;
        }
        else if ( mLoc_new.y + mRadius/2 > (float)getWindowHeight() )
        {
            mDir.y = -mDir.y;
        }
        else if ( mLoc_new.x + mRadius > (float)getWindowWidth() )
        {
            mDir.x = -mDir.x;
        }
    }

}

void Particle::breathe( vec2 loc )
{
    float add_radius = 1;
    printf("breathe!");
    mRadius = mRadius + add_radius;
}
