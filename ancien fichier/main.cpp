#include "GameManager.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    GameManager* game = new GameManager();
    game->InitGame();

    bool running = true;
    float deltaTime = 0;

    while (running)
    {
        game->GameLoop(running);
    }

    game->EndGame();

    return 0;
}
