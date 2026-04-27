#include "menu.h"
#include "core/scene_manager.h"
#include "core/scene_factory.h"
#include "raylib.h"

// constructor
Menu::Menu(SceneManager* m) : manager(m) {}

void Menu::init() {

}

// update logic (input + switching scenes)
void Menu::update() {
    Vector2 mouse = GetMousePosition();

    Rectangle snakeGameBtn = { 300, 200, 200, 50 };

    if (CheckCollisionPointRec(mouse, snakeGameBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        manager->changeScene(SceneFactory::createSnake());
    }
}

// drawing
void Menu::draw() {
    DrawText("Main Menu", 320, 120, 30, WHITE);

    DrawRectangle(300, 200, 200, 50, DARKGRAY);
    DrawText("Snake Game", 340, 215, 20, WHITE);
}

void Menu::shutdown() {

}