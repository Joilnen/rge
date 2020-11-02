#include <OgreSceneLoaderManager.h>
#include "ParticleUniverseWrapper.h"
#include <exception>
#include <iostream>

using namespace Ogre;

ParticleUniverseWrapper::ParticleUniverseWrapper() : pManager {ParticleUniverse::ParticleSystemManager::getSingletonPtr()} {

}

ParticleUniverseWrapper::~ParticleUniverseWrapper() {

}

void ParticleUniverseWrapper::initPlugin(Ogre::Root *r, Ogre::SceneNode *sn) {

    /****
    if(r)
        r->installPlugin(new ParticleUniverse::ParticleUniversePlugin);
    else {
        std::cout << "Nao instalou plugin\n";
    }
    ****/
    auto sm = r->getSceneManagers().begin()->second;
    auto pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
    // auto pSys = pManager->createParticleSystem("pSys1", "blackHole", sm);
    // auto pSys = pManager->createParticleSystem("pSys1", "ParticleUniverse/Nucleus", sm);
    auto pSys = pManager->createParticleSystem("pSys1", "mp_torch", sm);
    sn ? sn->attachObject(pSys) : sm->getRootSceneNode()->attachObject(pSys);
    pSys->setScale(Vector3(4, 4, 4));
    pSys->setScaleVelocity(10);
    pSys->start();
}



