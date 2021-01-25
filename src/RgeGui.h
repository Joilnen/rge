#ifndef RGEGUI_H
#define RGEGUI_H

#include <OgreImGuiOverlay.h>
#include <OgreOverlayManager.h>
#include <Bites/OgreInput.h>
#include <Bites/OgreImGuiInputListener.h>
#include <OgreRenderTargetListener.h>
#include <SDL2/SDL.h>

class RgeGui : public OgreBites::ImGuiInputListener, public Ogre::RenderTargetListener {

    public:
        void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) {
            if (!evt.source->getOverlaysEnabled())
                return;

            Ogre::ImGuiOverlay::NewFrame();
            ImGui::ShowDemoWindow();
        }

        bool keyReleased(const OgreBites::KeyboardEvent &ev) {
            SDL_Event e;
            e.type = SDL_KEYDOWN;
            e.key.keysym.sym = ::SDLK_ESCAPE; 
            SDL_PushEvent(&e);

            return true;
        }

        void setup(void) {
            auto imguiOverlay = OGRE_NEW Ogre::ImGuiOverlay();
            imguiOverlay->setZOrder(300);
            imguiOverlay->show();
            Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);
        }
};


#endif



