#ifndef UI_H
#define UI_H

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <OGRE/Ogre.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreImGuiOverlay.h>
#include <SDL2/SDL.h>

using namespace Ogre;

void  ui(Ogre::RenderWindow *rw, Ogre::SceneManager *s);

class Ui : public RenderTargetListener {

    // std::unique_ptr<ImGuiInputListener> mImguiListener;
    // InputListenerChain mListenerChain;

    MyGUI::OgrePlatform *plat {nullptr};
    MyGUI::Gui *gui {nullptr};
    Ui();
    public:
        static Ui& getInstance() {
            static Ui u;
            return u;
        }
        virtual ~Ui();

        void callBackExitReal(MyGUI::Widget *w, int x, int y, MyGUI::MouseButton b);
        void callBackExit(MyGUI::Widget *w, int x, int y, MyGUI::MouseButton b);
        void notifyWindowPressed(MyGUI::Widget *_widget);
        void addUiComponents(Ogre::RenderWindow *rw, Ogre::SceneManager *s);
};

#endif


