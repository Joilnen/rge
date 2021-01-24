#ifndef RGEGUI_H
#define RGEGUI_H

#include <OgreImGuiOverlay.h>
#include <Bites/OgreInput.h>
#include <Bites/OgreImGuiInputListener.h>
#include <OgreRenderTargetListener.h>


class RgeGui : public OgreBites::InputListener, public RenderTargetListener {

    OgreBites::InputListenerChain mListenerChain;
    unique_ptr<OgreBites::ImGuiInputListener> mImguiListener;

    public:
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

        void setUp(void) {
            mImguiListener.reset(new OgreBites::ImGuiInputListener());
            mListenerChain = OgreBites::InputListenerChain({mImguiListener.get()});
        }

        bool keyPressed(const OgreBites::KeyboardEvent& evt) { return mListenerChain.keyReleased(evt); }
        bool mouseMoved(const OgreBites::MouseMotionEvent& evt) { return mListenerChain.mouseMoved(evt); }
        bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) { return mListenerChain.mouseWheelRolled(evt); }
        bool mousePressed(const OgreBites::MouseButtonEvent& evt) { return mListenerChain.mousePressed(evt); }
        bool mouseReleased(const OgreBites::MouseButtonEvent& evt) { return mListenerChain.mouseReleased(evt); }
        bool textInput (const OgreBites::TextInputEvent& evt) { return mListenerChain.textInput(evt); }
};


#endif



