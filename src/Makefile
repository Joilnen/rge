SRC=main.cpp EngineManager.cpp WorkArea3D.cpp # frame_listener.cpp resources.cpp Actor.cpp Event.cpp World.cpp \
	Render.cpp Ui.cpp ParticleUniverseWrapper.cpp SampleUI.cpp 
OBJ=main.o EngineManager.o WorkArea3D.o# FrameListener.o resources.o Actor.o Event.o  World.o \
	Render.o Ui.o ParticleUniverseWrapper.o SampleUI.o  
BIN=russell
CC=c++ -std=c++2a
INC=-I ../external/particleuniverse/Plugins/ParticleUniverse/include -I../external/mygui/include -I ../external/mygui/include/OgrePlatform/include -I /usr/local/include/OGRE/Overlay -I /usr/local/include/OGRE/RTShaderSystem
LIB=-L../external/mygui/lib -L../external/particleuniverse/build
PARTICLE=../external/particleuniverse/build/Plugin_ParticleUniverse.so

.cpp.o:
	$(CC) -g -c $< `pkg-config --cflags --libs OGRE` $(INC)
all:$(OBJ)
	$(CC) -g $(OBJ) -o $(BIN) $(LIB) `pkg-config --cflags --libs OGRE` -lGL -ltinyxml -lboost_system -lSDL2 -lOgreOverlay -lOgreTerrain -lMyGUIEngine -lMyGUI.OgrePlatform -lOgreBites -lOgreRTShaderSystem -lParticleUniverse
clean:
	@rm -rf $(BIN) $(OBJ) > /dev/null


