#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;

extern vec2 mousePos;

ParticleController::ParticleController()
{
}

void ParticleController::update()
{
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p )
    {
        p->update();
    }
}

void ParticleController::draw()
{
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p )
    {
        p->draw();
    }
}

void ParticleController::addParticles( int amt )
{
    //mParticles.push_back( Particle( mousePos ) );
    for( int i=0; i<amt; i++ )
    {
        float x = Rand::randFloat( app::getWindowWidth() );
        float y = Rand::randFloat( app::getWindowHeight() );
        mParticles.push_back( Particle( vec2( x, y ) ) );
    }
}

void ParticleController::removeParticles( int amt )
{
    printf("%lu", mParticles.size());
    if (mParticles.size())
    {
        mParticles.pop_back();
    }
}

void ParticleController::addParticlesXY()
{
    mParticles.push_back( Particle( mousePos ) );
}

void ParticleController::removeParticleCloseToMouse( vec2 mouseCoords )
{
    //check all particles in list for distance and pick nearest
    for (list<Particle>::reverse_iterator p = mParticles.rbegin(); p != mParticles.rend(); ++p)
    {
        float x_mouse = mouseCoords.x;
        float y_mouse = mouseCoords.y;
        float x_particle = p->mLoc_new.x;
        float y_particle = p->mLoc_new.y;
        float mouse_particle_distance = sqrt( pow(x_particle-x_mouse,2) + pow(y_particle-y_mouse,2) );
        
        printf("distance: %f \n", mouse_particle_distance);
        
        if (mouse_particle_distance < p->mRadius)
        {
            printf("inside particle: %d %f %f \n", p->mID, p->mLoc.x,p->mLoc.y);
            
            //method: erase particle by moving it to end of list and then deleting last element
            //mParticles.splice( mParticles.end(), mParticles, p );
            //mParticles.pop_back();

            //method: use implicit function for erase (easier)
            mParticles.erase( --(p.base()) );

            break;
        }
    }
}

