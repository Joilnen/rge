#include <OGRE/Ogre.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <cstdlib>
#include "EngineManager.h"
#include "Actor.h"
#include <iostream>
#include <memory>
#include "RgeGui.h"
#include <OgreOverlaySystem.h>

using namespace Ogre;
using namespace std;

EngineManager::EngineManager() : OgreBites::ApplicationContext("Russell") {


}

EngineManager::~EngineManager() {

}

bool EngineManager::keyPressed(const OgreBites::KeyboardEvent& evt) {
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        getRoot()->queueEndRendering();
    return true;
}

void EngineManager::setup(void) {
    OgreBites::ApplicationContext::setup();
    auto imguiOverlay = new Ogre::ImGuiOverlay();
    imguiOverlay->setZOrder(300);
    imguiOverlay->show();
    // OverlayManager::getSingleton().addOverlay(imguiOverlay); // now owned by overlaymgr

    addInputListener(this);
}

void EngineManager::_init(const std::string &pcfg, const std::string &ocfg) {

}

void EngineManager::init(const std::string &pcfg, const std::string &ocfg) { 
}

void EngineManager::setResources() {

}

void EngineManager::_createParticle() {

}

void EngineManager::_addLights() {

}

void EngineManager::_initSceneManager() {

}



