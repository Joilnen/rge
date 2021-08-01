#include "EngineGui.h"

EngineGui::EngineGui() {

}

EngineGui::~EngineGui() {

}

void EngineGui::preViewportUpdate(const RenderTargetViewportEvent& evt) {
    if(!evt.source->getOverlaysEnabled()) return;
    ImGuiOverlay::NewFrame();
    // ImGui::ShowDemoWindow();
    listNodes();
}

bool EngineGui::textInput (const TextInputEvent& evt) { return mListenerChain.textInput (evt); }

void EngineGui::setupContent(void) {
    auto imguiOverlay = new ImGuiOverlay();
    imguiOverlay->setZOrder(300);
    imguiOverlay->show();
    OverlayManager::getSingleton().addOverlay(imguiOverlay); // now owned by overlaymgr

    /*
        NOTE:
        Custom apps will ASSERT on ImGuiOverlay::NewFrame() and not display any UI if they
        have not registered the overlay system by calling mSceneMgr->addRenderQueueListener(mOverlaySystem).
        OgreBites::SampleBrowser does this on behalf of the ImGuiDemo but custom applications will need to
        call this themselves.  See ApplicationContextBase::createDummyScene().
    */
    // mWindow->addListener(this);

    mImguiListener.reset(new ImGuiInputListener());
    // mListenerChain = OgreBites::InputListenerChain({mTrayMgr.get(), mImguiListener.get(), mCameraMan.get()});

    // mTrayMgr->showCursor();
}

void EngineGui::cleanupContent() {
    OverlayManager::getSingleton().destroy("ImGuiOverlay");
    // mWindow->removeListener(this);
}

void EngineGui::listNodes() {
    {
        ImGui::Begin("List Nodes");
        ImGui::Text("Test windows");
        if (ImGui::Button("Button"));
        ImGui::End();
    }
}
