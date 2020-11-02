#include "Ui.h"

Ui::Ui() {

}

Ui::~Ui() {

}

void Ui::callBackExit(MyGUI::WidgetPtr w, int x, int y, MyGUI::MouseButton b) {
    std::cout << "Clicou exit\n";
    MyGUI::InputManager::getInstance().injectMouseRelease(x, y, b); 	
    SDL_Event e;
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_ESCAPE;
    SDL_PushEvent(&e);
}

void Ui::addUiComponents(Ogre::RenderWindow *rw, Ogre::SceneManager *s) {
    MyGUI::OgrePlatform *plat = new MyGUI::OgrePlatform;
    plat->initialise(rw, s);
    MyGUI::Gui *gui = new MyGUI::Gui;
    gui->initialise();

    MyGUI::LayoutManager::getInstance().loadLayout("Button.layout");
    MyGUI::ButtonPtr button = gui->findWidget<MyGUI::Button>("MyFirstButton");
    button->eventMouseButtonPressed += MyGUI::newDelegate(Ui::callBackExit);
}




