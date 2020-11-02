#include "EngineManager.h"
#include "FrameListener.h"
#include <vector>
#include <OGRE/Overlay/OgreOverlay.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreImGuiOverlay.h>

EngineFrameListener::EngineFrameListener() {

}

EngineFrameListener::~EngineFrameListener() {

}

bool EngineFrameListener::frameStarted(const Ogre::FrameEvent &ev) {
    // Ogre::WindowEventUtilities::messagePump();
    EngineManager &gm = EngineManager::getInstance();
    for_each(gm.getVectorActor().begin(), gm.getVectorActor().end(), [&](auto &a) {
        if(a->getAnimState())
            a->getAnimState()->addTime(ev.timeSinceLastFrame);
    });
    return true;
}




