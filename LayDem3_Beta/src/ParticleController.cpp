#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"
#include "cinder/CinderImGui.h"


using namespace ci;
using std::list;

extern vec2 mousePos;
static int selected = -1;
int properties_of_particle = 0;


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

void ParticleController::selectParticle()
{
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p )
    {
        char buf[32];
        int n = p->mID;
        
        sprintf(buf, "Object %d", n);
        if (ImGui::Selectable(buf, selected == n))
        {
            selected = n;
            properties_of_particle = selected;
        }
    }
}

void ParticleController::deselectParticle()
{
    selected = -1;
}

void ParticleController::printParticleProperties()
{
    if (selected != -1)
    {
        list<Particle>::iterator p = mParticles.begin();
        advance(p, properties_of_particle);

        std::string s01 = std::to_string(p->mID);
        const char* pchar01 = s01.c_str();
        ImGui::Text("Particle ID: %s", pchar01);
        
        std::string s10 = std::to_string(p->mShape);
        //const char* pchar10 = s10.c_str();
        if (s10 == "0")
        {
            ImGui::Text("Shape: Circle");
        }
        else if (s10 == "1")
        {
            ImGui::Text("Shape: Square");
        }
        else if (s10 == "2")
        {
            ImGui::Text("Shape: Rectangle");
        }

        std::string s09 = std::to_string(p->mRadius);
        const char* pchar09 = s09.c_str();
        ImGui::Text("Radius: %s", pchar09);

        std::string s02 = std::to_string(p->mLoc.x);
        std::string s03 = std::to_string(p->mLoc.y);
        const char* pchar02 = s02.c_str();
        const char* pchar03 = s03.c_str();
        ImGui::Text("Origin loc (x,y): %s %s", pchar02,pchar03);

        std::string s04 = std::to_string(p->mLoc_new.x);
        std::string s05 = std::to_string(p->mLoc_new.y);
        const char* pchar04 = s04.c_str();
        const char* pchar05 = s05.c_str();
        ImGui::Text("Current loc (x,y): %s %s", pchar04,pchar05);

        std::string s06 = std::to_string(p->mDir.x);
        std::string s07 = std::to_string(p->mDir.y);
        const char* pchar06 = s06.c_str();
        const char* pchar07 = s07.c_str();
        ImGui::Text("Direction (x,y): %s %s", pchar06,pchar07);

        std::string s08 = std::to_string(p->mVel);
        const char* pchar08 = s08.c_str();
        ImGui::Text("Velocity: %s", pchar08);

        std::string s11 = std::to_string(p->mColor.x);
        std::string s12 = std::to_string(p->mColor.y);
        std::string s13 = std::to_string(p->mColor.z);
        const char* pchar11 = s11.c_str();
        const char* pchar12 = s12.c_str();
        const char* pchar13 = s13.c_str();
        ImGui::Text("Color (R,G,B): %s %s %s", pchar11,pchar12,pchar13);
    }
}
