#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include <OGRE/Ogre.h>
#include "Actor.h"
#include "Event.h"
#include <vector>
#include <SDL2/SDL.h>
#include <Bites/OgreApplicationContext.h>
#include <OgreRTShaderSystem.h>
#include <Bites/OgreImGuiInputListener.h>

class EngineManager : public OgreBites::ApplicationContext, public OgreBites::ImGuiInputListener {

    private:
        void _init(const std::string &pcfg, const std::string &ocfg);
        void _createParticle();
        void _addLights();
        void _initSceneManager();
    public:
        void init(const std::string &pcfg, const std::string &ocfg);
        void setResources();
};

#endif



