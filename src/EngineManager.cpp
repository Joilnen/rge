#include <OGRE/Ogre.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include <OgreRenderTargetListener.h>
#include "EngineManager.h"
#include <iostream>
#include <memory>
#include "EngineGui.h"
#include "RgeGui.h"

using namespace Ogre;
using namespace std;

EngineManager::EngineManager() : OgreBites::ApplicationContext("Russell") {

}

EngineManager::~EngineManager() {

}

bool EngineManager::frameStarted (const Ogre::FrameEvent &evt) { 
    pollEvents();

    ImGuiOverlay::NewFrame();
    ImGui::ShowDemoWindow();

	return OgreBites::ApplicationContext::frameStarted(evt);
}

#ifndef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
void EngineManager::locateResources() {
    OgreBites::ApplicationContext::locateResources();
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
        "../resources", "FileSystem", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
}
#endif

void EngineManager::setup() {
    OgreBites::ApplicationContext::setup();

    // get a pointer to the already created root
    auto root = getRoot();
    auto scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    auto shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

	scnMgr->addRenderQueueListener(getOverlaySystem()); // Enable drawing of Overlays


    addInputListener(this);


    auto imguiOverlay = new Ogre::ImGuiOverlay;
    imguiOverlay->setZOrder(300);
	imguiOverlay->show();
    Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);


    auto light = scnMgr->createLight("MainLight");
    auto lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    auto cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    getRenderWindow()->addViewport(cam);

	mImguiListener.reset(new OgreBites::ImGuiInputListener);
    addInputListener(mImguiListener.get());

    auto camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    camNode->attachObject(cam);

    auto ent = scnMgr->createEntity("Sinbad.mesh");
    auto node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}

bool EngineManager::keyPressed(const OgreBites::KeyboardEvent& evt) {
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        getRoot()->queueEndRendering();

	return OgreBites::InputListener::keyPressed(evt);
}



