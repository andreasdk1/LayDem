//
//  ParticleController.h
//  LayDem
//
//  Created by Andreas Lay on 13/09/2022.
//

#pragma once
#include "Particle.h"
#include <list>

class ParticleController
{
public:
    ParticleController();
    void update();
    void draw();
    void addParticles( int amt );
    void addParticlesXY();
    void removeParticles( int amt );
    void removeParticleCloseToMouse ( cinder::vec2 mouseCoords);
    void selectParticle();
    void deselectParticle();
    void printParticleProperties();
    std::list<Particle> mParticles;
};
