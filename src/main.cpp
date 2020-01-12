#include <SFML/Graphics.hpp>
#include "game.h"


int main() {
    auto game = new Game();
    sf::Clock clock;
    float delta_time = 0;

    while (game->is_running()) {
        game->handle_window_events();
        game->handle_input();
        game->update(delta_time);
        game->display();
        delta_time = clock.restart().asMilliseconds();
    }

    delete game;
    return 0;
}



