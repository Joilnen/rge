#ifndef RGEGUI_H
#define RGEGUI_H

#include <OgreImGuiOverlay.h>
#include <Bites/OgreInput.h>
#include <Bites/OgreImGuiInputListener.h>
#include <OgreRenderTargetListener.h>


class RgeGui : public OgreBites::InputListener, public RenderTargetListener {
    OgreBites::InputListenerChain il;

    void preViewportUpdate(const RenderTargetViewportEvent& evt) {

        if (!evt.source->getOverlaysEnabled())
            return;

        ImGuiOverlay::NewFrame();
        ImGui::ShowDemoWindow();
    }

    bool keyReleased(const OgreBites::KeyboardEvent &ev) {

        SDL_Event e;
        e.type = SDL_KEYDOWN;
        e.key.keysym.sym = ::SDLK_ESCAPE; 
        SDL_PushEvent(&e);

        return true;
    }
};


#endif



