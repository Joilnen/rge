#ifndef ENGINE_MANAGER_H
#define ENGINE_MANAGER_H

#include <OGRE/Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <Overlay/OgreOverlaySystem.h>
#include <OgreRTShaderSystem.h>
#include "RgeGui.h"

class EngineManager : public OgreBites::ApplicationContext, OgreBites::InputListener {

    std::unique_ptr<OgreBites::ImGuiInputListener> mImguiListener;
	OgreBites::InputListenerChain mListenerChain;
    void listNodes();
    public:
        EngineManager();
        virtual ~EngineManager();

#ifndef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
        void locateResources() {
#endif
        void setup();
        bool keyPressed(const OgreBites::KeyboardEvent& evt);
        bool keyReleased(const OgreBites::KeyboardEvent& evt) { return mImguiListener->keyReleased(evt); }
        bool mouseMoved(const OgreBites::MouseMotionEvent& evt) { return mImguiListener->mouseMoved(evt); }
        bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) { return mImguiListener->mouseWheelRolled(evt); }
        bool mousePressed(const OgreBites::MouseButtonEvent& evt) { return mImguiListener->mousePressed(evt); }
        bool mouseReleased(const OgreBites::MouseButtonEvent& evt) { return mImguiListener->mouseReleased(evt); }

        bool frameStarted (const Ogre::FrameEvent &evt);
};

#endif



