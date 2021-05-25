#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <Overlay/OgreImGuiOverlay.h>
#include <Bites/OgreImGuiInputListener.h>
#include <Overlay/OgreOverlaySystem.h>
#include <Bites/OgreTrays.h>
#include <iostream>

using namespace Ogre;

class MyTestApp : 
	public OgreBites::ApplicationContext, 
	public OgreBites::InputListener/* , public OgreBites::TrayListener */ {

    std::unique_ptr<OgreBites::ImGuiInputListener> mImguiListener;
    OgreBites::InputListenerChain mListenerChain;

    public:
        MyTestApp();
        void setup();
        bool keyPressed(const OgreBites::KeyboardEvent& evt); 
        bool keyReleased(const OgreBites::KeyboardEvent& evt) { return mImguiListener->keyReleased(evt); }
        bool mouseMoved(const OgreBites::MouseMotionEvent& evt) { return mImguiListener->mouseMoved(evt); }
        bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) { return mImguiListener->mouseWheelRolled(evt); }
        bool mousePressed(const OgreBites::MouseButtonEvent& evt) { return mImguiListener->mousePressed(evt); }
        bool mouseReleased(const OgreBites::MouseButtonEvent& evt) { return mImguiListener->mouseReleased(evt); }
        bool textInput (const OgreBites::TextInputEvent& evt) { return mImguiListener->textInput (evt); }
        bool frameStarted(const Ogre::FrameEvent& evt);
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    private:
        LogManager *log;
        // OgreBites::TrayManager *mTrayManager;
};

MyTestApp::MyTestApp() : OgreBites::ApplicationContext("MyTestApp")
{
	log = 0;
}

bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (mListenerChain.keyPressed(evt))
		return true;
	//mImguiListener.get()->keyPressed(evt);
	
    LogManager::getSingleton().logMessage("PASSOU DAQUI");
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
		getRoot()->queueEndRendering();

	return OgreBites::InputListener::keyPressed(evt);
}

bool MyTestApp::frameStarted(const Ogre::FrameEvent & evt)
{
    pollEvents();
	ImGuiOverlay::NewFrame(evt);
	ImGui::ShowDemoWindow();
	
	// Pass to superclass
	return OgreBites::ApplicationContext::frameStarted(evt);
}

bool MyTestApp::frameRenderingQueued(const Ogre::FrameEvent & evt)
{
	// mTrayManager->frameRendered(evt);
	return OgreBites::ApplicationContext::frameRenderingQueued(evt);
}

void MyTestApp::setup(void)
{
	OgreBites::ApplicationContext::setup();
	log = LogManager::getSingletonPtr();

	// get a pointer to the already created root
	auto root = getRoot();
	auto scnMgr = root->createSceneManager();

	// register our scene with the RTSS
	auto shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// also need to tell where we are
	auto camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	auto cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(2); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);

	getRenderWindow()->addViewport(cam);

	// register our class for input events
	addInputListener(this);

	// Overlays
	// mTrayManager = new OgreBites::TrayManager("InterfaceName", getRenderWindow(), this);
	scnMgr->addRenderQueueListener(getOverlaySystem()); // Enable drawing of Overlays
	// mTrayManager->showFrameStats(OgreBites::TrayLocation::TL_BOTTOMLEFT);

	//
	// ImGui
	//
	auto imguiOverlay = new ImGuiOverlay;
	imguiOverlay->setZOrder(300);
	imguiOverlay->show();
	Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay); // now owned by overlaymgr

	mImguiListener.reset(new OgreBites::ImGuiInputListener);
    addInputListener(mImguiListener.get());
	// mListenerChain = OgreBites::InputListenerChain({/*mTrayManager,*/ mImguiListener.get()});
}

int main(int argc, char *argv[])
{
    MyTestApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp(); 

    return 0;
}



