#pragma once
#include "Video.h"
#include "ResourceManager.h"

class Menu {
private:
    int selectedOption;
    int currentMapShown;
    
    int jugarID;
    int cambiarMapaID;
    int salirID;
    int backgroundID;
    int map1ID;
    int map2ID;
    int map3ID;

    int totalOptions;
    Video* video;
    ResourceManager* rm;

public:
    Menu();
    void render();
    void update(int keyPressed);
    int getSelectedOption();
    void resetSelection();
    void setCurrentMap(int map);
};