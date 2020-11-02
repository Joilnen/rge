#include <vector>
#include <string>
#include <iostream>
#include <functional>

#include "OGRE/Ogre.h"
#include "OGRE/OgreFrameListener.h"
#include "OGRE/Compositor/OgreCompositorManager2.h"
#include "OGRE/RTShaderSystem/OgreRTShaderSystem.h"

using std::vector;
using std::string;
using std::function;

class Listener : public Ogre::FrameListener, public Ogre::WindowEventListener
{
	bool running;
	function<void(const Ogre::FrameEvent&)> frameHandler;
public:

	Listener(Ogre::RenderWindow* pWindow)
	{
		Ogre::WindowEventUtilities::addWindowEventListener(pWindow, this);
		Ogre::Root::getSingleton().addFrameListener(this);
	}

	void doEachFrame(function<void(const Ogre::FrameEvent&)> handler)
	{
		frameHandler = handler;
	}

private:
	bool frameStarted(const Ogre::FrameEvent& evt) override
	{
		frameHandler(evt);
		return running;
	}

	bool windowClosing(Ogre::RenderWindow*)
	{
		running = false;
		return false;
	}
};

// Lifted from SampleBrowser.h
class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
{
public:

	ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
	{
		mShaderGenerator = pShaderGenerator;
	}

	/** This is the hook point where shader based technique will be created.
	It will be called whenever the material manager won't find appropriate technique
	that satisfy the target scheme name. If the scheme name is out target RT Shader System
	scheme name we will try to create shader generated technique for it.
	*/
	virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
		const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex,
		const Ogre::Renderable* rend)
	{
		Ogre::Technique* generatedTech = NULL;

		// Case this is the default shader generator scheme.
		if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
		{
			bool techniqueCreated;

			// Create shader generated technique for this material.
			techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
				originalMaterial->getName(),
				Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
				schemeName);

			// Case technique registration succeeded.
			if (techniqueCreated)
			{
				// Force creating the shaders for the generated technique.
				mShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());

				// Grab the generated technique.
				Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

				while (itTech.hasMoreElements())
				{
					Ogre::Technique* curTech = itTech.getNext();

					if (curTech->getSchemeName() == schemeName)
					{
						generatedTech = curTech;
						break;
					}
				}
			}
		}

		return generatedTech;
	}

protected:
	Ogre::RTShader::ShaderGenerator*        mShaderGenerator;                       // The shader generator instance.
};

string rootFolder()
{
	static string ogreRoot(getenv("OGRE_HOME"));
	return ogreRoot;
}

void loadPlugins(vector<string> plugins)
{
	// Load listed plugins
	for (string name : plugins)
	{
#ifdef _DEBUG
		Ogre::Root::getSingleton().loadPlugin(rootFolder() + R"(\bin\debug\)" + name + "_d");
#else
		Ogre::Root::getSingleton().loadPlugin(rootFolder() + R"(\bin\release\)" + name);
#endif
	}
}

void loadResources(string name, vector<string> paths)
{
	for (string path : paths)
	{
		string type;
		if (path.substr(path.length() - 4, 4) == ".zip")
		{
			type = "Zip";
		}
		else
		{
			type = "FileSystem";
		}
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rootFolder() + "\\" + path, type, name);
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(name);
}

