#ifndef FRAME_LISTENER_H
#define FRAME_LISTENER_H

#include <OgreOverlayPrerequisites.h>
#include <imgui.h>
#include <OGRE/Ogre.h>

class EngineFrameListener : public Ogre::FrameListener {

    Ogre::SceneNode *_node;
    float step{.1};

    public:
        EngineFrameListener();
        ~EngineFrameListener();
        bool frameStarted(const Ogre::FrameEvent &ev);
};

#endif


