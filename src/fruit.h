#pragma once

#include "vector2.h"

class Fruit {
private:
    Vector2 position;

public:
    Fruit(Vector2 startPos) {
        position = startPos;
    }

    void set_position(Vector2 pos) {
        position = pos;
    }

    Vector2 get_position() {
        return position;
    }
};