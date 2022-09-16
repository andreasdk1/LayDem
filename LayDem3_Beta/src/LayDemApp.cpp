#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "ParticleController.h"
#include "cinder/CinderImGui.h"
#include <iostream>


using namespace ci;
using namespace ci::app;
using namespace std;

void prepareSettings( App::Settings* settings );


vec2 mousePos;
bool particlesMotionTrigger;
bool particleCreationTrigger;
float pixelsMove = 10;
int properties_of_particle = 0;

class LayDemApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event) override;
	void update() override;
	void draw() override;

    ParticleController mParticleController;
    Particle mParticle2;
    
//private:
//  void updateGui();
};

void prepareSettings( App::Settings* settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setHighDensityDisplayEnabled();
    settings->setMultiTouchEnabled( false );
    settings->disableFrameRate();
}

void LayDemApp::setup()
{
    setWindowSize({ 800,600 });
    setFrameRate(60);
    ImGui::Initialize();
    //gl::enableAlphaBlending();
}

void LayDemApp::mouseDown( MouseEvent event )
{
    printf("x:%d y:%d \n", event.getPos().x, event.getPos().y );
    printf("%d %i \n", event.isLeft(), event.isRight() );
    printf("time:%f \n", getElapsedSeconds() );
    
    mousePos = event.getPos();
        
    if (event.isLeft())
    {
        if (particleCreationTrigger == true)
        {
            mParticleController.addParticlesXY();
        }
    }
    else if (event.isRight())
    {
        if (particleCreationTrigger == true)
        {
            //mParticleController.removeParticles(1);
            mParticleController.removeParticleCloseToMouse(mousePos);
        }
    }
}


void LayDemApp::keyDown(KeyEvent event)
{
    list<Particle>::reverse_iterator p = mParticleController.mParticles.rbegin();

    if (event.getChar() == 'w')
    {
        printf("Move up! \n");
        //--(p->mLoc.y);
        p->mLoc_new.y = p->mLoc_new.y - pixelsMove;
    }
    else if (event.getChar() == 'a')
    {
        printf("Move left! \n");
        p->mLoc_new.x = p->mLoc_new.x - pixelsMove;
    }
    else if (event.getChar() == 's')
    {
        printf("Move down! \n");
        p->mLoc_new.y = p->mLoc_new.y + pixelsMove;
    }
    else if (event.getChar() == 'd')
    {
        printf("Move right! \n");
        p->mLoc_new.x = p->mLoc_new.x + pixelsMove;
    }
    else if (event.getChar() == '1')
    {
        printf("Particles go! \n");
        particlesMotionTrigger = true;
    }
    else if (event.getChar() == '2')
    {
        printf("Particles stopped! \n");
        particlesMotionTrigger = false;
    }
    else if (event.getChar() == '3')
    {
        printf("Create 10 particles! \n");
        mParticleController.addParticles(10);
    }
    else if (event.getChar() == 'p')
    {
        if (particleCreationTrigger == true)
        {
            printf("Particle add: OFF! \n");
            particleCreationTrigger = false;
        }
        else if (particleCreationTrigger == false)
        {
            printf("Particle add: ON! \n");
            particleCreationTrigger = true;
        }
    }
}


void LayDemApp::update()
{
    mParticleController.update();
}


void LayDemApp::draw()
{
	//gl::clear( Color( 0, 0, 0 ) );
    gl::clear( Color( 0.1, 0.1, 0.1 ), true );
    //gl::clear( Color( gray, gray, gray ), true );
    
    mParticleController.draw();
    
    ImGui::Begin("List");
    ImGui::SetWindowFontScale(2.0);
    ImGui::Text("Objects:");

    ImGui::ListBoxHeader("##listbox",ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()));

//    ImGui::Selectable("Selected",true);
//    ImGui::Selectable("Not Selected",false);
//
    //USEFUL: convert int to const char* for use with imgui lists
//    std::string s = std::to_string(p->mID);
//    const char* pchar = s.c_str();

    static int selected = -1;
    //int selected_prev = -1;
    //float focustime = 0;

    for( list<Particle>::iterator p = mParticleController.mParticles.begin(); p != mParticleController.mParticles.end(); ++p )
    {
        char buf[32];
        int n = p->mID;
        
        sprintf(buf, "Object %d", n);
        if (ImGui::Selectable(buf, selected == n))
        {
            selected = n;
            properties_of_particle = selected;
            
            //focustime = getElapsedSeconds();
            //p->mRadius = p->mRadius * 2;
            
        }
    }
    ImGui::ListBoxFooter();
    ImGui::End();
    

    ImGui::Begin("Properties");
    ImGui::SetWindowFontScale(2.0);
    
    if (selected != -1)
    {
        list<Particle>::iterator p = mParticleController.mParticles.begin();
        advance(p, properties_of_particle);

        string s01 = std::to_string(p->mID);
        const char* pchar01 = s01.c_str();
        ImGui::Text("Particle ID: %s", pchar01);
        
        string s10 = std::to_string(p->mShape);
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

        string s09 = std::to_string(p->mRadius);
        const char* pchar09 = s09.c_str();
        ImGui::Text("Radius: %s", pchar09);

        string s02 = std::to_string(p->mLoc.x);
        string s03 = std::to_string(p->mLoc.y);
        const char* pchar02 = s02.c_str();
        const char* pchar03 = s03.c_str();
        ImGui::Text("Origin loc (x,y): %s %s", pchar02,pchar03);

        string s04 = std::to_string(p->mLoc_new.x);
        string s05 = std::to_string(p->mLoc_new.y);
        const char* pchar04 = s04.c_str();
        const char* pchar05 = s05.c_str();
        ImGui::Text("Current loc (x,y): %s %s", pchar04,pchar05);

        string s06 = std::to_string(p->mDir.x);
        string s07 = std::to_string(p->mDir.y);
        const char* pchar06 = s06.c_str();
        const char* pchar07 = s07.c_str();
        ImGui::Text("Direction (x,y): %s %s", pchar06,pchar07);

        string s08 = std::to_string(p->mVel);
        const char* pchar08 = s08.c_str();
        ImGui::Text("Velocity: %s", pchar08);

        string s11 = std::to_string(p->mColor.x);
        string s12 = std::to_string(p->mColor.y);
        string s13 = std::to_string(p->mColor.z);
        const char* pchar11 = s11.c_str();
        const char* pchar12 = s12.c_str();
        const char* pchar13 = s13.c_str();
        ImGui::Text("Color (R,G,B): %s %s %s", pchar11,pchar12,pchar13);
        
        

        
    }
    
    ImGui::End();
    
}



//CINDER_APP( LayDemApp, RendererGl )
CINDER_APP( LayDemApp, RendererGl( RendererGl::Options().msaa( 16 ) ), prepareSettings )

