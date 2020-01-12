#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include "snake.h"
#include "fruit.h"
using namespace std;


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void handle_window_events(sf::RenderWindow* window);
void handle_input(Snake* snake);
void draw_snake(sf::RenderWindow* window, Snake* snake);
void draw_snake_position(sf::RenderWindow* window, Vector2 pos);
void draw_fruit(sf::RenderWindow* window, Fruit* fruit);
void update(Snake* snake, Fruit* fruit);
Vector2 get_random_pos();

int main() {
    srand(time(nullptr));
    auto window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                       "snake-game");
    window->setFramerateLimit(60);
    auto snake = new Snake();
    auto fruit = new Fruit(get_random_pos());
    int frameCounter = 0;
    while (window->isOpen()) {
        handle_window_events(window);
        handle_input(snake);
        window->clear();
        if (frameCounter >= 15) {
            update(snake, fruit);
            frameCounter = 0;
        }
        draw_snake(window, snake);
        draw_fruit(window, fruit);
        window->display();
        frameCounter++;

        if (!snake->is_alive()) {
            window->close();
        }
    }
    delete snake;
    delete fruit;
    delete window;
    return 0;
}

void update(Snake* snake, Fruit* fruit) {
    snake->update();

    Vector2 snake_head_pos = snake->get_corpse().front();
    Vector2 fruit_pos = fruit->get_position();
    if (snake_head_pos.x == fruit_pos.x && snake_head_pos.y == fruit_pos.y) {
        snake->add_size();
        fruit->set_position(get_random_pos());
    }
}

Vector2 get_random_pos() {
    return {rand()%(WINDOW_WIDTH/20), rand()%(WINDOW_HEIGHT/20)};
}

void handle_window_events(sf::RenderWindow* window) {
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

void handle_input(Snake* snake) {
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

void draw_snake(sf::RenderWindow* window, Snake* snake) {
    for (auto pos : snake->get_corpse()) {
        draw_snake_position(window, pos);
    }
}

void draw_snake_position(sf::RenderWindow* window, Vector2 pos) {
    sf::RectangleShape rect;
    const int size = 20;
    rect.setSize(sf::Vector2f(size, size));
    rect.setPosition(pos.x*size, pos.y*size);
    rect.setFillColor(sf::Color::Green);
    window->draw(rect);
}

void draw_fruit(sf::RenderWindow* window, Fruit* fruit) {
    Vector2 pos = fruit->get_position();
    sf::RectangleShape rect;
    const int size = 20;
    rect.setSize(sf::Vector2f(size, size));
    rect.setPosition(pos.x*size, pos.y*size);
    rect.setFillColor(sf::Color::Red);
    window->draw(rect);
}
