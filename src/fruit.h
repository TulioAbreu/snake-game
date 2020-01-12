#pragma once

#include <SFML/Graphics.hpp>
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

    void draw(sf::RenderWindow* window) {
        Vector2 pos = get_position();
        sf::RectangleShape rect;
        const int size = 20;
        rect.setSize(sf::Vector2f(size, size));
        rect.setPosition(pos.x*size, pos.y*size);
        rect.setFillColor(sf::Color::Red);
        window->draw(rect);
    }
};