#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "vector2.h"
#include "direction.h"

class Snake {
private:
    std::list<Vector2> corpse;
    Direction direction;
    bool alive;

private:
    Vector2 get_head_position() {
        return corpse.front();
    }


    bool is_inside_arena(Vector2 arenaSize, Vector2 next_head_position) {
        if (next_head_position.x < 0) {
            return false;
        }
        if (next_head_position.y < 0) {
            return false;
        }
        if (next_head_position.x >= arenaSize.x) {
            return false;
        }
        if (next_head_position.y >= arenaSize.y) {
            return false;
        }
        return true;
    }

    void move() {
        Vector2 next_head_position = get_next_head_position();       
        corpse.pop_back();
        corpse.push_front(next_head_position);      
    }


    void draw_snake_position(sf::RenderWindow* window, Vector2 pos) {
        sf::RectangleShape rect;
        const int size = 20;
        rect.setSize(sf::Vector2f(size, size));
        rect.setPosition(pos.x*size, pos.y*size);
        rect.setFillColor(sf::Color::Green);
        window->draw(rect);
    }

    bool will_collide_itself() {
        Vector2 head = get_next_head_position();
        int counter = 0;
        for (auto piece : corpse) {
            if (head.x == piece.x && head.y == piece.y) {
                counter++;
            }
        }
        return counter > 0;
    }

    bool is_next_movement_valid(Vector2 arenaSize) {
        Vector2 next_head_position = get_next_head_position();
        return is_inside_arena(arenaSize, next_head_position);
    }

public:
    Snake() {
        corpse.push_front({0, 0});
        direction = EAST;
        alive = true;
    }

    Vector2 get_next_head_position() {
        Vector2 head_pos = get_head_position();
        switch (direction) {
        case NORTH: {
            return {head_pos.x, head_pos.y-1};
        } break;
        case SOUTH: {
            return {head_pos.x, head_pos.y+1};
        } break;
        case EAST: {
            return {head_pos.x+1, head_pos.y};
        } break;
        case WEST: {
            return {head_pos.x-1, head_pos.y};
        } break;
        }
        return {0, 0};
    }

    void update(Vector2 arena_size, float delta_time) {
        if (is_alive()) {
            if (will_collide_itself()) {
                alive = false;
            }

            if (is_next_movement_valid(arena_size)) {
                move();
            }
            else {
                alive = false;
            }
        }
    }

    bool is_alive() {
        return alive;
    }

    void set_direction(Direction direction) {
        this->direction = direction;
    }

    void add_size() {
        corpse.push_back(corpse.back());
    }

    int get_size() {
        return corpse.size();
    }

    std::list<Vector2> get_corpse() {
        return corpse;
    }

    void draw(sf::RenderWindow* window) {
        for (auto pos : get_corpse()) {
            draw_snake_position(window, pos);
        }
    }
};