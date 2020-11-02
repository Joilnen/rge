SRC=main.cpp GameManager.cpp
OBJ=main.o GameManager.o 
BIN=rnsf
CC=c++ -std=c++2a
INC=-I ../external/particleuniverse/Plugins/ParticleUniverse/include -I../external/mygui/include -I ../external/mygui/Platforms/Ogre/OgrePlatform/include
LIB=-L../external/mygui/lib -L../external/particleuniverse/build
PLG=../external/particleuniverse/build/Plugin_ParticleUniverse.so

.cpp.o:
	$(CC) -g -c $< `pkg-config --cflags --libs OGRE` $(INC)
all:$(OBJ)
	$(CC) -g $(OBJ) $(PLG) -o $(BIN) $(LIB) `pkg-config --cflags --libs OGRE` -lGL -ltinyxml -lboost_system -lSDL2 -lOgreOverlay -lOgreTerrain -lMyGUIEngine -lMyGUI.OgrePlatform
clean:
	@rm -rf $(BIN) $(OBJ) > /dev/null


