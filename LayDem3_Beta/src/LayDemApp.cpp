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
bool particleCreationTrigger = true;
float pixelsMove = 10;

class LayDemApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event) override;
	void update() override;
	void draw() override;

    ParticleController mParticleController;
    Particle mParticle2;
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
    ImGui::StyleColorsDark();
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
        //--(p->mLoc.y); // simpler way to move
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
        if (particlesMotionTrigger == true)
        {
            printf("Particles stop! \n");
            particlesMotionTrigger = false;
        }
        else if (particlesMotionTrigger == false)
        {
            printf("Particles go! \n");
            particlesMotionTrigger = true;
        }
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
            printf("Particle edit: OFF! \n");
            particleCreationTrigger = false;
        }
        else if (particleCreationTrigger == false)
        {
            printf("Particle edit: ON! \n");
            particleCreationTrigger = true;
        }
    }
    else if (event.getCode() == KeyEvent::KEY_ESCAPE)
    {
        mParticleController.deselectParticle();
    }
}


void LayDemApp::update()
{
    mParticleController.update();
}


void LayDemApp::draw()
{
    gl::clear( Color( 0.1, 0.1, 0.1 ), true );
    
    mParticleController.draw();
    
    // begin drawing of "List" box
    ImGui::Begin("List");
    ImGui::SetWindowFontScale(2.0);
    ImGui::Text("Objects:");
    ImGui::ListBoxHeader("##listbox",ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()));

    // USEFUL: convert int to const char* for use with imgui lists
//    std::string s = std::to_string(p->mID);
//    const char* pchar = s.c_str();

    mParticleController.selectParticle();

    ImGui::ListBoxFooter();
    ImGui::End();
    // begin drawing of "List" box


    // begin drawing of "Properties" box
    ImGui::Begin("Properties");
    ImGui::SetWindowFontScale(2.0);
    
    mParticleController.printParticleProperties();
    
    ImGui::End();
    // end drawing of "Properties" box

    
}

CINDER_APP( LayDemApp, RendererGl( RendererGl::Options().msaa( 16 ) ), prepareSettings )

