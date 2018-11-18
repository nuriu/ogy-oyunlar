#include <memory>

#include <Game.hpp>

int main()
{
    std::unique_ptr<Game> game = std::make_unique<Game>("Breakout-ish", 896, 600);

    game->run();

    return EXIT_SUCCESS;
}
