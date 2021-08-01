#include "RgeGui.h"

void RgeGui::preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt) {
    if (!evt.source->getOverlaysEnabled())
        return;

    Ogre::ImGuiOverlay::NewFrame();
    // ImGui::ShowDemoWindow();
    listNodes();
}

bool RgeGui::keyReleased(const OgreBites::KeyboardEvent &ev) {
    SDL_Event e;
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = ::SDLK_ESCAPE; 
    SDL_PushEvent(&e);

    return true;
}

void RgeGui::setup(void) {
    auto imguiOverlay = OGRE_NEW Ogre::ImGuiOverlay();
    imguiOverlay->setZOrder(300);
    imguiOverlay->show();
    Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);
}

void RgeGui::listNodes() {
    ImGui::Begin("List Nodes");
    ImGui::Text("Test windows");
    if (ImGui::Button("Button"));
    ImGui::End();
}
