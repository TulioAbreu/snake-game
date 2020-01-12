#pragma once

#include <list>
#include "vector2.h"
#include "direction.h"

class Snake {
private:
    std::list<Vector2> corpse;
    Direction direction;

private:
    Vector2 get_head_position() {
        return corpse.front();
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

    void handle_movement() {
        Vector2 next_head_position = get_next_head_position();
        corpse.pop_back();
        corpse.push_front(next_head_position);      
    }

public:
    Snake() {
        corpse.push_front({0, 0});
        direction = EAST;
    }

    void update() {
        handle_movement();
    }

    bool is_alive() {
        if (corpse.size() <= 2) {
            return true;
        }

        Vector2 head = get_head_position();
        int counter = 0;
        for (auto piece : corpse) {
            if (head.x == piece.x && head.y == piece.y) {
                counter++;
            }
        }
        return counter == 1;
    }

    void set_direction(Direction direction) {
        this->direction = direction;
    }

    void add_size() {
        corpse.push_back(corpse.back());
    }

    std::list<Vector2> get_corpse() {
        return corpse;
    }
};