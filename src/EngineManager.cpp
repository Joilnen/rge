#include <OGRE/Ogre.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include "EngineManager.h"
#include <iostream>
#include <memory>
#include "RgeGui.h"

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
    auto root = getRoot();
    auto scnMgr = root->createSceneManager();
    auto shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    addInputListener(this);

    auto imguiOverlay = OGRE_NEW Ogre::ImGuiOverlay();
    imguiOverlay->setZOrder(300);
    imguiOverlay->show();
    OverlayManager::getSingleton().addOverlay(imguiOverlay); 
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



