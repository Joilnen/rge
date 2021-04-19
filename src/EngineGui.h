#ifndef ENGINEGUI_H
#define ENGINEGUI_H

#include "OgreImGuiOverlay.h"
#include <Bites/OgreImGuiInputListener.h>

using namespace Ogre;
using namespace OgreBites;

class EngineGui : public RenderTargetListener {

    std::unique_ptr<ImGuiInputListener> mImguiListener;
    InputListenerChain mListenerChain;

    public:
        // Basic constructor
        EngineGui() {

        }
        virtual ~EngineGui() {

        }

        void preViewportUpdate(const RenderTargetViewportEvent& evt) {
            if(!evt.source->getOverlaysEnabled()) return;
            ImGuiOverlay::NewFrame();
            ImGui::ShowDemoWindow();
        }

        bool textInput (const TextInputEvent& evt) { return mListenerChain.textInput (evt); }

        void setupContent(void) {
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

        void cleanupContent() {
            OverlayManager::getSingleton().destroy("ImGuiOverlay");
            // mWindow->removeListener(this);
        }
};


#endif