int main()
{
	// Start up ogre
	Ogre::Root root("", "", "OgreLog.txt");

	loadPlugins({
		"RenderSystem_Direct3D11",
		"Plugin_ParticleFX",
		"Plugin_CgProgramManager"
	});

	// Use the first available renderer
	Ogre::RenderSystem* renderSys = root.getAvailableRenderers()[0];
	root.setRenderSystem(renderSys);

	// Set video mode
	renderSys->setConfigOption("Full Screen", "No");
	renderSys->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

	// Make the window
	Ogre::RenderWindow* pRenderWin = root.initialise(true);

	// Start compositor
	root.initialiseCompositor();

	// Resources necessary for the real-time shader.
	loadResources("Essential", {
		R"(media\RTShaderLib)",
		R"(media\RTShaderLib\materials)",
		R"(media\RTShaderLib\hlsl)",
		R"(media\RTShaderLib\cg)"
	});

	bool ok = Ogre::RTShader::ShaderGenerator::initialize();
	auto &shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingleton();

	// Necessary for D3D11. It has no fixed function pipeline.
	ShaderGeneratorTechniqueResolverListener sgtrl(&shaderGenerator);
	Ogre::MaterialManager::getSingleton().addListener(&sgtrl);

	// Set up scene manager and one camera
	Ogre::SceneManager* pSceneMgr = root.createSceneManager(
		Ogre::ST_GENERIC,
		1,
		Ogre::INSTANCING_CULLING_SINGLETHREAD
	);

	// Add scene manager to shader generator
	shaderGenerator.addSceneManager(pSceneMgr);

	loadResources("General", {
		R"(media\models)",
		R"(media\materials\scripts)",
		R"(media\materials\textures)",
		R"(media\materials\programs)",
		R"(media\materials\programs\cg)",
		R"(media\materials\programs\hlsl)",
		R"(media\packs\cubemapsJS.zip)"
	});
	
	// Done with the machinery, we can actually set up the scene now

	// Make camera
	Ogre::Camera* pCamera = pSceneMgr->createCamera("Camera");

	// Set up workspace
	Ogre::CompositorManager2* pCompositorManager = root.getCompositorManager2();
	const Ogre::String workspaceName = "scene workspace";
	pCompositorManager->createBasicWorkspaceDef(workspaceName, Ogre::ColourValue::Black);
	pCompositorManager->addWorkspace(pSceneMgr, pRenderWin, pCamera, workspaceName, true);

	// Make a simple scene. Mostly following the camera track example.
	pSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	// setup some basic lighting for our scene
	pSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
	Ogre::SceneNode *lightNode = pSceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(20, 80, 50);
	lightNode->attachObject(pSceneMgr->createLight());

	// create an ogre head entity and attach it to a node
	Ogre::Entity* head = pSceneMgr->createEntity("ogrehead.mesh");
	head->setName("Head");
	Ogre::SceneNode* headNode = pSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(head);

	pCamera->setAutoTracking(true, headNode);   // make the camera face the head

	// create a camera node and attach camera to it
	Ogre::SceneNode* camNode = pSceneMgr->getRootSceneNode()->createChildSceneNode();
	pCamera->detachFromParent();
	camNode->attachObject(pCamera);

	// set up a 10 second animation for our camera, using spline interpolation for nice curves
	Ogre::Animation* anim = pSceneMgr->createAnimation("CameraTrack", 10);
	anim->setInterpolationMode(Ogre::Animation::IM_SPLINE);

	// create a track to animate the camera's node
	Ogre::NodeAnimationTrack* track = anim->createNodeTrack(camNode);

	// create keyframes for our track
	track->createNodeKeyFrame(0)->setTranslate(Ogre::Vector3(200, 0, 0));
	track->createNodeKeyFrame(2.5)->setTranslate(Ogre::Vector3(0, -50, 100));
	track->createNodeKeyFrame(5)->setTranslate(Ogre::Vector3(-500, 100, 0));
	track->createNodeKeyFrame(7.5)->setTranslate(Ogre::Vector3(0, 200, -300));
	track->createNodeKeyFrame(10)->setTranslate(Ogre::Vector3(200, 0, 0));

	// create a new animation state to track this
	Ogre::AnimationState* pAnimState = pSceneMgr->createAnimationState("CameraTrack");
	pAnimState->setEnabled(true);

	// Listens for window close events and frame events.
	Listener listener(pRenderWin);

	listener.doEachFrame([=] (const Ogre::FrameEvent& evt) {
		pAnimState->addTime(evt.timeSinceLastFrame);
	});

	root.startRendering();

	return 0;
}


