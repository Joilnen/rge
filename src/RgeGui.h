#ifndef RGEGUI_H
#define RGEGUI_H

#include <OgreImGuiOverlay.h>
#include <OgreRenderTargetListener.h>


class RgeGui : public RenderTargetListener {

    void preViewportUpdate(const RenderTargetViewportEvent& evt) {

       if (!evt.source->getOverlaysEnabled()) return;

       ImGuiOverlay::NewFrame();
       ImGui::ShowDemoWindow();
    }

};


#endif
