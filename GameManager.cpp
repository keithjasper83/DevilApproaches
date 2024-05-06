#include "GameManager.h"
#include "ControlManager.h"
#include "Level.h"
#include "Player.h"
#include <SFML/System.hpp> // Include SFML's system header for sleep function

GameManager::GameManager()
{
    active = true;
    // Initialize the game
}

void GameManager::run()
{
    WindowManager windowManager;
    windowManager.createWindow();
    active = windowManager.isActive();

    ControlManager::isJoystickConnected();

    Level level(4000, 4000);
    Player player(level);
    player.setStartPosition();

    // Define viewport size and position
    sf::FloatRect viewport(0.f, 0.f, windowManager.window.getSize().x, windowManager.window.getSize().y);

    // Circular buffer for frame times
    const int numSamples = 100;
    std::vector<float> frameTimes(numSamples, 0.0f);
    int frameIndex = 0; // Index to keep track of the current frame time
    sf::Clock clock;    // Declare sf::Clock object

    while (windowManager.isActive())
    {
        windowManager.window.clear();

        // Set the view to the new viewport
        windowManager.window.setView(sf::View(viewport));
        ControlManager::pollEvents(windowManager.window);

        // Game logic and update at fixed timestep (60 FPS)
        // For simplicity, let's move the player automatically in this example
        // Handle player movement with keyboard input
        sf::Vector2f movement = ControlManager::getPlayerMovement();
        player.move(movement.x, movement.y);
        if (ControlManager::shouldExitGame())
        {
            std::cout << "Exiting game..." << std::endl;
            windowManager.closeWindow();
            break;
        }
        if (ControlManager::shouldResetGame())
        {
            std::cout << "Resetting game..." << std::endl;
            player.setStartPosition();
        }

        // Handle controller movement
        sf::Vector2f controllerMovement = ControlManager::getControllerMovement(0);
        player.move(controllerMovement.x, controllerMovement.y);

        if (ControlManager::shouldExitGame(0))
        {
            windowManager.closeWindow();
            break;
        }
        if (ControlManager::shouldResetGame(0))
        {
            player.setStartPosition();
        }

        // Update viewport position to keep player centered until it reaches the edge
        sf::Vector2f playerPosition = player.getPosition();
        if (playerPosition.x - viewport.width / 2.f < 0)
        {
            viewport.left = 0;
        }
        else if (playerPosition.x + viewport.width / 2.f > level.getSize().x)
        {
            viewport.left = level.getSize().x - viewport.width;
        }
        else
        {
            viewport.left = playerPosition.x - viewport.width / 2.f;
        }

        if (playerPosition.y - viewport.height / 2.f < 0)
        {
            viewport.top = 0;
        }
        else if (playerPosition.y + viewport.height / 2.f > level.getSize().y)
        {
            viewport.top = level.getSize().y - viewport.height;
        }
        else
        {
            viewport.top = playerPosition.y - viewport.height / 2.f;
        }

        // Render
        windowManager.window.setView(sf::View(viewport));
        level.draw(windowManager.window);
        player.draw(windowManager.window);

        // Calculate the average FPS
        float sumFrameTimes = 0.0f;
        for (int i = 0; i < numSamples; ++i)
        {
            sumFrameTimes += frameTimes[i];
        }
        float averageFPS = numSamples / sumFrameTimes;

        windowManager.updateWindowTitle(averageFPS, player.getPosition());
        windowManager.window.setView(windowManager.window.getDefaultView());

        // Draw player position
        windowManager.drawText("Player Position: (" + std::to_string(static_cast<int>(std::round(playerPosition.x))) +
                                   ", " + std::to_string(static_cast<int>(std::round(playerPosition.y))) + ")",
                               windowManager.window.getSize().x - 500, 10);

        // Draw FPS
        windowManager.drawText("FPS: " + std::to_string(static_cast<int>(averageFPS)),
                               windowManager.window.getSize().x - 500, 40);

        windowManager.window.display();

        // Update the circular buffer with the current frame time
        sf::Time frameTime = clock.restart();
        frameTimes[frameIndex] = frameTime.asSeconds();
        frameIndex = (frameIndex + 1) % numSamples;
    }
}
