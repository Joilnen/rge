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

void EngineManager::_init(const std::string &pcfg, const std::string &ocfg) {
    root = new Root(pcfg.c_str(), ocfg.c_str());

    // Ogre::RenderSystem *rs = root->getRenderSystemByName("OpenGL Rendering Subsystem");
    Ogre::RenderSystem *rs = root->getAvailableRenderers()[0];

    if(!(rs->getName() == "OpenGL Rendering Subsystem")) {
        OGRE_DELETE root;
        exit(-1);
    }

    // Configure our RenderSystem
    root->setRenderSystem(rs);
    renderWindow = root->initialise(false);

    // Use SDL2 to create a window
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);
    SDL_Log("###### Width %ld Height %ld\n", displayMode.w, displayMode.h);

    window = SDL_CreateWindow(
        "StolenDeath", // window title
        0,             // initial x position - of the actual render area, not the border
        0,             // initial y position - of the actual render area, not the border
        displayMode.w, // width, in pixels
        displayMode.h, // height, in pixels
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
 
    // Give the correct window handle to Ogre
    SDL_SysWMinfo wmInfo;
    SDL_GetVersion(&wmInfo.version);

    if(SDL_GetWindowWMInfo(window, &wmInfo) == SDL_FALSE) {

    }

    SDL_ShowCursor(SDL_ENABLE);

    Ogre::String winHandle;
    Ogre::NameValuePairList params;

//    switch (wmInfo.subsystem) {
#ifdef __MINGW32__
//        case SDL_SYSWM_WINDOWS:
            // Windows code
            winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.win.window);
//            break;
#elif __MACOSX__
//        case SDL_SYSWM_COCOA:
            //required to make OGRE play nice with our window
            params.insert(std::make_pair("macAPI", "cocoa"));
            params.insert(std::make_pair("macAPICocoaUseNSView", "true"));
            winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
//            break;
#else
//        case SDL_SYSWM_X11:
            winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.x11.window);
#endif
//    }
 
    params["top"] = "0";
    params["left"] = "0";
    params["externalWindowHandle"] = winHandle;

    renderWindow = root->createRenderWindow("russell", displayMode.w, displayMode.h, false, &params);
}

void EngineManager::init(const std::string &pcfg, const std::string &ocfg) { 
    _init(pcfg, ocfg);
    _initSceneManager();
    sceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
    _addLights();
    _createParticle();
}

void EngineManager::setResources() {

}

void EngineManager::_createParticle() {

    /****        
    Ogre::SceneNode* pNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "Particles_Node" );
    Ogre::ParticleSystem* pParticleSyst = sceneMgr->createParticleSystem( "Particles_PSyst", 50); //50 is the maximum of acceptable number of particles
    pNode->attachObject(pParticleSyst);	//like this all particule can be visible

    //Initialize the material for the diffuseColor management of each particle
    Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("ParticleMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->getTechnique(0)->getPass(0)->createTextureUnitState()->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE);
    mat->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    mat->setReceiveShadows(false);
    mat->setSceneBlending( SBT_TRANSPARENT_ALPHA );
    mat->setDepthBias( 0.1, 0 );
    pParticleSyst->setMaterialName("ParticleMat");
    pParticleSyst->_update(1);
    pParticleSyst->setDefaultDimensions( tailleParticules, tailleParticules ); 
    pParticleSyst->setSpeedFactor(0);
            
    for( int i = 0; i< 500; i++ ) {
        Ogre::Particle* particle = pParticleSyst->createParticle();
        if(particule == NULL)
            std::cout<<" Erreur, vous avez surement depasse le quota de particules pour ce particuleSystem : arret au Point :"<< i << std::endl;
        particle->particleType = Ogre::Particle::ParticleType::Visual;
        particle->position = Ogre::Vector3(cloud[i].x(), cloud[i].y(), cloud[i].z());
        particle->colour = Ogre::ColourValue(color[i][0], color[i][1], color[i][2]);
    }
    ****/
}

void EngineManager::_addLights() {

    auto lightNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    auto light = sceneMgr->createLight();
    light->setType(Light::LT_SPOTLIGHT);
    lightNode->attachObject(light);
    lightNode->translate(-40, 40, 0);
    lightNode->setDirection(Vector3(1, -1, 0));

    auto lightNode1 = sceneMgr->getRootSceneNode()->createChildSceneNode();
    auto light1 = sceneMgr->createLight();
    light1->setType(Light::LT_DIRECTIONAL);
    lightNode1->attachObject(light1);
    lightNode1->translate(20, 40, 0);
    lightNode1->setDirection(Vector3(0, -1, 0));

    auto lightNode2 = sceneMgr->getRootSceneNode()->createChildSceneNode();
    auto light2 = sceneMgr->createLight();
    light2->setType(Light::LT_SPOTLIGHT);
    lightNode2->attachObject(light2);
    lightNode2->translate(0, 5, 20);
    lightNode2->setDirection(Vector3(0, 1, -14));
}

void EngineManager::_initSceneManager() {

    // sceneMgr = root->createSceneManager(ST_GENERIC, String("scene1"));
    sceneMgr = root->createSceneManager();
    camera = sceneMgr->createCamera("MainCam");
    camera->setNearClipDistance(5.0f);
    camera->setFarClipDistance(1000.0f);
    auto cameraNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    cameraNode->attachObject(camera);
    cameraNode->setPosition(Vector3(0, 20, 160));
    cameraNode->lookAt(Vector3(0, 0, -10), Node::TransformSpace::TS_WORLD);

    vpBottom = renderWindow->addViewport(camera);
    // vpTop = renderWindow->addViewport(camera, vpBottom->getZOrder() + 1, 0, 0, 0.25f, 0.25f);
    // vpTop->setBackgroundColour(ColourValue(0, 0, 0.68));
}

void EngineManager::loop() {

}

RenderWindow *EngineManager::getRenderWindow() {
    return renderWindow;
}

SceneManager *EngineManager::getSceneManager() {
    return sceneMgr;
}

void EngineManager::addActor(Actor *a) {
    actorsStack.push_back(a);
}

std::vector<Actor *> &EngineManager::getVectorActor() {
    return actorsStack;
}




