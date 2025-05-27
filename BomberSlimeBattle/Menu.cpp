#include "Menu.h"

Menu::Menu() {
    video = Video::getInstance();
    rm = ResourceManager::getInstance();
    selectedOption = 0;
    totalOptions = 3;
    currentMapShown = 1;

    map1ID = rm->loadAndGetGraphicID("Assets/numOne.png");
    map2ID = rm->loadAndGetGraphicID("Assets/numTwo.png");
    map3ID = rm->loadAndGetGraphicID("Assets/numThree.png");

    backgroundID = rm->loadAndGetGraphicID("Assets/backgroundMenu.png");
    jugarID = rm->loadAndGetGraphicID("Assets/playButton.png");
    cambiarMapaID = rm->loadAndGetGraphicID("Assets/changeMapButton.png");
    salirID = rm->loadAndGetGraphicID("Assets/exitButton.png");
}

void Menu::render() {
    // Fondo
    video->renderGraphic(backgroundID, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    const int buttonWidth = 200;
    const int buttonHeight = 50;
    const int spacing = 70;

    int totalHeight = totalOptions * spacing;
    int x = (SCREEN_WIDTH - buttonWidth) / 2;
    int y = (SCREEN_HEIGHT - totalHeight) / 2;

    for (int i = 0; i < totalOptions; i++) {
        if (i == selectedOption)
            video->drawRect(x - 10, y + spacing * i - 10, buttonWidth + 20, buttonHeight + 20, 255, 255, 0);

        int id = (i == 0) ? jugarID : (i == 1) ? cambiarMapaID : salirID;
        video->renderGraphic(id, x, y + i * spacing, buttonWidth, buttonHeight, 0, 0);

        if (i == 1) {
            int mapNumID = (currentMapShown == 1) ? map1ID : (currentMapShown == 2) ? map2ID : map3ID;

            video->renderGraphic(mapNumID, x + buttonWidth + 20, y + i * spacing, 32, 50, 0, 0);
        }
    }
}

void Menu::update(int keyPressed) {
    if (keyPressed == SDLK_DOWN)
        selectedOption = (selectedOption + 1) % totalOptions;
    else if (keyPressed == SDLK_UP)
        selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
}

int Menu::getSelectedOption() {
    return selectedOption + 1;
}

void Menu::resetSelection() {
    selectedOption = 0;
}

void Menu::setCurrentMap(int map) {
    currentMapShown = map;
}
