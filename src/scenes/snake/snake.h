#pragma once
#include "core/scene.h"

class Snake : public Scene {
public:
    void init() override;
    void update() override;
    void draw() override;
    void shutdown() override;
};