#include "Ui.h"

Ui::Ui() {

}

Ui::~Ui() {

}

void Ui::notifyWindowPressed(MyGUI::Window* _widget, const std::string& _name) { 
    MyGUI::WindowPtr window = _widget->castType<MyGUI::Window>(); 
    if(_name == "close")
        window->destroySmooth(); 
    else if (_name == "minimized") { 
        // hide window and show button in your taskbar 
    } 
    else if (_name == "maximized") { 
        // maximized window 
    } 
}

void Ui::callBackExit(MyGUI::WidgetPtr w, int x, int y, MyGUI::MouseButton b) {
    std::cout << "Clicou exit\n";
    MyGUI::InputManager::getInstance().injectMouseRelease(x, y, b); 	
    SDL_Event e;
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = ::SDLK_ESCAPE;
    SDL_PushEvent(&e);
}

void Ui::addUiComponents(Ogre::RenderWindow *rw, Ogre::SceneManager *s) {

    auto plat = new MyGUI::OgrePlatform;
    plat->initialise(rw, s);

    auto gui = new MyGUI::Gui;
    gui->initialise();

    MyGUI::LayoutManager::getInstance().loadLayout("Button.layout");
    auto button = gui->findWidget<MyGUI::Button>("MyFirstButton"); 
    button->eventMouseButtonPressed += MyGUI::newDelegate(Ui::callBackExit);

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



