#ifndef RGEGUI_H
#define RGEGUI_H

#include <OgreImGuiOverlay.h>
#include <OgreOverlayManager.h>
#include <Bites/OgreInput.h>
#include <Bites/OgreImGuiInputListener.h>
#include <OgreRenderTargetListener.h>
#include <SDL2/SDL.h>

class RgeGui : public OgreBites::ImGuiInputListener, public Ogre::RenderTargetListener {

    void listNodes();
    public:
        void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
        bool keyReleased(const OgreBites::KeyboardEvent &ev);
        void setup(void);
};


#endif



