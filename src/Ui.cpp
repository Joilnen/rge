#include "Ui.h"

Ui::Ui() {

}

Ui::~Ui() {

}

void Ui::notifyWindowPressed(MyGUI::Widget *_widget) { 
    std::cout << "OooOOooo\n";
}

void Ui::callBackExitReal(MyGUI::Widget *w, int x, int y, MyGUI::MouseButton b) {
    std::cout << "Clicou exit "<< x << " " << y << "\n";
    SDL_Event e;
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = ::SDLK_ESCAPE;
    SDL_PushEvent(&e);
}

void Ui::callBackExit(MyGUI::Widget *w, int x, int y, MyGUI::MouseButton b) {
    std::cout << "Clicou exit "<< x << " " << y << "\n";
    if(b == MyGUI::MouseButton::Left) {
        MyGUI::LayoutManager::getInstance().loadLayout("Button.layout");
        auto button = gui->findWidget<MyGUI::Button>("MyFirstButton"); 

        button->eventMouseButtonReleased += MyGUI::newDelegate(this, &Ui::callBackExitReal);
    }
}

void Ui::addUiComponents(Ogre::RenderWindow *rw, Ogre::SceneManager *s) {
    plat = new MyGUI::OgrePlatform;
    plat->initialise(rw, s);

    gui = new MyGUI::Gui;
    gui->initialise();

    MyGUI::LayerManager::getInstance().getLayerCount();

    MyGUI::LayoutManager::getInstance().loadLayout("Button.layout");
    auto button = gui->findWidget<MyGUI::Button>("MyFirstButton"); 
    button->eventMouseButtonReleased += MyGUI::newDelegate(this, &Ui::callBackExitReal);
    // button->eventMouseButtonReleased += MyGUI::newDelegate(this, &Ui::callBackExit);
}



