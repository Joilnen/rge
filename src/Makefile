SRC=main.cpp frame_listener.cpp resources.cpp Actor.cpp Event.cpp EngineManager.cpp World.cpp \
	Render.cpp Ui.cpp ParticleUniverseWrapper.cpp SampleUI.cpp 
OBJ=main.o FrameListener.o resources.o Actor.o Event.o EngineManager.o World.o \
	Render.o Ui.o ParticleUniverseWrapper.o SampleUI.o  
BIN=russell
CC=c++ -std=c++2a
INC=-I ../external/particleuniverse/Plugins/ParticleUniverse/include -I../external/mygui/include -I ../external/mygui/include/OgrePlatform/include -I /usr/local/include/OGRE/Overlay
LIB=-L../external/mygui/lib -L../external/particleuniverse/build
PARTICLE=../external/particleuniverse/build/Plugin_ParticleUniverse.so

.cpp.o:
	$(CC) -g -c $< `pkg-config --cflags --libs OGRE` $(INC)
all:$(OBJ)
	$(CC) -g $(OBJ) -o $(BIN) $(LIB) $(PARTICLE) `pkg-config --cflags --libs OGRE` -lGL -ltinyxml -lboost_system -lSDL2 -lOgreOverlay -lOgreTerrain -lMyGUIEngine -lMyGUI.OgrePlatform
clean:
	@rm -rf $(BIN) $(OBJ) > /dev/null


