#include "Ui.h"

Ui::Ui() {

}

Ui::~Ui() {

}

void Ui::notifyWindowPressed(MyGUI::Widget *_widget) { 
    std::cout << "OooOOooo\n";
}

void Ui::callBackExit(MyGUI::Widget *w, int x, int y, MyGUI::MouseButton b) {
    std::cout << "Clicou exit "<< x << " " << y << "\n";
    if(b == MyGUI::MouseButton::Left) {
        SDL_Event e;
        e.type = SDL_KEYDOWN;
        e.key.keysym.sym = ::SDLK_ESCAPE;
        SDL_PushEvent(&e);
    }
}

void Ui::addUiComponents(Ogre::RenderWindow *rw, Ogre::SceneManager *s) {
    auto plat = new MyGUI::OgrePlatform;
    plat->initialise(rw, s);

    auto gui = new MyGUI::Gui;
    gui->initialise();

    MyGUI::LayoutManager::getInstance().loadLayout("Button.layout");
    auto button = gui->findWidget<MyGUI::Button>("MyFirstButton"); 
    button->eventMouseButtonReleased += MyGUI::newDelegate(Ui::callBackExit);
    // button->eventMouseButtonClick = MyGUI::newDelegate(Ui::callBackExit);

    /****
    MyGUI::WindowPtr window = _widget->castType<MyGUI::Window>(); 
    if(_name == "close")
        window->destroySmooth(); 
    else if(_name == "minimized") { 
        // hide window and show button in your taskbar 
    } 
    else if(_name == "maximized") { 
        // maximized window 
    }
    ****/
}



