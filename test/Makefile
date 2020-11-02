SRC=HelloOgre.cpp
OBJ=HelloOgre.o 
BIN=test
CC=c++ -std=c++2a
INC=-I ../external/particleuniverse/Plugins/ParticleUniverse/include -I../external/mygui/include -I ../external/mygui/include/Platforms/Ogre/OgrePlatform/include -I ../external/imgui
LIB=-L../external/mygui/lib -L../external/particleuniverse/build
PARTICLE=../external/particleuniverse/build/Plugin_ParticleUniverse.so

.cpp.o:
	$(CC) -g -c $< `pkg-config --cflags --libs OGRE` $(INC)
all:$(OBJ)
	$(CC) -g $(OBJ) -o $(BIN) $(LIB) $(PARTICLE) `pkg-config --cflags --libs OGRE` -lGL -ltinyxml -lboost_system -lSDL2 -lOgreOverlay -lOgreTerrain -lMyGUIEngine -lMyGUI.OgrePlatform
clean:
	@rm -rf $(BIN) $(OBJ) > /dev/null


