#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include <OGRE/Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <Overlay/OgreOverlaySystem.h>
#include <OgreRTShaderSystem.h>
#include "RgeGui.h"

class EngineManager : public OgreBites::ApplicationContext, public Ogre::RenderTargetListener, public OgreBites::InputListener {

    std::unique_ptr<OgreBites::ImGuiInputListener> mImguiListener;
	OgreBites::InputListenerChain mListenerChain;

    public:
        EngineManager();
        virtual ~EngineManager();

        void preViewportUpdate (const Ogre::RenderTargetViewportEvent &evt);

#ifndef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
        void locateResources() {
#endif
        void setup();
        bool keyPressed(const OgreBites::KeyboardEvent& evt);

};

#endif



