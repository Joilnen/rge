#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include <OGRE/Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <OgreRTShaderSystem.h>
#include "RgeGui.h"

class EngineManager : public OgreBites::ApplicationContext, public OgreBites::InputListener {

    private:
        void _init(const std::string &pcfg, const std::string &ocfg);
        void _createParticle();
        void _addLights();
        void _initSceneManager();
        bool keyPressed(const OgreBites::KeyboardEvent& evt);
        void setup(void);
    public:
        EngineManager();
        virtual ~EngineManager();
        void init(const std::string &pcfg, const std::string &ocfg);
        void setResources();
};

#endif



