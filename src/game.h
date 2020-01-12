#pragma once


#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include "snake.h"
#include "fruit.h"
#include "vector2.h"


const int WINDOW_WIDTH = 640,
          WINDOW_HEIGHT = 480;

class Game {
private:
    sf::RenderWindow* window;
    Snake* snake;
    Fruit* fruit;
    float accumulated_time;
    bool running;

private:
    Vector2 get_random_pos() {
        return {rand()%(WINDOW_WIDTH/20), rand()%(WINDOW_HEIGHT/20)};
    }

    bool has_snake_eaten_fruit() {
        Vector2 snake_head_pos = snake->get_corpse().front();
        Vector2 fruit_pos = fruit->get_position();
        return snake_head_pos.x == fruit_pos.x && snake_head_pos.y == fruit_pos.y;
    }

    void respawn_fruit() {
        fruit->set_position(get_random_pos());
    }

    void on_eat_fruit() {
        snake->add_size();
        respawn_fruit();
    }

public:
    Game() {
        srand(time(nullptr));
        snake = new Snake();
        fruit = new Fruit(get_random_pos());
        window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "snake-game");
        window->setFramerateLimit(60);
        running = true;
        accumulated_time = 0;
    }

    ~Game() {
        if (window->isOpen()) {
            window->close();
        }
        delete window;
        delete snake;
        delete fruit;
    }

    bool is_running() {
        return running;
    }

    void handle_window_events() {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed: {
                    window->close();
                } break;
                default: {

                }
            }
        }
    }

    void handle_input() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            snake->set_direction(NORTH);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            snake->set_direction(SOUTH);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            snake->set_direction(WEST);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            snake->set_direction(EAST);
        }
    }

    float current_framerate() {
        return 1000/(2 + snake->get_size()/10);        
    }

    void update(float delta_time) {
        accumulated_time += delta_time;

        if (accumulated_time >= current_framerate()) {
            accumulated_time = 0;

            snake->update({WINDOW_WIDTH/20, WINDOW_HEIGHT/20}, delta_time);

            if (has_snake_eaten_fruit()) {
                on_eat_fruit();
            }
        }
    }

    void display() {
        window->clear();
        snake->draw(window);
        fruit->draw(window);
        window->display();
    }
};