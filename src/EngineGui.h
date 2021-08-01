#ifndef ENGINEGUI_H
#define ENGINEGUI_H

#include "OgreRenderTargetListener.h"
#include "OgreOverlayManager.h"
#include "OgreImGuiOverlay.h"
#include <Bites/OgreImGuiInputListener.h>

using namespace Ogre;
using namespace OgreBites;

class EngineGui : public RenderTargetListener {

    std::unique_ptr<ImGuiInputListener> mImguiListener;
    InputListenerChain mListenerChain;
    void listNodes();

    public:
        // Basic constructor
        EngineGui();
        virtual ~EngineGui();
        void preViewportUpdate(const RenderTargetViewportEvent& evt);
        bool textInput (const TextInputEvent& evt);
        void setupContent(void);
        void cleanupContent();
};


#endif



